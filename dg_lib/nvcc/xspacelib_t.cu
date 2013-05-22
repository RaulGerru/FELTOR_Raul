#include <iostream>

#include "xspacelib.cuh"
#include "cg.cuh"

const unsigned n=5;


double sine( double x, double y){ return 2.*sin(x)*sin(y);}
double solution( double x, double y){ return sin(x)*sin(y);}

using namespace std;
using namespace dg;

int main()
{
    const dg::Grid<double, n> grid( 0, 2.*M_PI, 0, 2.*M_PI, 80, 80, dg::DIR, dg::PER);
    const double eps = 1e-9;

    DVec b = dg::evaluate( sine, grid), x( b.size(), 0);
    const DVec sol = evaluate( solution, grid);
    W2D<double,n> w2d(grid.hx(), grid.hy());
    V2D<double,n> v2d(grid.hx(), grid.hy());

    Polarisation2dX<double, n, DVec> polarisation ( grid);
    DMatrix laplace = create::laplacian( grid, false);
    CG<DMatrix, DVec, V2D<double, n> > cg( x, x.size());
    cout << "Test of w2d: "<<blas2::dot( w2d, b)<<endl;
    blas2::symv( w2d, b, b);
    cout << "Test of v2d: "<<blas2::dot( v2d, b)<<endl;
    cg( laplace, x, b, v2d, eps);
    blas1::axpby( 1., x, -1, sol, x);
    cout << "Norm "<< nrml2(x, grid)<<endl;
    cout << "Rel error "<<nrml2( x, grid)/nrml2( sol, grid)<<endl;
    cout << "Integral "<< integ(x, grid)<<endl;
    cout << "Bracket "<< dot(sol,sol, grid)<<endl;
    cout << "Rel error "<<(dot(sol,sol,grid)-M_PI*M_PI)/M_PI/M_PI<<endl;
    return 0;
}
