#pragma once

#include "dg/algorithm.h"
#include "parameters.h"

namespace asela
{

template< class Geometry, class Matrix, class Container >
struct Asela
{
    Asela( const Geometry& g, asela::Parameters p);

    void operator()( double time, const std::vector<Container>& y, std::vector<Container>& yp);

    /// ///////////////////DIAGNOSTICS///////////////////////////////
    const Container& potential( int i) const { return m_phi[i];}
    const Container& aparallel( int i) const { return m_apar[i];}
    const Container& density(   int i) const { return m_n[i];}
    const Container& velocity( int i) const { return m_u[i];}
    const std::array<Container,2>& gradN( int i) const { return m_dFN[i];}
    const std::array<Container,2>& gradU( int i) const { return m_dFU[i];}
    const std::array<Container,2>& gradP( int i) const { return m_dP[i];}
    const std::array<Container,2>& gradA( int i) const { return m_dA[i];}
    const dg::Elliptic<Geometry, Matrix, Container>& laplaceM() const{return m_lapMperp;}
    /// ////////////////DIAGNOSTICS END//////////////////////////////

    void compute_psi( double time);
    void compute_phi( double time, const std::array<Container,2>& n);
    void compute_apar( double time, const std::array<Container,2>& n, std::array<Container,2>& u);
    void compute_diff( const Container& nme, double beta, Container& result)
    {
        if( m_p.nu_perp != 0)
        {
            dg::blas2::gemv( m_lapMperp, nme, m_temp0);
            dg::blas2::gemv( -m_p.nu_perp, m_lapMperp, m_temp0, beta, result);
        }
        else
            dg::blas1::scal( result, beta);
    }

  private:
    //Containers
    Container m_temp0, m_temp1, m_temp2;
    std::array<Container,2> m_phi, m_apar, m_n, m_u;
    std::array<std::array<Container,2>,2> m_dFN, m_dBN, m_dFU, m_dBU, m_dP, m_dA;
    std::vector<Container> m_multi_chi;
    //matrices and solvers
    Matrix m_dxF, m_dxB, m_dxC;
    Matrix m_dyF, m_dyB, m_dyC;
    dg::ArakawaX< Geometry, Matrix, Container > m_arakawa;
    dg::Elliptic< Geometry, Matrix, Container > m_lapMperp;
    std::vector<dg::Elliptic<Geometry, Matrix, Container>> m_multi_pol;
    std::vector<dg::Helmholtz<Geometry, Matrix, Container>> m_multi_maxwell, m_multi_invgamma;

    dg::MultigridCG2d<Geometry, Matrix, Container> m_multigrid;
    dg::Extrapolation<Container> m_old_phi, m_old_psi, m_old_gammaN, m_old_gammaNW, m_old_Apar, m_old_gammaApar;

    const asela::Parameters m_p;
};
///@}

template<class Grid, class Matrix, class Container>
Asela<Grid, Matrix, Container>::Asela( const Grid& g, Parameters p):
    //////////the derivative and arakawa operators /////////////////////////
    m_dxF ( dg::create::dx( g, dg::forward)),
    m_dxB ( dg::create::dx( g, dg::backward)),
    m_dxC ( dg::create::dx( g, dg::centered)),
    m_dyF ( dg::create::dy( g, dg::forward)),
    m_dyB ( dg::create::dy( g, dg::backward)),
    m_dyC ( dg::create::dy( g, dg::centered)),
    m_arakawa(g, g.bcx(), g.bcy()),
    //////////the elliptic and Helmholtz operators//////////////////////////
    m_lapMperp ( g, dg::normed, dg::centered),
    m_multigrid( g, 3),
    m_old_phi( 2, dg::evaluate( dg::zero, g)),
    m_old_psi( 2, dg::evaluate( dg::zero, g)),
    m_old_gammaN( 2, dg::evaluate( dg::zero, g)),
    m_old_gammaNW( 2, dg::evaluate( dg::zero, g)),
    m_old_Apar( 2, dg::evaluate( dg::zero, g)),
    m_old_gammaApar( 2, dg::evaluate( dg::zero, g)),
    m_p(p)
{
    ////////////////////////////init temporaries///////////////////
    dg::assign( dg::evaluate( dg::zero, g), m_temp0);
    m_temp1 = m_temp2 = m_temp0;
    m_phi[0] = m_phi[1] = m_temp0;
    m_apar = m_n = m_u = m_phi;
    m_dA[0] = m_dA[1] = m_phi;
    m_dFN = m_dBN = m_dFU = m_dBU = m_dP = m_dA;

    //////////////////////////////init elliptic and helmholtz operators////////////
    m_multi_chi = multigrid.project( m_temp0);
    m_multi_pol.resize(3);
    m_multi_maxwell.resize(3);
    m_multi_invgamma.resize(3);
    for( unsigned u=0; u<3; u++)
    {
        m_multi_pol[u].construct(      multigrid.grid(u), dg::not_normed, dg::centered, m_p.jfactor);
        m_multi_maxwell[u].construct(  multigrid.grid(u), 1., dg::centered);
        m_multi_invgamma[u].construct( multigrid.grid(u), -0.5*m_p.tau[1]*m_p.mu[1], dg::centered);
    }
}

template<class Geometry, class Matrix, class Container>
void Asela<Geometry, Matrix, Container>::compute_phi( double t, const std::array<Container,2>& nme)
{
    dg::blas1::axpby( m_p.mu[1], nme[1], m_p.mu[1], 1., m_temp0); //chi =  \mu_i n_i

    multigrid.project( m_temp0, multi_chi);
    for( unsigned u=0; u<3; u++)
        multi_pol[u].set_chi( multi_chi[u]);

    //----------Compute right hand side------------------------//
    if (m_p.tau[1] == 0.) {
        //compute N_i - n_e
        dg::blas1::axpby( 1., nme[1], -1., nme[0], m_temp0);
    }
    else
    {
        //compute Gamma N_i - n_e
        m_old_gammaN.extrapolate( time, m_temp0);
        std::vector<unsigned> numberG = m_multigrid.direct_solve(
            m_multi_invgamma, m_temp0, nme[1], m_p.eps_gamma);
        m_old_gammaN.update( time, m_temp0);
        if(  numberG[0] == m_multigrid.max_iter())
            throw dg::Fail( m_p.eps_gamma);
        dg::blas1::axpby( -1., nme[0], 1., m_temp0, m_temp0);
    }
    //----------Invert polarisation----------------------------//
    m_old_phi.extrapolate( time, m_phi[0]);
    std::vector<unsigned> number = m_multigrid.direct_solve(
        m_multi_pol, m_phi[0], m_temp0,
        {m_p.eps_pol, 10.*m_p.eps_pol, 10.*m_p.eps_pol});
    m_old_phi.update( time, m_phi[0]);
    if(  number[0] == m_multigrid.max_iter())
        throw dg::Fail( m_p.eps_pol[0]);
}
template<class Geometry, class Matrix, class Container>
void Asela<Geometry, Matrix, Container>::compute_psi(
    double time)
{
    //-----------Solve for Gamma Phi---------------------------//
    if (m_p.tau[1] == 0.) {
        dg::blas1::copy( m_phi[0], m_phi[1]);
    } else {
        m_old_psi.extrapolate( time, m_phi[1]);
        std::vector<unsigned> number = m_multigrid.direct_solve(
            m_multi_invgamma, m_phi[1], m_phi[0], m_p.eps_gamma);
        m_old_psi.update( time, m_phi[1]);
        if(  number[0] == m_multigrid.max_iter())
            throw dg::Fail( m_p.eps_gamma);
    }
    //-------Compute Psi and derivatives
    dg::blas2::symv( m_dxC, m_phi[0], m_dP[0][0]);
    dg::blas2::symv( m_dyC, m_phi[0], m_dP[0][1]);
    dg::blas1::pointwiseDot( -0.5, m_dP[0][0], m_dP[0][0], -0.5, m_dP[0][1], m_dP[0][1], 1., m_phi[1]);
    dg::blas2::symv( m_dxC, m_phi[1], m_dP[1][0]);
    dg::blas2::symv( m_dyC, m_phi[1], m_dP[1][1]);
}
template<class Geometry, class Matrix, class Container>
void Asela<Geometry, Matrix, Container>::compute_apar(
    double time, const std::array<Container>& n, std::array<Container,2>& u)
{
    //on input
    //n[0] = n_e, u[0]:= w_e
    //n[1] = N_i, u[1]:= W_i
    //----------Compute and set chi----------------------------//
    dg::blas1::axpby(  m_p.beta/m_p.mu[1], n[1],
                      -m_p.beta/m_p.mu[0], n[0], m_temp0);
    m_multigrid.project( m_temp0, m_multi_chi);
    for( unsigned u=0; u<m_p.stages; u++)
        m_multi_maxwell[u].set_chi( m_multi_chi[u]);

    //----------Compute right hand side------------------------//
    dg::blas1::pointwiseDot(  m_p.beta, n[1], u[1],
                             -m_p.beta, n[0], u[0],
                              0., m_temp0);
    //----------Invert Induction Eq----------------------------//
    m_old_apar.extrapolate( time, m_apar);
    std::vector<unsigned> number = m_multigrid.direct_solve(
        m_multi_induction, m_apar[0], m_temp0, m_p.eps_pol[0]);
    m_old_apar.update( time, m_apar[0]);
    if(  number[0] == m_multigrid.max_iter())
        throw dg::Fail( m_p.eps_pol[0]);
    //----------Compute Derivatives----------------------------//
    //For now we do not apply Gamma on A
    dg::blas1::copy( m_apar[0], m_apar[1]);
    dg::blas2::symv( m_dxC, m_apar[0], m_dA[0][0]);
    dg::blas2::symv( m_dyC, m_apar[0], m_dA[0][1]);
    dg::blas2::symv( m_dxC, m_apar[1], m_dA[1][0]);
    dg::blas2::symv( m_dyC, m_apar[1], m_dA[1][1]);

    //----------Compute Velocities-----------------------------//
    dg::blas1::axpby( 1., u[0], -1./m_p.mu[0], m_apar[0], u[0]);
    dg::blas1::axpby( 1., u[1], -1./m_p.mu[1], m_apar[1], u[1]);
}

template<class G, class M, class Container>
void Asela<G, M, Container>::compute_perp( double time, const std::array<std::array<Container,2>,2>& y, std::array<std::array<Container,2>,2>& yp)
{
    //Compute using Arakawa brackets
    for( unsigned i=0; i<2; i++)
    {
        //ExB dynamics
        arakawa( y[0][i], phi[i], yp[0][i]);                 //[N,phi]_RZ
        arakawa( y[1][i], phi[i], yp[1][i]);                 //[w,phi]_RZ

        // Density equation
        dg::blas1::pointwiseDot( 1., m_n[i], m_u[i], 0., m_temp0);
        arakawa( 1., apar[i], m_temp0,   1., yp[0][i]); // [Apar, UN]_RZ

        // Velocity Equation
        dg::blas1::transform( m_n[i], m_temp0, dg::LN<double>());
        arakawa( m_p.tau[i]/m_p.mu[i], apar[i], m_temp0, 1., yp[1][i]);  // + tau/mu [Apar,logN]_RZ
        dg::blas1::pointwiseDot( 1., m_u[i], m_u[i], 0., m_temp0);
        arakawa( 0.5, apar[i], m_temp0,   1., yp[1][i]);                       // +0.5[Apar,U^2]_RZ
    }
}

template<class Geometry, class Matrix, class Container>
void Asela<Geometry, Matrix, Container>::operator()( double time,  const std::array<std::array<Container,2>,2>& y, std::array<std::array<Container,2>,2>& yp)
{
    /* y[0][0] := n_e - 1
       y[0][1] := N_i - 1
       y[1][0] := w_e = U_e + Apar_e / mu_e
       y[1][1] := W_i = U_i + Apar_i / mu_i
    */

    dg::Timer t;
    t.tic();

    compute_phi( time, y[0]); //computes phi[0] and Gamma n_i

    compute_psi( time ); //compues phi[1]

    //transform n-1 to n
    dg::blas1::transform( y[0], m_n, dg::PLUS<>(+1.)); //n = y+1

    // Compute Apar and m_U if necessary --- reads and updates m_u
    dg::blas1::copy( y[1], m_u);
    if( m_p.beta != 0)
        compute_apar( time, m_n, m_u);

    //parallel dynamics (uses m_n and m_u)
    compute_perp( time, y, yp);

    // Add diffusion
    for( unsigned i=0; i<2; i++)
    {
        compute_diff( y[0][i], 1., yp[0][i]);
        compute_diff(  m_u[i], 1., yp[1][i]);
    }

    t.toc();
    #ifdef MPI_VERSION
        int rank;
        MPI_Comm_rank( MPI_COMM_WORLD, &rank);
        if(rank==0)
    #endif
    std::cout << "One rhs took "<<t.diff()<<"s\n";
}

} //namespace asela
