#pragma once

#include <thrust/host_vector.h>
#include "grid.h"
#include "../enums.h"

/*! @file

  * @brief contains creation functions for integration weights and their inverse
  */

namespace dg{
namespace create{
    
///@cond
/**
* @brief create host_vector containing 1d X-space abscissas 
*
* same as evaluation of f(x) = x on the grid
* @param g The grid 
*
* @return Host Vector
*/
thrust::host_vector<double> abscissas( const Grid1d& g)
{
    thrust::host_vector<double> v(g.size()); 
    for( unsigned i=0; i<g.N(); i++)
    {
        for( unsigned j=0; j<g.n(); j++)
            v[i*g.n()+j] = (g.x0()+g.h()*(double)i) + (g.h()/2.)*(1 + g.dlt().abscissas()[j]);
    }
    return v;
}
///@endcond


///@addtogroup highlevel
///@{

/*!@class hide_weights_doc
* @brief create host vector containing X-space weight coefficients
* @param g The grid 
* @return Host Vector
* @sa <a href="./dg_introduction.pdf" target="_blank">Introduction to dg methods</a>
*/
/*!@class hide_inv_weights_doc
* @brief create host vector containing inverse X-space weight coefficients
* @param g The grid 
* @return Host Vector
* @sa <a href="./dg_introduction.pdf" target="_blank">Introduction to dg methods</a>
*/
/*!@class hide_weights_coo_doc
* @brief create host vector containing X-space weight coefficients
* @param g The grid 
* @param coo The coordinate for which to generate the weights (in 2d only \c dg::x and \c dg::y are allowed)
* @return Host Vector with full grid size
* @sa <a href="./dg_introduction.pdf" target="_blank">Introduction to dg methods</a>
*/

///@copydoc hide_weights_doc
///@copydoc hide_code_evaluate1d
thrust::host_vector<double> weights( const Grid1d& g)
{
    thrust::host_vector<double> v( g.size());
    for( unsigned i=0; i<g.N(); i++)
        for( unsigned j=0; j<g.n(); j++)
            v[i*g.n() + j] = g.h()/2.*g.dlt().weights()[j];
    return v;
}
///@copydoc hide_inv_weights_doc
thrust::host_vector<double> inv_weights( const Grid1d& g)
{
    thrust::host_vector<double> v = weights( g);
    for( unsigned i=0; i<g.size(); i++)
        v[i] = 1./v[i];
    return v;
}

///@cond
namespace detail{

int get_i( unsigned n, int idx) { return idx%(n*n)/n;}
int get_j( unsigned n, int idx) { return idx%(n*n)%n;}
int get_i( unsigned n, unsigned Nx, int idx) { return (idx/(n*Nx))%n;}
int get_j( unsigned n, unsigned Nx, int idx) { return idx%n;}
}//namespace detail
///@endcond

///@copydoc hide_weights_doc
///@copydoc hide_code_evaluate2d
thrust::host_vector<double> weights( const aTopology2d& g)
{
    thrust::host_vector<double> v( g.size());
    for( unsigned i=0; i<g.size(); i++)
        v[i] = g.hx()*g.hy()/4.*
                g.dlt().weights()[detail::get_i(g.n(),g.Nx(), i)]*
                g.dlt().weights()[detail::get_j(g.n(),g.Nx(), i)];
    return v;
}
///@copydoc hide_inv_weights_doc
thrust::host_vector<double> inv_weights( const aTopology2d& g)
{
    thrust::host_vector<double> v = weights( g);
    for( unsigned i=0; i<g.size(); i++)
        v[i] = 1./v[i];
    return v;
}

///@copydoc hide_weights_coo_doc
thrust::host_vector<double> weights( const aTopology2d& g, enum Coordinate coo)
{
    thrust::host_vector<double> w( g.size());
    if( coo == dg::x) {
        for( unsigned i=0; i<g.size(); i++)
            w[i] = g.hx()/2.* g.dlt().weights()[i%g.n()];
    }
    else if( coo == dg::y) {
        for( unsigned i=0; i<g.size(); i++)
            w[i] = g.hy()/2.* g.dlt().weights()[(i/(g.n()*g.Nx()))%g.n()];
    }
    else 
        std::cerr << "WARNING: specified wrong coordinate in 2d grid\n";
    return w;
}


///@copydoc hide_weights_doc
///@copydoc hide_code_evaluate3d
thrust::host_vector<double> weights( const aTopology3d& g)
{
    thrust::host_vector<double> v( g.size());
    for( unsigned i=0; i<g.size(); i++)
        v[i] = g.hx()*g.hy()*g.hz()/4.*
               g.dlt().weights()[detail::get_i(g.n(), g.Nx(), i)]*
               g.dlt().weights()[detail::get_j(g.n(), g.Nx(), i)];
    return v;
}

///@copydoc hide_inv_weights_doc
thrust::host_vector<double> inv_weights( const aTopology3d& g)
{
    thrust::host_vector<double> v = weights( g);
    for( unsigned i=0; i<g.size(); i++)
        v[i] = 1./v[i];
    return v;
}

///@copydoc hide_weights_coo_doc
thrust::host_vector<double> weights( const aTopology3d& g, enum Coordinate coo)
{
    thrust::host_vector<double> w( g.size());
    if( coo == dg::x) {
        for( unsigned i=0; i<g.size(); i++)
            w[i] = g.hx()/2.* g.dlt().weights()[i%g.n()];
    }
    else if( coo == dg::y) {
        for( unsigned i=0; i<g.size(); i++)
            w[i] = g.hy()/2.* g.dlt().weights()[(i/(g.n()*g.Nx()))%g.n()];
    }
    else if( coo == dg::z) {
        for( unsigned i=0; i<g.size(); i++)
            w[i] = g.hz();
    }
    else if( coo == dg::xy) {
        for( unsigned i=0; i<g.size(); i++)
            w[i] = g.hx()*g.hy()/4.* g.dlt().weights()[i%g.n()]*g.dlt().weights()[(i/(g.n()*g.Nx()))%g.n()];
    }
    else if( coo == dg::yz) {
        for( unsigned i=0; i<g.size(); i++)
            w[i] = g.hy()*g.hz()/2.* g.dlt().weights()[(i/(g.n()*g.Nx()))%g.n()];
    }
    else if( coo == dg::xz) {
        for( unsigned i=0; i<g.size(); i++)
            w[i] = g.hx()*g.hz()/2.* g.dlt().weights()[i%g.n()];
    }
    return w;
}

///@}
}//namespace create
}//namespace dg
