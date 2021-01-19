#include <iostream>
#include <iomanip>
#include <sstream>
#include <thrust/host_vector.h>

#include "dg/algorithm.h"
#include "dg/file/json_utilities.h"

#ifndef WITHOUT_GLFW
#include "draw/host_window.h"
#endif
#include "dg/file/file.h"

#include "init.h"
#include "diag.h"
#include "shu.cuh"


int main( int argc, char* argv[])
{
    ////Parameter initialisation ////////////////////////////////////////////
    Json::Value js;
    enum file::error mode = file::error::is_warning;
    if( argc == 1)
        file::file2Json( "input/default.json", js, file::comments::are_discarded);
    else
        file::file2Json( argv[1], js);
    std::cout << js <<std::endl;

    /////////////////////////////////////////////////////////////////
    dg::CartesianGrid2d grid = shu::createGrid( js, mode);
    dg::DVec w2d( dg::create::weights(grid));
    /////////////////////////////////////////////////////////////////

    std::string initial = file::get( mode, js, "init", "type", "lamb").asString();
    dg::HVec omega = shu::initial_conditions.at( initial)(js, mode, grid);

    dg::DVec y0( omega ), y1( y0);
    //subtract mean mass
    if( grid.bcx() == dg::PER && grid.bcy() == dg::PER)
    {
        double meanMass = dg::blas1::dot( y0, w2d)/(double)(grid.lx()*grid.ly());
        dg::blas1::axpby( -meanMass, 1., 1., y0);
    }
    //make solver and stepper
    shu::Shu<dg::CartesianGrid2d, dg::IDMatrix, dg::DMatrix, dg::DVec>
        shu( grid, js, mode);
    shu::Diffusion<dg::CartesianGrid2d, dg::DMatrix, dg::DVec> diffusion( grid, js, mode);
    if( "mms" == initial)
    {
        double sigma = file::get( mode, js, "init", "sigma", 0.2).asDouble();
        double velocity = file::get( mode, js, "init", "velocity", 0.1).asDouble();
        shu.set_mms_source( sigma, velocity, grid.ly());
    }

    double time = 0;
    shu::Variables var = {shu, grid, y0, time, w2d, 0., mode, js};
    dg::Timer t;
    t.tic();
    shu( 0., y0, y1);
    t.toc();
    var.duration = t.diff();
    for( auto record : shu::diagnostics1d_list)
    {
        double result = record.function( var);
        std::cout  << "Diagnostics "<<record.name<<" "<<result<<"\n";
    }

    /// ////////////// Initialize timestepper ///////////////////////
    std::string stepper = file::get( mode, js, "timestepper", "stepper", "FilteredMultistep").asString();
    std::string regularization = file::get( mode, js, "regularization", "type", "moddal").asString();
    dg::ModalFilter<dg::DMatrix, dg::DVec> filter;
    dg::Karniadakis<dg::DVec> karniadakis;
    dg::ShuOsher<dg::DVec> shu_osher;
    dg::FilteredExplicitMultistep<dg::DVec> multistep;
    if( regularization == "modal")
    {
        double alpha = file::get( mode, js, "regularization", "alpha", 36).asDouble();
        double order = file::get( mode, js, "regularization", "order", 8).asDouble();
        double eta_c = file::get( mode, js, "regularization", "eta_c", 0.5).asDouble();
        filter.construct( dg::ExponentialFilter(alpha, eta_c, order, grid.n()), grid);
    }
    double dt = file::get( mode, js, "timestepper", "dt", 2e-3).asDouble();
    if( "Karniadakis" == stepper)
    {
        if( regularization != "viscosity")
        {
            throw dg::Error(dg::Message(_ping_)<<"Warning! Karniadakis only works with viscosity regularization! Exit now!");

            return -1;
        }
        double eps_time = file::get( mode, js, "timestepper", "eps_time", 1e-10).asDouble();
        karniadakis.construct( y0, y0.size(), eps_time);
        karniadakis.init( shu, diffusion, time, y0, dt);
    }
    else if( "Shu-Osher" == stepper)
    {
        shu_osher.construct( "SSPRK-3-3", y0);
    }
    else if( "FilteredMultistep" == stepper)
    {
        multistep.construct( "eBDF", 3, y0);
        multistep.init( shu, filter, time, y0, dt);
    }
    else
    {
        throw dg::Error(dg::Message(_ping_)<<"Error! Timestepper not recognized!\n");

        return -1;
    }
    unsigned maxout = file::get( mode, js, "output", "maxout", 100).asUInt();
    unsigned itstp = file::get( mode, js, "output", "itstp", 5).asUInt();
    std::string output = file::get( mode, js, "output", "type", "glfw").asString();
#ifndef WITHOUT_GLFW
    if( "glfw" == output)
    {
        ////////////////////////////////glfw//////////////////////////////
        //create visualisation vectors
        dg::DVec visual( grid.size());
        dg::HVec hvisual( grid.size());
        //transform vector to an equidistant grid
        std::stringstream title;
        GLFWwindow* w = draw::glfwInitAndCreateWindow(600, 600, "");
        draw::RenderHostData render( 1,1);
        draw::ColorMapRedBlueExt colors( 1.);
        dg::IDMatrix equidistant = dg::create::backscatter( grid );
        while (!glfwWindowShouldClose(w) && time < maxout*itstp*dt)
        {
            dg::blas2::symv( equidistant, y0, visual);
            colors.scale() =  (float)thrust::reduce( visual.begin(), visual.end(), -1., dg::AbsMax<double>() );
            //draw and swap buffers
            dg::blas1::transfer( visual, hvisual);
            render.renderQuad( hvisual, grid.n()*grid.Nx(), grid.n()*grid.Ny(), colors);
            title << "Time "<<time<< " \ttook "<<t.diff()/(double)itstp<<"\t per step";
            glfwSetWindowTitle(w, title.str().c_str());
            title.str("");
            glfwPollEvents();
            glfwSwapBuffers(w);
            //step
            t.tic();
            try{
                for( unsigned j=0; j<itstp; j++)
                {
                    if( "Karniadakis" == stepper)
                        karniadakis.step( shu, diffusion, time, y0);
                    else if ( "FilteredMultistep" == stepper)
                        multistep.step( shu, filter, time, y0);
                    else if ( "Shu-Osher" == stepper)
                        shu_osher.step( shu, filter, time, y0, time, y0, dt);
                }
            } catch( dg::Fail& fail) {
                std::cerr << "CG failed to converge to "<<fail.epsilon()<<"\n";
                std::cerr << "Does Simulation respect CFL condition?\n";
                return -1;
            }
            t.toc();
            var.duration = t.diff()/(double)itstp;
        }
        glfwTerminate();
    }
    else
#endif //WITHOUT_GLFW
    {
        std::string inputfile = js.toStyledString(); //save input without comments, which is important if netcdf file is later read by another parser
        std::string outputfile;
        if( argc == 1 || argc == 2)
            outputfile = "shu.nc";
        else
            outputfile = argv[2];
        /// //////////////////////set up netcdf/////////////////////////////////////
        file::NC_Error_Handle err;
        int ncid=-1;
        try{
            err = nc_create( outputfile.c_str(),NC_NETCDF4|NC_CLOBBER, &ncid);
        }catch( std::exception& e)
        {
            std::cerr << "ERROR creating file "<<outputfile<<std::endl;
            std::cerr << e.what()<<std::endl;
           return -1;
        }
        /// Set global attributes
        std::map<std::string, std::string> att;
        att["title"] = "Output file of feltor/src/lamb_dipole/shu_b.cu";
        att["Conventions"] = "CF-1.7";
        ///Get local time and begin file history
        auto ttt = std::time(nullptr);
        auto tm = *std::localtime(&ttt);

        std::ostringstream oss;
        ///time string  + program-name + args
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        for( int i=0; i<argc; i++) oss << " "<<argv[i];
        att["history"] = oss.str();
        att["comment"] = "Find more info in feltor/src/lamb_dipole/shu.tex";
        att["source"] = "FELTOR";
        att["references"] = "https://github.com/feltor-dev/feltor";
        att["inputfile"] = inputfile;
        for( auto pair : att)
            err = nc_put_att_text( ncid, NC_GLOBAL,
                pair.first.data(), pair.second.size(), pair.second.data());

        int dim_ids[3], tvarID;
        std::map<std::string, int> id1d, id3d;
        err = file::define_dimensions( ncid, dim_ids, &tvarID, grid,
                {"time", "y", "x"});

        //Create field IDs
        for( auto& record : shu::diagnostics2d_list)
        {
            std::string name = record.name;
            std::string long_name = record.long_name;
            id3d[name] = 0;
            err = nc_def_var( ncid, name.data(), NC_DOUBLE, 3, dim_ids,
                    &id3d.at(name));
            err = nc_put_att_text( ncid, id3d.at(name), "long_name", long_name.size(),
                long_name.data());
        }
        for( auto& record : shu::diagnostics1d_list)
        {
            std::string name = record.name;
            std::string long_name = record.long_name;
            id1d[name] = 0;
            err = nc_def_var( ncid, name.data(), NC_DOUBLE, 1, &dim_ids[0],
                &id1d.at(name));
            err = nc_put_att_text( ncid, id1d.at(name), "long_name", long_name.size(),
                long_name.data());
        }
        err = nc_enddef(ncid);
        size_t start[3] = {0, 0, 0};
        size_t count[3] = {1, grid.n()*grid.Ny(), grid.n()*grid.Nx()};
        ///////////////////////////////////first output/////////////////////////
        dg::DVec resultD = dg::evaluate( dg::zero, grid);
        dg::HVec resultH( resultD);
        for( auto& record : shu::diagnostics2d_list)
        {
            record.function( resultD, var);
            dg::assign( resultD, resultH);
            file::put_vara_double( ncid, id3d.at(record.name), start[0], grid, resultH);
        }
        for( auto& record : shu::diagnostics1d_list)
        {
            double result = record.function( var);
            nc_put_vara_double( ncid, id1d.at(record.name), start, count, &result);
        }
        err = nc_put_vara_double( ncid, tvarID, start, count, &time);
        ///////////////////////////////////timeloop/////////////////////////
        unsigned step=0;
        try{
        for( unsigned i=1; i<=maxout; i++)
        {

            dg::Timer ti;
            ti.tic();
            for( unsigned j=0; j<itstp; j++)
            {
                if( "Karniadakis" == stepper)
                    karniadakis.step( shu, diffusion, time, y0);
                else if ( "FilteredMultistep" == stepper)
                    multistep.step( shu, filter, time, y0);
                else if ( "Shu-Osher" == stepper)
                    shu_osher.step( shu, filter, time, y0, time, y0, dt);
            }
            step+=itstp;
            ti.toc();
            var.duration = ti.diff() / (double) itstp;
            //output all fields
            start[0] = i;
            for( auto& record : shu::diagnostics2d_list)
            {
                record.function( resultD, var);
                dg::assign( resultD, resultH);
                file::put_vara_double( ncid, id3d.at(record.name), start[0], grid, resultH);
            }
            for( auto& record : shu::diagnostics1d_list)
            {
                double result = record.function( var);
                nc_put_vara_double( ncid, id1d.at(record.name), start, count, &result);
            }
            err = nc_put_vara_double( ncid, tvarID, start, count, &time);
            std::cout << "\n\t Step "<<step <<" of "<<itstp*maxout <<" at time "<<time;
            std::cout << "\n\t Average time for one step: "<<var.duration<<"s\n\n"<<std::flush;
        }
        }
        catch( dg::Fail& fail) {
            std::cerr << "CG failed to converge to "<<fail.epsilon()<<"\n";
            std::cerr << "Does Simulation respect CFL condition?\n";
            err = nc_close(ncid);
            return -1;
        }
        err = nc_close(ncid);
    }
    ////////////////////////////////////////////////////////////////////
    std::cout << "Time "<<time<<std::endl;
    for( auto record : shu::diagnostics1d_list)
    {
        double result = record.function( var);
        std::cout  << "Diagnostics "<<record.name<<" "<<result<<"\n";
    }

    return 0;

}
