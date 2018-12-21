#include <iostream>
#include <iomanip>
#include <functional>

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

#include "backend/typedefs.h"
#include "topology/evaluation.h"
#include "arakawa.h"
#include "runge_kutta.h"


//![function]
void rhs(double t, const std::array<double,2>& y, std::array<double,2>& yp, double damping, double omega_0, double omega_drive){
    //damped driven harmonic oscillator
    // x -> y[0] , v -> y[1]
    yp[0] = y[1];
    yp[1] = -2.*damping*omega_0*y[1] - omega_0*omega_0*y[0] + sin(omega_drive*t);
}
//![function]

std::array<double, 2> solution( double t, double damping, double omega_0, double omega_drive)
{
    double tmp1 = (2.*omega_0*damping);
    double tmp2 = (omega_0*omega_0 - omega_drive*omega_drive)/omega_drive;
    double amp = 1./sqrt( tmp1*tmp1 + tmp2*tmp2);
    double phi = atan( 2.*omega_drive*omega_0*damping/(omega_drive*omega_drive-omega_0*omega_0));

    double x = amp*sin(omega_drive*t+phi)/omega_drive;
    double v = amp*cos(omega_drive*t+phi);
    return {x,v};
}

int main()
{
    std::cout << "Program to test correct implementation of Runge Kutta methods in runge_kutta.h at the example of the damped driven harmonic oscillator. Errors should be small! \n";
    std::cout << std::scientific;
    //![doxygen]
    //... in main
    //set start and end time, number of steps and timestep
    const double t_start = 0., t_end = 1.;
    const unsigned N = 40;
    const double dt = (t_end - t_start)/(double)N;
    //set physical parameters and initial condition
    const double damping = 0.2, omega_0 = 1.0, omega_drive = 0.9;
    std::array<double,2> u = solution(t_start, damping, omega_0, omega_drive);
    //construct Runge Kutta class
    dg::RungeKutta<std::array<double,2> >  rk( "Runge-Kutta-4-4", u);
    //construct a functor with the right interface
    using namespace std::placeholders; //for _1, _2, _3
    auto functor = std::bind( rhs, _1, _2, _3, damping, omega_0, omega_drive);
    //integration loop
    double t=t_start;
    for( unsigned i=0; i<N; i++)
        rk.step( functor, t, u, t, u, dt); //step inplace
    //now compute error
    dg::blas1::axpby( 1., solution(t_end, damping, omega_0, omega_drive), -1., u);
    std::cout << "Norm of error is "<<sqrt(dg::blas1::dot( u, u))<<"\n";
    //![doxygen]
    std::vector<std::string> names{
        "Euler",
        "Midpoint-2-2",
        "Kutta-3-3",
        "Runge-Kutta-4-4",
        "Heun-Euler-2-1-2",
        "Bogacki-Shampine-4-2-3",
        "ARK-4-2-3 (explicit)",
        "Zonneveld-5-3-4",
        "ARK-6-3-4 (explicit)",
        "Sayfy-Aburub-6-3-4",
        "Cash-Karp-6-4-5",
        "Fehlberg-6-4-5",
        "Dormand-Prince-7-4-5",
        "ARK-8-4-5 (explicit)",
        "Verner-8-5-6",
        "Fehlberg-13-7-8",
        "Feagin-17-8-10"
    };
    for( auto name : names)
    {
        u = solution(t_start, damping, omega_0, omega_drive);
        std::array<double, 2> u1(u), sol = solution(t_end, damping, omega_0, omega_drive);
        dg::stepperRK(name, functor, t_start, u, t_end, u1, N);
        dg::blas1::axpby( 1., sol , -1., u1);
        std::cout << "Norm of error in "<<std::setw(24) <<name<<"\t"<<sqrt(dg::blas1::dot( u1, u1))<<"\n";
    }
    return 0;
}