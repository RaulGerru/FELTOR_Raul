#include <iostream>
#include <iomanip>

#include "dg/file/file.h"
#include "shu.cuh"
#include "parameters.h"

double delta =0.05;
double rho =M_PI/15.;
double shearLayer(double x, double y){
    if( y<= M_PI)
        return delta*cos(x) - 1./rho/cosh( (y-M_PI/2.)/rho)/cosh( (y-M_PI/2.)/rho);
    return delta*cos(x) + 1./rho/cosh( (3.*M_PI/2.-y)/rho)/cosh( (3.*M_PI/2.-y)/rho);
}

int main( int argc, char * argv[])
{
    dg::Timer t;
    ////////////////////////Parameter initialisation//////////////////////////
    Json::Value js;
    if( argc != 3)
    {
        std::cerr << "ERROR: Wrong number of arguments!\nUsage: "<< argv[0]<<" [inputfile] [outputfile]\n";
        return -1;
    }
    else
        file::file2Json( argv[1], js);
    std::string input = js.toStyledString(); //save input without comments, which is important if netcdf file is later read by another parser
    const Parameters p( js);
    p.display( std::cout);

    //////////////initiate solver/////////////////////////////////////////
    dg::Grid2d grid( 0, p.lx, 0, p.ly, p.n, p.Nx, p.Ny, p.bc_x, p.bc_y);
    dg::DVec w2d( dg::create::weights(grid));
    dg::Lamb lamb( p.posX*p.lx, p.posY*p.ly, p.R, p.U);
    dg::HVec omega;
    if( p.initial == "lamb")
        omega = dg::evaluate ( lamb, grid);
    else if ( p.initial == "shear")
        omega = dg::evaluate ( shearLayer, grid);
    dg::DVec y0( omega );
    const dg::DVec one = dg::evaluate( dg::one, grid);
    //make solver and stepper
    dg::Shu<dg::DMatrix, dg::DVec> shu( grid, p.eps);
    dg::Diffusion< dg::DMatrix, dg::DVec > diff( grid, p.D);
    dg::Karniadakis< dg::DVec> karniadakis( y0, y0.size(), 1e-10);
    karniadakis.init( shu, diff, 0., y0, p.dt);

    dg::DVec varphi( grid.size()), potential;
    double vorticity = dg::blas2::dot( one , w2d, y0);
    double enstrophy = 0.5*dg::blas2::dot( y0, w2d, y0);
    double energy =    0.5*dg::blas2::dot( y0, w2d, shu.potential()) ;
    potential = shu.potential();
    shu.arakawa().variation( potential, varphi);
    double variation = dg::blas2::dot( varphi, w2d, one );
    double time = 0;
    /////////////////////////////set up netcdf/////////////////////////////////////
    file::NC_Error_Handle err;
    int ncid;
    err = nc_create( argv[2],NC_NETCDF4|NC_CLOBBER, &ncid);
    err = nc_put_att_text( ncid, NC_GLOBAL, "inputfile", input.size(), input.data());
    int dim_ids[3], tvarID;
    int EtimeID, EtimevarID;
    err = file::define_dimensions( ncid, dim_ids, &tvarID, grid);
    err = file::define_time( ncid, "energy_time", &EtimeID, &EtimevarID);
    //field IDs
    std::string names3d[2] = {"vorticity_field", "potential"}; 
    std::string names1d[4] = {"vorticity", "enstrophy", "energy", "variation"}; 
    int dataIDs[2], variableIDs[4]; 
    for( unsigned i=0; i<2; i++){
        err = nc_def_var( ncid, names3d[i].data(), NC_DOUBLE, 3, dim_ids, &dataIDs[i]);}
    for( unsigned i=0; i<4; i++){
        err = nc_def_var( ncid, names1d[i].data(), NC_DOUBLE, 1, &EtimeID, &variableIDs[i]);}
    err = nc_enddef(ncid);
    size_t start[3] = {0, 0, 0};
    size_t count[3] = {1, grid.n()*grid.Ny(), grid.n()*grid.Nx()};
    size_t Estart[] = {0};
    size_t Ecount[] = {1};
    ///////////////////////////////////first output/////////////////////////
    std::vector<dg::HVec> output(2);
    dg::blas1::transfer( y0, output[0]);
    dg::blas1::transfer( shu.potential(), output[1]);
    for( int k=0;k<2; k++)
        err = nc_put_vara_double( ncid, dataIDs[k], start, count, output[k].data() );
    err = nc_put_vara_double( ncid, tvarID, start, count, &time);
    double output1d[4] = {vorticity, enstrophy, energy, variation};
    for( int k=0;k<4; k++)
        err = nc_put_vara_double( ncid, variableIDs[k], Estart, Ecount, &output1d[k] );
    err = nc_put_vara_double( ncid, EtimevarID, Estart, Ecount, &time);
    ///////////////////////////////////timeloop/////////////////////////
    unsigned step=0;
    try{
    for( unsigned i=0; i<p.maxout; i++)
    {

        dg::Timer ti;
        ti.tic();
        for( unsigned j=0; j<p.itstp; j++)
        {
            karniadakis.step( shu, diff, time, y0);//one step further
            output1d[0] = vorticity = dg::blas2::dot( one , w2d, y0);
            output1d[1] = enstrophy = 0.5*dg::blas2::dot( y0, w2d, y0);
            potential = shu.potential();
            output1d[2] = energy    = 0.5*dg::blas2::dot( y0, w2d, potential) ;
            shu.arakawa().variation(potential, varphi);
            output1d[3] = variation = dg::blas2::dot( varphi, w2d, one );
            Estart[0] += 1;
            for( int k=0;k<4; k++)
                err = nc_put_vara_double( ncid, variableIDs[k], Estart, Ecount, &output1d[k] );
            err = nc_put_vara_double( ncid, EtimevarID, Estart, Ecount, &time);
            if( energy>1e6) throw dg::Fail(p.eps);
        }
        step+=p.itstp;
        //output all fields
        dg::blas1::transfer( y0, output[0]);
        dg::blas1::transfer( shu.potential(), output[1]);
        start[0] = i;
        for( int k=0;k<2; k++)
            err = nc_put_vara_double( ncid, dataIDs[k], start, count, output[k].data() );
        err = nc_put_vara_double( ncid, tvarID, start, count, &time);
        ti.toc();
        std::cout << "\n\t Step "<<step <<" of "<<p.itstp*p.maxout <<" at time "<<time;
        std::cout << "\n\t Average time for one step: "<<ti.diff()/(double)p.itstp<<"s\n\n"<<std::flush;
    }
    }
    catch( dg::Fail& fail) { 
        std::cerr << "CG failed to converge to "<<fail.epsilon()<<"\n";
        std::cerr << "Does Simulation respect CFL condition?\n";
    }
    err = nc_close(ncid);

    return 0;

}
