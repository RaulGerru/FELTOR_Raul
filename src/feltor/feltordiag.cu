#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <functional>
#include "json/json.h"
#include "dg/algorithm.h" 
#include "dg/geometries/geometries.h"
#include "dg/file/file.h"
using HVec = dg::HVec; 
using DVec = dg::DVec;   
using DMatrix = dg::DMatrix;   
using IDMatrix = dg::IDMatrix;
using IHMatrix = dg::IHMatrix;
using Geometry = dg::CylindricalGrid3d;
#define MPI_OUT
#include "feltordiag.h" 
     
    
int main( int argc, char* argv[])
{
    if( argc < 3)
    {
        std::cerr << "Usage: "<<argv[0]<<" [input0.nc ... inputN.nc] [output.nc]\n";
        return -1;
    }
    for( int i=1; i<argc-1; i++)
        std::cout << argv[i]<< " ";
    std::cout << " -> "<<argv[argc-1]<<std::endl;

    //------------------------open input nc file--------------------------------//
    file::NC_Error_Handle err;
    int ncid_in;
    err = nc_open( argv[1], NC_NOWRITE, &ncid_in); //open 3d file
    size_t length;
    err = nc_inq_attlen( ncid_in, NC_GLOBAL, "inputfile", &length);
    std::string inputfile(length, 'x');
    err = nc_get_att_text( ncid_in, NC_GLOBAL, "inputfile", &inputfile[0]);
    err = nc_inq_attlen( ncid_in, NC_GLOBAL, "geomfile", &length);
    std::string geomfile(length, 'x');
    err = nc_get_att_text( ncid_in, NC_GLOBAL, "geomfile", &geomfile[0]);
    err = nc_close( ncid_in);
    Json::Value js,gs;
    file::string2Json(inputfile, js, file::comments::are_forbidden);
    file::string2Json(geomfile, gs, file::comments::are_forbidden);
    //we only need some parameters from p, not all
    const feltor::Parameters p(js, file::error::is_warning);
    const dg::geo::solovev::Parameters gp(gs);
    p.display();
    gp.display();
    std::vector<std::string> names_input{
        "electrons", "ions", "Ue", "Ui", "potential", "induction"
    };
 
    //-----------------Create Netcdf output file with attributes----------//
    int ncid_out;
    err = nc_create(argv[argc-1],NC_NETCDF4|NC_CLOBBER, &ncid_out);

    /// Set global attributes
    std::map<std::string, std::string> att;
    att["title"] = "Output file of feltor/src/feltor/feltordiag.cu";
    att["Conventions"] = "CF-1.7";
    ///Get local time and begin file history
    auto ttt = std::time(nullptr);
    auto tm = *std::localtime(&ttt);
    std::ostringstream oss;
    ///time string  + program-name + args
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    for( int i=0; i<argc; i++) oss << " "<<argv[i];
    att["history"] = oss.str();
    att["comment"] = "Find more info in feltor/src/feltor.tex";
    att["source"] = "FELTOR";
    att["references"] = "https://github.com/feltor-dev/feltor";
    att["inputfile"] = inputfile;
    att["geomfile"] = geomfile;
    for( auto pair : att)
        err = nc_put_att_text( ncid_out, NC_GLOBAL,
            pair.first.data(), pair.second.size(), pair.second.data());

    //-------------------Construct grids-------------------------------------//
  
    const double Rmin=gp.R_0-p.boxscaleRm*gp.a;
    const double Zmin=-p.boxscaleZm*gp.a*gp.elongation;
    const double Rmax=gp.R_0+p.boxscaleRp*gp.a;
    const double Zmax=p.boxscaleZp*gp.a*gp.elongation;

    dg::Grid2d   g2d_out( Rmin,Rmax, Zmin,Zmax,
        p.n_out, p.Nx_out, p.Ny_out, p.bcxN, p.bcyN);
 
    dg::geo::TokamakMagneticField mag = dg::geo::createSolovevField(gp);
    double RO=mag.R0(), ZO=0.;
    dg::geo::findOpoint( mag.get_psip(), RO, ZO);
    const double psipO = mag.psip()( RO, ZO);
    if( p.damping_alpha > 0.) 
    {  
        double damping_psi0 = (1.-p.damping_boundary*p.damping_boundary)*psipO;
        double damping_alpha = -(2.*p.damping_boundary+p.damping_alpha)*p.damping_alpha*psipO;
        mag = dg::geo::createModifiedSolovevField(gp, damping_psi0+damping_alpha/2.,
                fabs(p.damping_alpha/2.), ((psipO>0)-(psipO<0)));
    } 
    dg::HVec psipog2d = dg::evaluate( mag.psip(), g2d_out);
    // Construct weights and temporaries

    dg::HVec transferH2d = dg::evaluate(dg::zero,g2d_out);
    dg::HVec t2d_mp = dg::evaluate(dg::zero,g2d_out);
       
    ///---------------  Construct X-point grid ---------------------//
         
       
    //std::cout << "Type X-point grid resolution (n(3), Npsi(32), Neta(640)) Must be divisible by 8\n";
    std::cout << "Using default X-point grid resolution (n(3), Npsi(64), Neta(640))\n";
    unsigned npsi = 3, Npsi = 64, Neta =160;//set number of psivalues (NPsi % 8 == 0)
    //std::cin >> npsi >> Npsi >> Neta;
    std::cout << "You typed "<<npsi<<" x "<<Npsi<<" x "<<Neta<<"\n";
    std::cout << "Generate X-point flux-aligned grid!\n";
    double R_X = gp.R_0-1.1*gp.triangularity*gp.a; 
    double Z_X = -1.1*gp.elongation*gp.a;
    dg::geo::findXpoint( mag.get_psip(), R_X, Z_X);
    dg::geo::CylindricalSymmTensorLvl1 monitor_chi = dg::geo::make_Xconst_monitor( mag.get_psip(), R_X, Z_X) ;
    dg::geo::SeparatrixOrthogonal generator(mag.get_psip(), monitor_chi, psipO, R_X, Z_X, mag.R0(), 0, 0, false);
    double fx_0 = 1./8.;
    double psipmax = dg::blas1::reduce( psipog2d, 0. ,thrust::maximum<double>()); //DEPENDS ON GRID RESOLUTION!!
    std::cout << "psi max is            "<<psipmax<<"\n";
    psipmax = -fx_0/(1.-fx_0)*psipO;
    std::cout << "psi max in g1d_out is "<<psipmax<<"\n";
    dg::geo::CurvilinearGridX2d gridX2d( generator, fx_0, 0., npsi, Npsi, Neta, dg::DIR_NEU, dg::NEU);
    std::cout << "psi max in gridX2d is "<<gridX2d.x1()<<"\n";
    std::cout << "psi min in gridX2d is "<<gridX2d.x0()<<"\n";
    std::cout << "eta max in gridX2d is "<<gridX2d.y1()<<"\n";
    std::cout << "eta min in gridX2d is "<<gridX2d.y0()<<"\n"; 
    std::cout << "DONE!\n"; 
    //Create 1d grid  
    dg::Grid1d g1d_out(psipO, psipmax, 3, Npsi, dg::DIR_NEU); //inner value is always 0
    const double f0 = ( gridX2d.x1() - gridX2d.x0() ) / ( psipmax - psipO );
    std::cout << "f0 is "<<f0<<"\n";
    dg::HVec t1d = dg::evaluate( dg::zero, g1d_out), fsa1d( t1d);
    dg::HVec transfer1d = dg::evaluate(dg::zero,g1d_out);
    
              
    /// ------------------- Compute 1d flux labels ---------------------//
      
    std::vector<std::tuple<std::string, dg::HVec, std::string> > map1d;
    /// Compute flux volume label
    dg::Average<dg::HVec > poloidal_average( gridX2d.grid(), dg::coo2d::y);
    //metric and map  
    dg::SparseTensor<dg::HVec> metricX = gridX2d.metric();
    std::vector<dg::HVec > coordsX = gridX2d.map();
    dg::HVec volX2d = dg::tensor::volume2d( metricX); 
    dg::blas1::pointwiseDot( coordsX[0], volX2d, volX2d); //R\sqrt{g}   
    dg::HVec dvdpsip, transferH2dX(volX2d);
    poloidal_average( volX2d,dvdpsip, false);  
    dg::blas1::scal( dvdpsip, 4.*M_PI*M_PI*f0);  	    
    map1d.emplace_back( "dvdpsi", dvdpsip,
        "Derivative of flux volume with respect to flux label psi");
    dg::HVec X_psi_vol = dg::integrate(dvdpsip, g1d_out);
    map1d.emplace_back( "psi_vol", X_psi_vol,
        "Flux volume evaluated with X-point grid");
    
    /// Compute flux area label
    dg::HVec gradZetaX = metricX.value(0,0), X_psi_area;
    dg::blas1::transform( gradZetaX, gradZetaX, dg::SQRT<double>());
    dg::blas1::pointwiseDot( volX2d, gradZetaX, gradZetaX); //R\sqrt{g}|\nabla\zeta|
    poloidal_average( gradZetaX, X_psi_area, false);
    dg::blas1::scal( X_psi_area, 4.*M_PI*M_PI);
    map1d.emplace_back( "psi_area", X_psi_area,
        "Flux area evaluated with X-point grid");

    dg::HVec rho = dg::evaluate( dg::cooX1d, g1d_out);
    dg::blas1::axpby( -1./psipO, rho, +1., 1., rho); //transform psi to rho
    map1d.emplace_back("rho", rho,
        "Alternative flux label rho = 1-psi/psimin");
    dg::blas1::transform( rho, rho, dg::SQRT<double>());
    map1d.emplace_back("rho_p", rho,
        "Alternative flux label rho_p = sqrt(1-psi/psimin)"); 
    dg::geo::SafetyFactor qprof( mag);
    dg::HVec qprofile = dg::evaluate( qprof, g1d_out);
    map1d.emplace_back("q-profile", qprofile,
        "q-profile (Safety factor) using direct integration");
    map1d.emplace_back("psi_psi",    dg::evaluate( dg::cooX1d, g1d_out),
        "Poloidal flux label psi (same as coordinate)");
    dg::HVec psit = dg::integrate( qprofile, g1d_out);
    map1d.emplace_back("psit1d", psit,
        "Toroidal flux label psi_t integrated using q-profile");
    //we need to avoid integrating >=0 for total psi_t
    dg::Grid1d g1d_fine(psipO<0. ? psipO : 0., psipO<0. ? 0. : psipO, 3 ,Npsi,dg::DIR_NEU);
    qprofile = dg::evaluate( qprof, g1d_fine);
    dg::HVec w1d = dg::create::weights( g1d_fine);
    double psit_tot = dg::blas1::dot( w1d, qprofile);
    dg::blas1::scal ( psit, 1./psit_tot);
    dg::blas1::transform( psit, psit, dg::SQRT<double>());
    map1d.emplace_back("rho_t", psit,
        "Toroidal flux label rho_t = sqrt( psit/psit_tot)");

    // interpolate from 2d grid to X-point points
    dg::IHMatrix grid2gridX2d  = dg::create::interpolation(
        coordsX[0], coordsX[1], g2d_out);
    // interpolate fsa back to 2d or 3d grid
    dg::IHMatrix fsa2rzmatrix = dg::create::interpolation(
        psipog2d, g1d_out, dg::DIR_NEU);

    dg::HVec dvdpsip2d = dg::evaluate( dg::zero, g2d_out);
    dg::blas2::symv( fsa2rzmatrix, dvdpsip, dvdpsip2d);
    dg::HMatrix dpsi = dg::create::dx( g1d_out, dg::DIR_NEU);
 
 
/// ------------------- NEW:Partial FSA and CONVOLUTION elements ---------------------//
   
   
    double eta_0=3*M_PI/2; //NEW: Defining center of partial fsa
    double eta_range=90.; //NEW: Defining the poloidal range of partial fsa 
	double conv_window=7.5; // NEW: Window for the convolution function    
    double radial_cut_point=0.; //NEW: Radial position where we will like to do the cut of the 1D convolution
       
    //NEW DATA AND GRID DEFINITIONS    
    dg::HVec  part_volX2d(volX2d), conv_volX2d(volX2d); //NEW: Grids for the partial fsa and the convoluted grid
    dg::HVec part_transferH2dX(volX2d), preconv_transferH2dX(volX2d), conv_def_transferH2dX(volX2d), post_conv_def_transferH2dX(volX2d); //NEW:
    dg::Grid1d g1d_out_eta(gridX2d.y0(), gridX2d.y1(), 3, Neta, dg::DIR_NEU); ////NEW 1D grid for the eta (poloidal) directions instead of psi  
    //Definitions of partial fsa DATA, The DATA matrix to do the convolution on, which is divided by the convoluted grid, THe convoluted DATA matrix and the convoluted data matrix over which we are going to make the fsa to compare with the original one.
    dg::HVec part_t1d(t1d), part_fsa1d(t1d), conv_fsa(t1d), conv_LCFS_1d=dg::evaluate( dg::zero, g1d_out_eta), LCFS_1d=dg::evaluate( dg::zero, g1d_out_eta); //NEW:
    // Definition of partial fsa1d, the fsa of the convolution, the radial cut of the convolution and of the original quantity (called LCFS as it is where we are usually interested)

	
    //NEW: Initialization of CONVOLUTION functor   
	dg::geo::Convolution_def conv(conv_window, gridX2d);
	conv_volX2d=conv.convoluted_grid();//NEW: Save the convoluted Grid	   
	dg::blas1::pointwiseDot(part_volX2d, dg::evaluate(dg::geo::Grid_cutter(eta_0, eta_range), gridX2d.grid()), part_volX2d); //NEW: Define the cutted grid por the partial fsa

///---------------- End of FSA and CONVOLUTION definitions ---------------------///
 
    // define 2d and 1d and 0d dimensions and variables
    int dim_ids[3], tvarID;
    err = file::define_dimensions( ncid_out, dim_ids, &tvarID, g2d_out);
    //Write long description
    std::string long_name = "Time at which 2d fields are written";
    err = nc_put_att_text( ncid_out, tvarID, "long_name", long_name.size(),
            long_name.data());
          
    int dim_ids1d[2] = {dim_ids[0], 0}; //time,  psi
    err = file::define_dimension( ncid_out, &dim_ids1d[1], g1d_out, {"psi"} ); 
    std::map<std::string, int> id0d, id1d, id2d, id2dX;

    size_t count1d[2] = {1, g1d_out.n()*g1d_out.N()};
    size_t count2d[3] = {1, g2d_out.n()*g2d_out.Ny(), g2d_out.n()*g2d_out.Nx()};
    size_t count2d_X[3]= {1, gridX2d.n()*gridX2d.Ny(), gridX2d.n()*gridX2d.Nx()};
    size_t start2d[3] = {0, 0, 0};
    
    
	size_t count1d_conv[2] = {1, gridX2d.n()*gridX2d.Ny()}; //NEW convolution variables for the plot (eta and eta, psi2)
    int partial_dim_idsX[2]={0,0};
    err = file::define_dimensions(ncid_out, partial_dim_idsX,  gridX2d.grid(), {"eta", "psi2"});  //NEW definition of the names of the new coordinates
    int dim_idsX[3]={dim_ids[0], partial_dim_idsX[0], partial_dim_idsX[1]};
 
   
		long_name = "Flux surface label";
        err = nc_put_att_text( ncid_out, dim_idsX[1], "long_name",
            long_name.size(), long_name.data()); //NEW Description new coordinate
        long_name = "Flux angle";
        err = nc_put_att_text( ncid_out, dim_idsX[2], "long_name",
            long_name.size(), long_name.data()); //NEW Description new coordinate
        
                   
        err = nc_def_var( ncid_out, "xcc", NC_DOUBLE, 3, dim_idsX, &id2dX["xcc"]);
		long_name="Cartesian x-coordinate";
        err = nc_put_att_text( ncid_out, id2dX["xcc"], "long_name",
            long_name.size(), long_name.data()); //NEW variable for the transformation from X-grid to the Z, R grid
        err = nc_def_var( ncid_out, "ycc", NC_DOUBLE, 3, dim_idsX, &id2dX["ycc"]);
        long_name="Cartesian y-coordinate"; //NEW variable for the transformation from X-grid to the Z, R grid
        err = nc_put_att_text( ncid_out, id2dX["ycc"], "long_name",
            long_name.size(), long_name.data());
            
        err = nc_def_var( ncid_out, "volX2d_sqrt(g)", NC_DOUBLE, 3, dim_idsX, &id2dX["volX2d_sqrt(g)"]);
		long_name="Volume matrix_sqrt(g)"; //NEW? To save the volume matrix
        err = nc_put_att_text( ncid_out, id2dX["volX2d_sqrt(g)"], "long_name",
            long_name.size(), long_name.data());
            
         err = nc_def_var( ncid_out, "conv_volX2d_sqrt(g)", NC_DOUBLE, 3, dim_idsX, &id2dX["conv_volX2d_sqrt(g)"]);
		long_name="Convoluted_Volume matrix_sqrt(g)"; //NEW: To save the convoluted volume matrix 
        err = nc_put_att_text( ncid_out, id2dX["conv_volX2d_sqrt(g)"], "long_name",
            long_name.size(), long_name.data());
            
            
       dg::HVec eta_c=dg::evaluate( dg::cooX1d, g1d_out_eta);
       std::string  name = "eta_coord"; //NEW variable to plot in the x axis the eta 1D coordinate
       err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 2, dim_idsX,
            &id2dX[name]);          
       long_name = "Poloidal coordinate";
		err = nc_put_att_text( ncid_out, id2dX[name], "long_name", long_name.size(),
            long_name.data());

    //write 1d static vectors (psi, q-profile, ...) into file
    for( auto tp : map1d)
    {
        int vid;
        err = nc_def_var( ncid_out, std::get<0>(tp).data(), NC_DOUBLE, 1,
            &dim_ids1d[1], &vid);
        err = nc_put_att_text( ncid_out, vid, "long_name",
            std::get<2>(tp).size(), std::get<2>(tp).data());
        err = nc_enddef( ncid_out);
        err = nc_put_var_double( ncid_out, vid, std::get<1>(tp).data());
        err = nc_redef(ncid_out);
    }

    for( auto& record : feltor::diagnostics2d_list)
    {
        std::string record_name = record.name;
        if( record_name[0] == 'j')
            record_name[1] = 'v';
        name = record_name + "_fluc2d";
        long_name = record.long_name + " (Fluctuations wrt fsa on phi = 0 plane.)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 3, dim_ids,
            &id2d[name]);
        err = nc_put_att_text( ncid_out, id2d[name], "long_name", long_name.size(),
            long_name.data());

        name = record_name + "_fsa2d";
        long_name = record.long_name + " (Flux surface average interpolated to 2d plane.)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 3, dim_ids,
            &id2d[name]);
        err = nc_put_att_text( ncid_out, id2d[name], "long_name", long_name.size(),
            long_name.data());
       
       
        if( record_name[0] == 'j'){ //NEW DEFINITION OF VARIABLE FOR CONVOLUTED CURRENTS ONLY (J's)
			name = record_name + "_conv2d"; //NEW Convoluted matrix in the X-grid
        long_name = record.long_name + " (2d values convoluted in 'small' angles.)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 3, dim_idsX,
            &id2dX[name]);
        err = nc_put_att_text( ncid_out, id2dX[name], "long_name", long_name.size(),
            long_name.data()); 		
            
        name = record_name + "_Xgrid"; //NEW Original total data in the X-grid
        long_name = record.long_name + " (Toroidal average in the X grid)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 3, dim_idsX,
            &id2dX[name]);
        err = nc_put_att_text( ncid_out, id2dX[name], "long_name", long_name.size(),
            long_name.data()); 
            
        name = record_name + "_conv1d_LCFS"; //NEW Variable for the radial cut of the convoluted variable
        long_name = record.long_name + " (1D Fluxes at LCFS, poloidal distribution of convolution)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 2, dim_idsX,
            &id2dX[name]);
        err = nc_put_att_text( ncid_out, id2dX[name], "long_name", long_name.size(),
            long_name.data()); 	
            
        name = record_name + "_1d_LCFS"; //NEW Variable for the radial cut of the original data
        long_name = record.long_name + " (1D Fluxes at LCFS)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 2, dim_idsX,
            &id2dX[name]);
        err = nc_put_att_text( ncid_out, id2dX[name], "long_name", long_name.size(),
            long_name.data()); 
            
        name = record_name + "_fsa_conv"; //NEW Variable for the fsa of the convoluted data
        long_name = record.long_name + " (Flux surface average of convolution)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 2, dim_ids1d,
            &id1d[name]);
        err = nc_put_att_text( ncid_out, id1d[name], "long_name", long_name.size(),
            long_name.data()); 	
        
        /*     
        name = record_name + "_partX2d";// NEW THe cutted grid for the partial fsa in the X-Grid
        long_name = record.long_name + " (2d partial fsa in X_grid.)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 3, dim_idsX,
            &id2dX[name]);
        err = nc_put_att_text( ncid_out, id2dX[name], "long_name", long_name.size(),
            long_name.data()); 	
         */
		}  
 
        name = record_name + "_fsa"; 
        long_name = record.long_name + " (Flux surface average.)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 2, dim_ids1d,
            &id1d[name]);
        err = nc_put_att_text( ncid_out, id1d[name], "long_name", long_name.size(),
            long_name.data());
            
                name = record_name + "_part_fsa_at_"+std::to_string(eta_0)+"_"+std::to_string(eta_range); //NEW partial fsa at the position defined
        long_name = record.long_name + " (Partial Flux surface average.)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 2, dim_ids1d,
            &id1d[name]);
        err = nc_put_att_text( ncid_out, id1d[name], "long_name", long_name.size(),
            long_name.data());

        name = record_name + "_ifs";
        long_name = record.long_name + " (wrt. vol integrated flux surface average)";
        if( record_name[0] == 'j')
            long_name = record.long_name + " (wrt. vol derivative of the flux surface average)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 2, dim_ids1d,
            &id1d[name]);
        err = nc_put_att_text( ncid_out, id1d[name], "long_name", long_name.size(),
            long_name.data());

        name = record_name + "_ifs_lcfs";
        long_name = record.long_name + " (wrt. vol integrated flux surface average evaluated on last closed flux surface)";
        if( record_name[0] == 'j')
            long_name = record.long_name + " (flux surface average evaluated on the last closed flux surface)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 1, dim_ids,
            &id0d[name]);
        err = nc_put_att_text( ncid_out, id0d[name], "long_name", long_name.size(),
            long_name.data());

        name = record_name + "_ifs_norm";
        long_name = record.long_name + " (wrt. vol integrated square flux surface average from 0 to lcfs)";
        if( record_name[0] == 'j')
            long_name = record.long_name + " (wrt. vol integrated square derivative of the flux surface average from 0 to lcfs)";
        err = nc_def_var( ncid_out, name.data(), NC_DOUBLE, 1, dim_ids,
            &id0d[name]);
        err = nc_put_att_text( ncid_out, id0d[name], "long_name", long_name.size(),
            long_name.data());
    } 
    /////////////////////////////////////////////////////////////////////////
    size_t counter = 0;
    int ncid;
    for( int j=1; j<argc-1; j++)
    {
        int timeID;

        size_t steps;
        std::cout << "Opening file "<<argv[j]<<"\n";
        try{
            err = nc_open( argv[j], NC_NOWRITE, &ncid); //open 3d file
        } catch ( file::NC_Error& error)
        {
            std::cerr << "An error occurded opening file "<<argv[j]<<"\n";
            std::cerr << error.what()<<std::endl;
            std::cerr << "Continue with next file\n";
            continue;
        }
        err = nc_inq_unlimdim( ncid, &timeID); //Attention: Finds first unlimited dim, which hopefully is time and not energy_time
        err = nc_inq_dimlen( ncid, timeID, &steps);
        //steps = 3;
        for( unsigned i=0; i<steps; i++)//timestepping
        {
            if( j > 1 && i == 0)
                continue; // else we duplicate the first timestep
            start2d[0] = i;
            size_t start2d_out[3] = {counter, 0,0};
            size_t startX2d_out[3] = {counter, 0,0}; //NEW For the time of the convoluted output (Not sure if neccesary)
            size_t start1d_out[2] = {counter, 0};
            // read and write time
            double time=0.;
            err = nc_get_vara_double( ncid, timeID, start2d, count2d, &time);
            std::cout << counter << " Timestep = " << i <<"/"<<steps-1 << "  time = " << time << std::endl;
            counter++;
            err = nc_put_vara_double( ncid_out, tvarID, start2d_out, count2d, &time);
            err = nc_put_vara_double( ncid_out, tvarID, startX2d_out, count2d_X, &time);

             for( auto& record : feltor::diagnostics2d_list)
            {
                std::string record_name = record.name;
                if( record_name[0] == 'j')
                    record_name[1] = 'v';
                //1. Read toroidal average
                int dataID =0;
                bool available = true;
                try{
                    err = nc_inq_varid(ncid, (record.name+"_ta2d").data(), &dataID);
                } catch ( file::NC_Error& error)
                { 
                    if(  i == 0)
                    { 
                        std::cerr << error.what() <<std::endl;
                        std::cerr << "Offending variable is "<<record.name+"_ta2d\n";
                        std::cerr << "Writing zeros ... \n";
                    }
                    available = false;
                }
                if( available)
                {  
                    err = nc_get_vara_double( ncid, dataID,
                        start2d, count2d, transferH2d.data());
           
                    //2. Compute fsa, partial fsa and output fsa and partial fsa
                    
                    dg::blas2::symv( grid2gridX2d, transferH2d, transferH2dX); //interpolate onto X-point grid. a.k.a Define the data in the X-grid                   
                    part_transferH2dX=transferH2dX; //NEW: Define the data matrices that we are going to edit for the partial fsa and the convolution
                    
                    //ORIGINAL FSA
                    dg::blas1::pointwiseDot( transferH2dX, volX2d, transferH2dX); //multiply by sqrt(g)   
                    poloidal_average( transferH2dX, t1d, false); //average over eta
                    dg::blas1::scal( t1d, 4*M_PI*M_PI*f0); //
                    dg::blas1::pointwiseDivide( t1d, dvdpsip, fsa1d );
                    
                    //NEW Partial FSA
                    dg::blas1::pointwiseDot( part_transferH2dX, part_volX2d, part_transferH2dX);  
                    poloidal_average( part_transferH2dX, part_t1d, false);
                    dg::blas1::scal( part_t1d, 4*M_PI*M_PI*f0); 
                    dg::blas1::scal(part_t1d, 360/eta_range); //NEW: Normalization factor (explained in feltor.pdf)
                    dg::blas1::pointwiseDivide( part_t1d, dvdpsip, part_fsa1d ); 
                    
                    if( record_name[0] == 'j'){
                        dg::blas1::pointwiseDot( fsa1d, dvdpsip, fsa1d );
                        dg::blas1::pointwiseDot( part_fsa1d, dvdpsip, part_fsa1d ); 

						//NEW: Define the function to be convoluted dividing the data (already multiplied by sqrt(g)) by the convoluted volume
                        dg::blas1::pointwiseDivide(transferH2dX, conv_volX2d, preconv_transferH2dX);

                        //NEW: Make the convolution
                        conv_def_transferH2dX=conv.convolute(preconv_transferH2dX);
                        
                        //NEW: Do the FSA of the convoluted data
                        dg::blas1::pointwiseDot( conv_def_transferH2dX, volX2d, post_conv_def_transferH2dX);   
						poloidal_average(post_conv_def_transferH2dX, conv_fsa, false);
						dg::blas1::scal( conv_fsa, 4*M_PI*M_PI*f0);
                    
						//NEW: We obtain a radial cut of the convoluted data
						conv_LCFS_1d=conv.radial_cut(conv_def_transferH2dX, radial_cut_point);
						dg::blas1::pointwiseDivide(transferH2dX, volX2d, transferH2dX);
						//NEW: We obtain a radial cut of the original data
						LCFS_1d=conv.radial_cut(transferH2dX, radial_cut_point);
                               
					} 
                    //3. Interpolate fsa on 2d plane : <f>
                    dg::blas2::gemv(fsa2rzmatrix, fsa1d, transferH2d); //fsa on RZ grid //IT SHOULD BE WITHOUT X
                } 
                else
                {
                    dg::blas1::scal( fsa1d, 0.);
                    dg::blas1::scal( part_fsa1d, 0.);
                    dg::blas1::scal( transferH2d, 0.);
                } 
                err = nc_put_vara_double( ncid_out, id1d.at(record_name+"_fsa"),
                    start1d_out, count1d, fsa1d.data());
                err = nc_put_vara_double( ncid_out, id1d.at(record_name+"_part_fsa_at_"+std::to_string(eta_0)+"_"+std::to_string(eta_range)),
                    start1d_out, count1d, part_fsa1d.data()); //NEW: Save the partial fsa data
                err = nc_put_vara_double( ncid_out, id2d.at(record_name+"_fsa2d"),
                    start2d_out, count2d, transferH2d.data() ); 
                    
                if( record_name[0] == 'j'){ //NEW: Saving the new already defined variables 
				err = nc_put_vara_double( ncid_out, id2dX.at(record_name+"_conv2d"),
                startX2d_out, count2d_X, conv_def_transferH2dX.data() ); 
                
                err = nc_put_vara_double( ncid_out, id2dX.at(record_name+"_Xgrid"),
                startX2d_out, count2d_X, transferH2dX.data() );  
                          
                err = nc_put_vara_double( ncid_out, id2dX.at(record_name+"_conv1d_LCFS"),
                start1d_out, count1d_conv, conv_LCFS_1d.data() );  
                
                err = nc_put_vara_double( ncid_out, id2dX.at(record_name+"_1d_LCFS"),
                start1d_out, count1d_conv, LCFS_1d.data() );  

                err = nc_put_vara_double( ncid_out, id1d.at(record_name+"_fsa_conv"),
                    start1d_out, count1d, conv_fsa.data());
                
                err = nc_put_vara_double( ncid_out, id2dX["xcc"], startX2d_out, count2d_X, gridX2d.map()[0].data());//NEW SAving the maps and metrics of the new coordinates 
                err = nc_put_vara_double( ncid_out, id2dX["ycc"], startX2d_out, count2d_X, gridX2d.map()[1].data());
                err = nc_put_vara_double( ncid_out, id2dX["volX2d_sqrt(g)"], startX2d_out, count2d_X, volX2d.data());
				err = nc_put_vara_double( ncid_out, id2dX["conv_volX2d_sqrt(g)"], startX2d_out, count2d_X, conv_volX2d.data());
				err = nc_put_vara_double( ncid_out, id2dX["eta_coord"], start1d_out, count1d_conv, eta_c.data());
                                  
                /*
                err = nc_put_vara_double( ncid_out, id2dX.at(record_name+"_partX2d"),
                startX2d_out, count2d_X, part_transferH2dX.data() ); 		 
                */
				}
                
                    
                    
                //4. Read 2d variable and compute fluctuations
                available = true;
                try{
                    err = nc_inq_varid(ncid, (record.name+"_2d").data(), &dataID);
                } catch ( file::NC_Error& error)
                {
                    if(  i == 0)
                    {
                        std::cerr << error.what() <<std::endl;
                        std::cerr << "Offending variable is "<<record.name+"_2d\n";
                        std::cerr << "Writing zeros ... \n";
                    }
                    available = false;
                }
                if( available)
                {
                    err = nc_get_vara_double( ncid, dataID, start2d, count2d,
                        t2d_mp.data());  //HERE t2d_mp IS THE DATA 
                    if( record_name[0] == 'j')
                        dg::blas1::pointwiseDot( t2d_mp, dvdpsip2d, t2d_mp ); //HERE WE SIMPLY MULTIPLY BY THE DVDPSIP2D: WHY DVDPSIP2D AND NOT VOLX2d????
                    dg::blas1::axpby( 1.0, t2d_mp, -1.0, transferH2d); //HERE WE SUBSTRACT THE AVERAGE TO GET THE FLUCTUATIONS AND SAVE IT IN TRANSFER H2D
                    err = nc_put_vara_double( ncid_out, id2d.at(record_name+"_fluc2d"),
                        start2d_out, count2d, transferH2d.data() );

                    //5. flux surface integral/derivative
                    double result =0.;
                    if( record_name[0] == 'j') //j indicates a flux
                    {
                        dg::blas2::symv( dpsi, fsa1d, t1d);
                        dg::blas1::pointwiseDivide( t1d, dvdpsip, transfer1d);

                        result = dg::interpolate( dg::xspace, fsa1d, 0., g1d_out);
                    }
                    else
                    {
                        dg::blas1::pointwiseDot( fsa1d, dvdpsip, t1d);
                        transfer1d = dg::integrate( t1d, g1d_out);

                        result = dg::interpolate( dg::xspace, transfer1d, 0., g1d_out);
                    }
                    err = nc_put_vara_double( ncid_out, id1d.at(record_name+"_ifs"),
                        start1d_out, count1d, transfer1d.data());
                    //flux surface integral/derivative on last closed flux surface
                    err = nc_put_vara_double( ncid_out, id0d.at(record_name+"_ifs_lcfs"),
                        start2d_out, count2d, &result );
                    //6. Compute norm of time-integral terms to get relative importance
                    if( record_name[0] == 'j') //j indicates a flux
                    {
                        dg::blas2::symv( dpsi, fsa1d, t1d);
                        dg::blas1::pointwiseDivide( t1d, dvdpsip, t1d); //dvjv
                        dg::blas1::pointwiseDot( t1d, t1d, t1d);//dvjv2
                        dg::blas1::pointwiseDot( t1d, dvdpsip, t1d);//dvjv2
                        transfer1d = dg::integrate( t1d, g1d_out);
                        result = dg::interpolate( dg::xspace, transfer1d, 0., g1d_out);
                        result = sqrt(result);
                    }
                    else
                    {
                        dg::blas1::pointwiseDot( fsa1d, fsa1d, t1d);
                        dg::blas1::pointwiseDot( t1d, dvdpsip, t1d);
                        transfer1d = dg::integrate( t1d, g1d_out);

                        result = dg::interpolate( dg::xspace, transfer1d, 0., g1d_out);
                        result = sqrt(result);
                    }
                    err = nc_put_vara_double( ncid_out, id0d.at(record_name+"_ifs_norm"),
                        start2d_out, count2d, &result );
                }
                else
                {
                    dg::blas1::scal( transferH2d, 0.);
                    dg::blas1::scal( transfer1d, 0.);
                    double result = 0.;
                    err = nc_put_vara_double( ncid_out, id2d.at(record_name+"_fluc2d"),
                        start2d_out, count2d, transferH2d.data() );
                    err = nc_put_vara_double( ncid_out, id1d.at(record_name+"_ifs"),
                        start1d_out, count1d, transfer1d.data());
                    err = nc_put_vara_double( ncid_out, id0d.at(record_name+"_ifs_lcfs"),
                        start2d_out, count2d, &result );
                    err = nc_put_vara_double( ncid_out, id0d.at(record_name+"_ifs_norm"),
                        start2d_out, count2d, &result );
                }

            } 


        } //end timestepping
        err = nc_close(ncid);
    }
    err = nc_close(ncid_out);

    return 0;
}
