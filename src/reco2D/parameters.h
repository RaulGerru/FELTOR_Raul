#pragma once
#include "dg/enums.h"
#include "json/json.h"

namespace asela{
/**
 * @brief Provide a mapping between input file and named parameters
 */
struct Parameters
{
    unsigned n; //!< \# of polynomial coefficients in R and Z
    unsigned Nx; //!< \# of cells in x -direction
    unsigned Ny; //!< \# of cells in y -direction

    double dt;  //!< timestep
    unsigned n_out;  //!< \# of polynomial coefficients in output file
    unsigned Nx_out;  //!< \# of cells in x-direction in output file
    unsigned Ny_out; //!< \# of cells in y-direction in output file
    double lxhalf, lyhalf;
    double eps_pol;  //!< accuracy of polarization
    double jfactor; //jump factor € [1,0.01]
    double eps_maxwell; //!< accuracy of induction equation
    double eps_gamma; //!< accuracy of gamma operator
    double eps_time;//!< accuracy of implicit timestep
    double eps_hat;//!< 1

    double mu[2]; //!< mu[0] = mu_e, m[1] = mu_i
    double tau[2]; //!< tau[0] = -1, tau[1] = tau_i
    double beta; //!< plasma beta

    double nu_perp;  //!< perpendicular diffusion
    double amp0;
    double amp1;
    double mY; //!< perpendicular position relative to box height
    unsigned init;

    Parameters( const Json::Value& js) {
        n       = js["n"].asUInt();
        Nx      = js["Nx"].asUInt();
        Ny      = js["Ny"].asUInt();
        dt      = js["dt"].asDouble();
        n_out   = js["n_out"].asUInt();
        Nx_out  = js["Nx_out"].asUInt();
        Ny_out  = js["Ny_out"].asUInt();


        lxhalf = js["lxhalf"].asDouble();
        lyhalf = js["lyhalf"].asDouble();
        eps_pol     = js["eps_pol"].asDouble();
        jfactor     = js["jumpfactor"].asDouble();
        eps_maxwell = js["eps_maxwell"].asDouble();
        eps_gamma   = js["eps_gamma"].asDouble();
        eps_time    = js["eps_time"].asDouble();
        eps_hat     = 1.;

        mu[0]       = js["mu"].asDouble();
        mu[1]       = +1.;
        tau[0]      = -1.;
        tau[1]      = js["tau"].asDouble();
        beta        = js["beta"].asDouble();
        nu_perp     = js["nu_perp"].asDouble();

        amp0         = js["amplitude0"].asDouble();
        amp1         = js["amplitude1"].asDouble();
        mY          = js["mY"].asDouble();
        init        = js["initmode"].asUInt();

    }
};

}//namespace eule

