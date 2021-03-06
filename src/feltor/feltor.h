#pragma once

#include "dg/algorithm.h"
#include "parameters.h"
#include "dg/geometries/geometries.h"
#ifndef DG_MANUFACTURED
#define FELTORPARALLEL 1
#define FELTORPERP 1
#endif


//Latest measurement: m = 10.000 per step

namespace feltor
{

namespace routines{
struct ComputePerpDrifts{
    ComputePerpDrifts( double mu, double tau):
        m_mu(mu), m_tau(tau){}
    DG_DEVICE
    void operator()(
            double N, double d0N, double d1N, double d2N,
            double U, double d0U, double d1U, double d2U,
            double d0P, double d1P, double d2P,
            double b_0,         double b_1,         double b_2,
            double curv0,       double curv1,       double curv2,
            double curvKappa0,  double curvKappa1,  double curvKappa2,
            double divCurvKappa,
            double& dtN, double& dtU
        )
    {
        double KappaU = curvKappa0*d0U+curvKappa1*d1U+curvKappa2*d2U;
        double KappaN = curvKappa0*d0N+curvKappa1*d1N+curvKappa2*d2N;
        double KappaP = curvKappa0*d0P+curvKappa1*d1P+curvKappa2*d2P;
        double KU = curv0*d0U+curv1*d1U+curv2*d2U;
        double KN = curv0*d0N+curv1*d1N+curv2*d2N;
        double KP = curv0*d0P+curv1*d1P+curv2*d2P;
        double PN = b_0*( d1P*d2N-d2P*d1N)+
                    b_1*( d2P*d0N-d0P*d2N)+
                    b_2*( d0P*d1N-d1P*d0N);//ExB drift
        double PU = b_0*( d1P*d2U-d2P*d1U)+
                    b_1*( d2P*d0U-d0P*d2U)+
                    b_2*( d0P*d1U-d1P*d0U);//ExB drift
        dtN =   -PN
                -N * KP
                -m_tau * KN
                -m_mu * U * U * KappaN
                -2. * m_mu * N * U * KappaU
                -m_mu * N * U * U * divCurvKappa;
        dtU =   -PU
                -U*KappaP
                -m_tau * KU
                -m_tau * U * divCurvKappa
                -(2. * m_tau + m_mu * U * U)*KappaU
                - 2. * m_tau * U * KappaN / N;
    }
    DG_DEVICE
    void operator()(
            double N, double d0N, double d1N, double d2N,
            double U, double d0U, double d1U, double d2U,
            double d0P, double d1P, double d2P,
            double A,       double d0A, double d1A, double d2A,
            double b_0,         double b_1,         double b_2,
            double curv0,       double curv1,       double curv2,
            double curvKappa0,  double curvKappa1,  double curvKappa2,
            double divCurvKappa,
            double& dtN, double& dtU
        )
    {
        //first compute the regular dynamics
        this->operator()( N,  d0N,  d1N,  d2N,
             U,        d0U,  d1U,  d2U,
             d0P,  d1P,  d2P,
             b_0,          b_1,          b_2,
             curv0,        curv1,        curv2,
             curvKappa0,   curvKappa1,   curvKappa2,
             divCurvKappa,
             dtN, dtU);
        //now add the additional terms from modified parallel derivative
        double KappaU = curvKappa0*d0U+curvKappa1*d1U+curvKappa2*d2U;
        double KappaN = curvKappa0*d0N+curvKappa1*d1N+curvKappa2*d2N;
        double KappaP = curvKappa0*d0P+curvKappa1*d1P+curvKappa2*d2P;

        double KnablaBA = (curv0-curvKappa0)*d0A
                         +(curv1-curvKappa1)*d1A
                         +(curv2-curvKappa2)*d2A;
        double UA = b_0*( d1U*d2A-d2U*d1A)+
                    b_1*( d2U*d0A-d0U*d2A)+
                    b_2*( d0U*d1A-d1U*d0A);
        double NA = b_0*( d1N*d2A-d2N*d1A)+
                    b_1*( d2N*d0A-d0N*d2A)+
                    b_2*( d0N*d1A-d1N*d0A);
        double PA = b_0*( d1P*d2A-d2P*d1A)+
                    b_1*( d2P*d0A-d0P*d2A)+
                    b_2*( d0P*d1A-d1P*d0A);
        dtN +=  -( A*N*KappaU + A*U*KappaN + N*UA + U*NA)
                -N*U*( A*divCurvKappa - KnablaBA);
        dtU +=  -1./m_mu*( A*KappaP + PA)
                -1.*U*( A*KappaU + UA)
                -1.*m_tau/m_mu/N*(A*KappaN + NA);


    }
    private:
    double m_mu, m_tau;
};
struct ComputeChi{
    DG_DEVICE
    void operator() ( double& chi, double tilde_Ni, double binv,
    double mu_i) const{
        chi = mu_i*(tilde_Ni+1.)*binv*binv;
    }
};
struct ComputePsi{
    DG_DEVICE
    void operator()( double& gradPhi2, double dxPhi, double dyPhi,
        double dzPhi, double& HdxPhi, double HdyPhi, double HdzPhi
        ) const{
        gradPhi2 = (dxPhi*HdxPhi + dyPhi*HdyPhi + dzPhi*HdzPhi);
    }
    DG_DEVICE
    void operator()( double& GammaPhi, double dxPhi, double dyPhi,
        double dzPhi, double& HdxPhi, double HdyPhi, double HdzPhi,
        double binv) const{
        //u_E^2
        this->operator()(
            HdxPhi, dxPhi, dyPhi, dzPhi, HdxPhi, HdyPhi , HdzPhi);
        HdxPhi   = binv*binv*HdxPhi;
        //Psi
        GammaPhi = GammaPhi - 0.5*HdxPhi;
    }
};
struct ComputeLogN{
    DG_DEVICE
    void operator()( double tilde_n, double& npe, double& logn) const{
        npe =  tilde_n + 1.;
        logn =  log(npe);
    }
};
struct ComputeSource{
    DG_DEVICE
    void operator()( double& result, double tilde_n, double profne,
        double source, double omega_source) const{
        result = omega_source*source*(profne - tilde_n);
    }
};
//Resistivity (consistent density dependency,
//parallel momentum conserving, quadratic current energy conservation dependency)
struct AddResistivity{
    AddResistivity( double eta, std::array<double,2> mu): m_eta(eta){
        m_mu[0] = mu[0], m_mu[1] = mu[1];
    }
    DG_DEVICE
    void operator()( double ne, double ni, double ue,
        double ui, double& dtUe, double& dtUi) const{
        double current = (ne)*(ui-ue);
        dtUe += -m_eta/m_mu[0] * current;
        dtUi += -m_eta/m_mu[1] * (ne)/(ni) * current;
    }
    private:
    double m_eta;
    double m_mu[2];
};
}//namespace routines

template< class Geometry, class IMatrix, class Matrix, class Container >
struct Explicit
{
    using vector = std::array<std::array<Container,2>,2>;
    using container = Container;
    Explicit( const Geometry& g, feltor::Parameters p,
        dg::geo::TokamakMagneticField mag, bool full_system ); //full system means explicit AND implicit

    //Given N_i-1 initialize n_e-1 such that phi=0
    void initializene( const Container& ni, Container& ne);
    //Given n_e-1 initialize N_i-1 such that phi=0
    void initializeni( const Container& ne, Container& ni, std::string initphi);

    void operator()( double t,
        const std::array<std::array<Container,2>,2>& y,
        std::array<std::array<Container,2>,2>& yp);

    const std::array<std::array<Container,2>,2>& fields() const{
        return m_fields;
    }
    const std::array<Container,2>& potentials() const{
        return m_phi;
    }
    const std::array<std::array<Container,2>,2>& sources() const{
        return m_s;
    }

    /// ///////////////////DIAGNOSTIC MEMBERS //////////////////////
    const Geometry& grid() const {
        return m_multigrid.grid(0);
    }
    //potential[0]: electron potential, potential[1]: ion potential
    const Container& uE2() const {
        return m_UE2;
    }
    const Container& density(int i)const{
        return m_fields[0][i];
    }
    const Container& density_source(int i)const{
        return m_s[0][i];
    }
    const Container& velocity(int i)const{
        return m_fields[1][i];
    }
    const Container& velocity_source(int i)const{
        return m_s[1][i];
    }
    const Container& potential(int i) const {
        return m_phi[i];
    }
    const Container& induction() const {
        return m_apar;
    }
    const std::array<Container, 3> & gradN (int i) const {
        return m_dN[i];
    }
    const std::array<Container, 3> & gradU (int i) const {
        return m_dU[i];
    }
    const std::array<Container, 3> & gradP (int i) const {
        return m_dP[i];
    }
    const std::array<Container, 3> & gradA () const {
        return m_dA;
    }
    const Container & dsN (int i) const {
        return m_dsN[i];
    }
    const Container & dsU (int i) const {
        return m_dsU[i];
    }
    const Container & dssN(int i) { //2nd fieldaligned derivative
        return m_dssN[i];
    }
    const Container & dssU(int i) {
        return m_dssU[i];
    }
    void compute_gradSN( int i, std::array<Container,3>& gradS) const{
        // MW: don't like this function, if we need more gradients we might
        // want a more flexible solution
        // grad S_ne and grad S_ni
        dg::blas2::symv( m_dx_N, m_s[0][i], gradS[0]);
        dg::blas2::symv( m_dy_N, m_s[0][i], gradS[1]);
        if(!m_p.symmetric)dg::blas2::symv( m_dz, m_s[0][i], gradS[2]);
    }
    const Container & compute_dppN(int i) { //2nd varphi derivative
        dg::blas2::symv( m_dz, m_fields[0][i], m_temp0);
        dg::blas2::symv( m_dz, m_temp0, m_temp1);
        return m_temp1;
    }
    const Container & compute_dppP(int i) {
        dg::blas2::symv( m_dz, m_phi[i], m_temp0);
        dg::blas2::symv( m_dz, m_temp0, m_temp1);
        return m_temp1;
    }
    const Container & compute_dppU(int i) {
        dg::blas2::symv( m_dz, m_fields[1][i], m_temp0);
        dg::blas2::symv( m_dz, m_temp0, m_temp1);
        return m_temp1;
    }
    const dg::SparseTensor<Container>& projection() const{
        return m_hh;
    }
    const std::array<Container, 3> & curv () const {
        return m_curv;
    }
    const std::array<Container, 3> & curvKappa () const {
        return m_curvKappa;
    }
    const Container& divCurvKappa() const {
        return m_divCurvKappa;
    }
    const Container& bphi( ) const { return m_bphi; }
    const Container& binv( ) const { return m_binv; }
    const Container& divb( ) const { return m_divb; }
    const Container& vol3d() const { return m_vol3d;}
    const Container& weights() const { return m_lapperpN.weights();}
    //bhat / sqrt{g} / B
    const std::array<Container, 3> & bhatgB () const {
        return m_b;
    }
    const Container& lapMperpP (int i)
    {
        dg::blas2::gemv( m_lapperpP, m_phi[i], m_temp1);
        return m_temp1;
    }
    const Container& lapMperpA ()
    {
        dg::blas2::gemv( m_lapperpU, m_apar, m_temp1);
        return m_temp1;
    }
    /////////////////////////DIAGNOSTICS END////////////////////////////////
    void compute_diffusive_lapMperpN( const Container& density, Container& temp0, Container& result ){
        // compute the negative diffusion contribution -Lambda N
        // perp dissipation for N: nu_perp Delta_p N or -nu_perp Delta_p**2 N
        if( m_p.perp_diff == "viscous")
        {
            dg::blas1::transform( density, temp0, dg::PLUS<double>(-1));
            dg::blas2::gemv( m_lapperpN, temp0, result); //!minus
        }
        else
        {
            dg::blas1::transform( density, result, dg::PLUS<double>(-1));
            dg::blas2::gemv( m_lapperpN, result, temp0);
            dg::blas2::gemv( m_lapperpN, temp0, result); //!plus
        }
    }
    void compute_diffusive_lapMperpU( const Container& velocity, Container& temp0, Container& result ){
        // compute the negative diffusion contribution -Lambda U
        // perp dissipation for U: nu_perp Delta_p U or -nu_perp Delta_p**2 U
        if( m_p.perp_diff == "viscous")
        {
            dg::blas2::gemv( m_lapperpU, velocity, result); //!minus
        }
        else
        {
            dg::blas2::gemv( m_lapperpU, velocity, temp0);
            dg::blas2::gemv( m_lapperpU, temp0, result); //!plus
        }
    }

    //source strength, profile - 1
    void set_source( bool fixed_profile, Container profile, double omega_source, Container source, double omega_damping, Container damping )
    {
        m_fixed_profile = fixed_profile;
        m_profne = profile;
        m_omega_source = omega_source;
        m_source = source;
        m_omega_damping = omega_damping;
        m_damping = damping;
    }
    void compute_apar( double t, std::array<std::array<Container,2>,2>& fields);
  private:
    void compute_phi( double t, const std::array<Container,2>& y);
    void compute_psi( double t);
    void compute_perp( double t,
        const std::array<std::array<Container,2>,2>& y,
        const std::array<std::array<Container,2>,2>& fields,
        std::array<std::array<Container,2>,2>& yp);
    void compute_parallel( double t,
        const std::array<std::array<Container,2>,2>& y,
        const std::array<std::array<Container,2>,2>& fields,
        std::array<std::array<Container,2>,2>& yp);
    void construct_mag( const Geometry&, feltor::Parameters,
        dg::geo::TokamakMagneticField);
    void construct_bhat( const Geometry&, feltor::Parameters,
        dg::geo::TokamakMagneticField);
    void construct_invert( const Geometry&, feltor::Parameters,
        dg::geo::TokamakMagneticField);

    Container m_UE2;
    Container m_temp0, m_temp1, m_temp2;//helper variables
#ifdef DG_MANUFACTURED
    Container m_R, m_Z, m_P; //coordinates
#endif //DG_MANUFACTURED

    //these should be considered const // m_curv is full curvature
    std::array<Container,3> m_curv, m_curvKappa, m_b;
    Container m_divCurvKappa;
    Container m_bphi, m_binv, m_divb;
    Container m_source, m_profne, m_damping;
    Container m_vol3d;

    Container m_apar;
    std::array<Container,2> m_phi, m_logn, m_dsN, m_dsU, m_dssN, m_dssU;
    std::array<Container,3> m_dA;
    std::array<std::array<Container,3>,2> m_dP, m_dN, m_dU;
    std::array<std::array<Container,2>,2> m_fields, m_s; //fields, sources

    std::vector<Container> m_multi_chi;

    //matrices and solvers
    Matrix m_dx_N, m_dx_U, m_dx_P, m_dy_N, m_dy_U, m_dy_P, m_dz;
    dg::geo::DS<Geometry, IMatrix, Matrix, Container> m_ds_P, m_ds_N, m_ds_U;
    dg::Elliptic3d< Geometry, Matrix, Container> m_lapperpN, m_lapperpU, m_lapperpP;
    std::vector<dg::Elliptic3d< Geometry, Matrix, Container> > m_multi_pol;
    std::vector<dg::Helmholtz3d<Geometry, Matrix, Container> > m_multi_invgammaP,
        m_multi_invgammaN, m_multi_induction;

    dg::MultigridCG2d<Geometry, Matrix, Container> m_multigrid;
    dg::Extrapolation<Container> m_old_phi, m_old_psi, m_old_gammaN, m_old_apar;

    dg::SparseTensor<Container> m_hh;

    const feltor::Parameters m_p;
    double m_omega_source = 0., m_omega_damping = 0.;
    bool m_fixed_profile = true;
    bool m_full_system = false;

};

template<class Grid, class IMatrix, class Matrix, class Container>
void Explicit<Grid, IMatrix, Matrix, Container>::construct_mag(
    const Grid& g, feltor::Parameters p, dg::geo::TokamakMagneticField mag)
{
    if( !(p.perp_diff == "viscous" || p.perp_diff == "hyperviscous") )
        throw dg::Error(dg::Message(_ping_)<<"Warning! perp_diff value '"<<p.perp_diff<<"' not recognized!! I do not know how to proceed! Exit now!");
    //due to the various approximations bhat and mag not always correspond
    dg::geo::CylindricalVectorLvl0 curvNabla, curvKappa;
    if( p.curvmode == "true" )
    {
        curvNabla = dg::geo::createTrueCurvatureNablaB(mag);
        curvKappa = dg::geo::createTrueCurvatureKappa(mag);
        dg::assign(  dg::pullback(dg::geo::TrueDivCurvatureKappa(mag), g),
            m_divCurvKappa);
    }
    else if( p.curvmode == "low beta")
    {
        curvNabla = curvKappa = dg::geo::createCurvatureNablaB(mag, +1);
        dg::assign( dg::evaluate(dg::zero, g), m_divCurvKappa);
    }
    else if( p.curvmode == "toroidal")
    {
        curvNabla = dg::geo::createCurvatureNablaB(mag, +1);
        curvKappa = dg::geo::createCurvatureKappa(mag, +1);
        dg::assign(  dg::pullback(dg::geo::DivCurvatureKappa(mag, +1), g),
            m_divCurvKappa);
    }
    else if( p.curvmode == "low beta negative")
    {
        curvNabla = curvKappa = dg::geo::createCurvatureNablaB(mag, -1);
        dg::assign( dg::evaluate(dg::zero, g), m_divCurvKappa);
    }
    else if( p.curvmode == "toroidal negative")
    {
        curvNabla = dg::geo::createCurvatureNablaB(mag, -1);
        curvKappa = dg::geo::createCurvatureKappa(mag, -1);
        dg::assign(  dg::pullback(dg::geo::DivCurvatureKappa(mag, -1), g),
            m_divCurvKappa);
    }
    else
        throw dg::Error(dg::Message(_ping_)<<"Warning! curvmode value '"<<p.curvmode<<"' not recognized!! I don't know what to do! I exit!\n");
    dg::pushForward(curvNabla.x(), curvNabla.y(), curvNabla.z(),
        m_curv[0], m_curv[1], m_curv[2], g);
    dg::pushForward(curvKappa.x(), curvKappa.y(), curvKappa.z(),
        m_curvKappa[0], m_curvKappa[1], m_curvKappa[2], g);
    dg::blas1::axpby( 1., m_curvKappa, 1., m_curv);
    dg::assign(  dg::pullback(dg::geo::InvB(mag), g), m_binv);
    dg::assign(  dg::pullback(dg::geo::Divb(mag), g), m_divb);

}
template<class Grid, class IMatrix, class Matrix, class Container>
void Explicit<Grid, IMatrix, Matrix, Container>::construct_bhat(
    const Grid& g, feltor::Parameters p, dg::geo::TokamakMagneticField mag)
{
    //in DS we take the true bhat
    auto bhat = dg::geo::createBHat( mag);
    m_ds_N.construct( bhat, g, p.bcxN, p.bcyN, dg::geo::NoLimiter(),
        dg::forward, p.rk4eps, p.mx, p.my, 2.*M_PI/(double)p.Nz );
    if( p.bcxU == p.bcxN && p.bcyU == p.bcyN)
        m_ds_U.construct( m_ds_N);
    else
        m_ds_U.construct( bhat, g, p.bcxU, p.bcyU, dg::geo::NoLimiter(),
            dg::forward, p.rk4eps, p.mx, p.my, 2.*M_PI/(double)p.Nz);
    if( p.bcxP == p.bcxN && p.bcyP == p.bcyN)
        m_ds_P.construct( m_ds_N);
    else if( p.bcxP == p.bcxU && p.bcyP == p.bcyU)
        m_ds_P.construct( m_ds_U);
    else
        m_ds_P.construct( bhat, g, p.bcxP, p.bcyP, dg::geo::NoLimiter(),
            dg::forward, p.rk4eps, p.mx, p.my, 2.*M_PI/(double)p.Nz);

    // in Poisson we take EPhi except for the true curvmode
    bhat = dg::geo::createEPhi(+1);
    if( p.curvmode == "true")
        bhat = dg::geo::createBHat(mag);
    else if ( p.curvmode == "toroidal negative" || p.curvmode == "low beta negative")
        bhat = dg::geo::createEPhi(-1);
    dg::pushForward(bhat.x(), bhat.y(), bhat.z(), m_b[0], m_b[1], m_b[2], g);
    dg::SparseTensor<Container> metric = g.metric();
    dg::tensor::inv_multiply3d( metric, m_b[0], m_b[1], m_b[2],
                                        m_b[0], m_b[1], m_b[2]);
    Container vol = dg::tensor::volume( metric);
    dg::blas1::pointwiseDivide( m_binv, vol, vol); //1/vol/B
    dg::assign( m_b[2], m_bphi); //save bphi for momentum conservation
    for( int i=0; i<3; i++)
        dg::blas1::pointwiseDot( vol, m_b[i], m_b[i]); //b_i/vol/B
    m_hh = dg::geo::createProjectionTensor( bhat, g);
    m_lapperpN.construct ( g, p.bcxN, p.bcyN, dg::PER, dg::normed, dg::centered),
    m_lapperpU.construct ( g, p.bcxU, p.bcyU, dg::PER, dg::normed, dg::centered),
    m_lapperpP.construct ( g, p.bcxP, p.bcyP, dg::PER, dg::normed, dg::centered),
    m_lapperpN.set_chi( m_hh);
    m_lapperpU.set_chi( m_hh);
    m_lapperpP.set_chi( m_hh);
    if( p.curvmode != "true")
    {
        m_lapperpN.set_compute_in_2d(true);
        m_lapperpU.set_compute_in_2d(true);
        m_lapperpP.set_compute_in_2d(true);
    }
    m_lapperpP.set_jfactor(0); //we don't want jump terms in source
}
template<class Grid, class IMatrix, class Matrix, class Container>
void Explicit<Grid, IMatrix, Matrix, Container>::construct_invert(
    const Grid& g, feltor::Parameters p, dg::geo::TokamakMagneticField mag)
{
    /////////////////////////init elliptic and helmholtz operators/////////
    auto bhat = dg::geo::createEPhi(+1); //bhat = ephi except when "true"
    if( p.curvmode == "true")
        bhat = dg::geo::createBHat( mag);
    else if ( p.curvmode == "toroidal negative" || p.curvmode == "low beta negative")
        bhat = dg::geo::createEPhi(-1);
    m_multi_chi = m_multigrid.project( m_temp0);
    m_multi_pol.resize(p.stages);
    m_multi_invgammaP.resize(p.stages);
    m_multi_invgammaN.resize(p.stages);
    m_multi_induction.resize(p.stages);
    for( unsigned u=0; u<p.stages; u++)
    {
        m_multi_pol[u].construct( m_multigrid.grid(u),
            p.bcxP, p.bcyP, dg::PER, dg::not_normed,
            dg::centered, p.jfactor);
        m_multi_invgammaP[u].construct(  m_multigrid.grid(u),
            p.bcxP, p.bcyP, dg::PER, -0.5*p.tau[1]*p.mu[1], dg::centered);
        m_multi_invgammaN[u].construct(  m_multigrid.grid(u),
            p.bcxN, p.bcyN, dg::PER, -0.5*p.tau[1]*p.mu[1], dg::centered);
        m_multi_induction[u].construct(  m_multigrid.grid(u),
            p.bcxU, p.bcyU, dg::PER, -1., dg::centered);

        dg::SparseTensor<Container> hh = dg::geo::createProjectionTensor(
            bhat, m_multigrid.grid(u));
        m_multi_pol[u].set_chi( hh);
        m_multi_invgammaP[u].elliptic().set_chi( hh);
        m_multi_invgammaN[u].elliptic().set_chi( hh);
        m_multi_induction[u].elliptic().set_chi( hh);
        if(p.curvmode != "true"){
            m_multi_pol[u].set_compute_in_2d( true);
            m_multi_invgammaP[u].elliptic().set_compute_in_2d( true);
            m_multi_invgammaN[u].elliptic().set_compute_in_2d( true);
            m_multi_induction[u].elliptic().set_compute_in_2d( true);
        }
    }
}
template<class Grid, class IMatrix, class Matrix, class Container>
Explicit<Grid, IMatrix, Matrix, Container>::Explicit( const Grid& g,
    feltor::Parameters p, dg::geo::TokamakMagneticField mag, bool full_system):
#ifdef DG_MANUFACTURED
    m_R( dg::pullback( dg::cooX3d, g)),
    m_Z( dg::pullback( dg::cooY3d, g)),
    m_P( dg::pullback( dg::cooZ3d, g)),
#endif //DG_MANUFACTURED
    m_dx_N( dg::create::dx( g, p.bcxN) ),
    m_dx_U( dg::create::dx( g, p.bcxU) ),
    m_dx_P( dg::create::dx( g, p.bcxP) ),
    m_dy_N( dg::create::dy( g, p.bcyN) ),
    m_dy_U( dg::create::dy( g, p.bcyU) ),
    m_dy_P( dg::create::dy( g, p.bcyP) ),
    m_dz( dg::create::dz( g, dg::PER) ),
    m_multigrid( g, p.stages),
    m_old_phi( 2, dg::evaluate( dg::zero, g)),
    m_old_psi( m_old_phi), m_old_gammaN( m_old_phi), m_old_apar( m_old_phi),
    m_p(p), m_full_system(full_system)
{
    //--------------------------init vectors to 0-----------------//
    dg::assign( dg::evaluate( dg::zero, g), m_temp0 );
    m_UE2 = m_temp2 = m_temp1 = m_temp0;
    m_apar = m_temp0;

    m_phi[0] = m_phi[1] = m_temp0;
    m_dssN = m_dssU = m_dsN = m_dsU =  m_logn = m_phi;
    m_dA[0] = m_dA[1] = m_dA[2] = m_temp0;
    m_dP[0] = m_dP[1] = m_dA;
    m_dN = m_dU = m_dP;
    m_fields[0] = m_fields[1] = m_phi;
    m_s = m_fields;

    //--------------------------Construct-------------------------//
    construct_mag( g, p, mag);
    construct_bhat( g, p, mag);
    construct_invert( g, p, mag);
    //---------------------------Volume------------------------------//
    dg::assign( dg::create::volume(g), m_vol3d);
}

template<class Geometry, class IMatrix, class Matrix, class Container>
void Explicit<Geometry, IMatrix, Matrix, Container>::initializene(
    const Container& src, Container& target)
{
    // ne = Ni
    dg::blas1::copy( src, target);
    if (m_p.tau[1] != 0.) {
        // ne-1 = Gamma (ni-1)
        std::vector<unsigned> number = m_multigrid.direct_solve(
            m_multi_invgammaN, target, src, m_p.eps_gamma);
        if(  number[0] == m_multigrid.max_iter())
            throw dg::Fail( m_p.eps_gamma);
    }
}
template<class Geometry, class IMatrix, class Matrix, class Container>
void Explicit<Geometry, IMatrix, Matrix, Container>::initializeni(
    const Container& src, Container& target, std::string initphi)
{
    // Ni = ne
    dg::blas1::copy( src, target);
    if (m_p.tau[1] != 0.) {
        if( m_p.initphi == "zero")
        {
            //add FLR correction -0.5*tau*mu*Delta n_e
            dg::blas2::symv( 0.5*m_p.tau[1]*m_p.mu[1],
                m_lapperpN, src, 1.0, target);
            //wird stark negativ falls alpha klein!!
        }
        else if( m_p.initphi == "balance")
            //add FLR correction +0.5*tau*mu*Delta n_e
            dg::blas2::symv( -0.5*m_p.tau[1]*m_p.mu[1],
                m_lapperpN, src, 1.0, target);
            //wird stark negativ falls alpha klein!!
        else
        {
            #ifdef MPI_VERSION
                int rank;
                MPI_Comm_rank( MPI_COMM_WORLD, &rank);
                if(rank==0)
            #endif
            throw dg::Error(dg::Message(_ping_)<<"Warning! initphi value '"<<initphi<<"' not recognized. I have tau = "<<m_p.tau[1]<<" ! I don't know what to do! I exit!\n");
        }
    }
}

template<class Geometry, class IMatrix, class Matrix, class Container>
void Explicit<Geometry, IMatrix, Matrix, Container>::compute_phi(
    double time, const std::array<Container,2>& y)
{
    //y[0]:= n_e - 1
    //y[1]:= N_i - 1
    //----------Compute and set chi----------------------------//
    dg::blas1::subroutine( routines::ComputeChi(),
        m_temp0, y[1], m_binv, m_p.mu[1]);
    m_multigrid.project( m_temp0, m_multi_chi);
    for( unsigned u=0; u<m_p.stages; u++)
        m_multi_pol[u].set_chi( m_multi_chi[u]);

    //----------Compute right hand side------------------------//
    if (m_p.tau[1] == 0.) {
        //compute N_i - n_e
        dg::blas1::axpby( 1., y[1], -1., y[0], m_temp0);
    }
    else
    {
        //compute Gamma N_i - n_e
        m_old_gammaN.extrapolate( time, m_temp0);
#ifdef DG_MANUFACTURED
        dg::blas1::copy( y[1], m_temp1);
        dg::blas1::evaluate( m_temp1, dg::plus_equals(), manufactured::SGammaNi{
            m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
            m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,time);
        std::vector<unsigned> numberG = m_multigrid.direct_solve(
            m_multi_invgammaN, m_temp0, m_temp1, m_p.eps_gamma);
#else
        std::vector<unsigned> numberG = m_multigrid.direct_solve(
            m_multi_invgammaN, m_temp0, y[1], m_p.eps_gamma);
#endif //DG_MANUFACTURED
        m_old_gammaN.update( time, m_temp0);
        if(  numberG[0] == m_multigrid.max_iter())
            throw dg::Fail( m_p.eps_gamma);
        dg::blas1::axpby( -1., y[0], 1., m_temp0, m_temp0);
    }
#ifdef DG_MANUFACTURED
    dg::blas1::evaluate( m_temp0, dg::plus_equals(), manufactured::SPhie{
        m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
        m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,time);
#endif //DG_MANUFACTURED
    //----------Invert polarisation----------------------------//
    m_old_phi.extrapolate( time, m_phi[0]);
    std::vector<unsigned> number = m_multigrid.direct_solve(
        m_multi_pol, m_phi[0], m_temp0, m_p.eps_pol);
    m_old_phi.update( time, m_phi[0]);
    if(  number[0] == m_multigrid.max_iter())
        throw dg::Fail( m_p.eps_pol);
}

template<class Geometry, class IMatrix, class Matrix, class Container>
void Explicit<Geometry, IMatrix, Matrix, Container>::compute_psi(
    double time)
{
    //-----------Solve for Gamma Phi---------------------------//
    if (m_p.tau[1] == 0.) {
        dg::blas1::copy( m_phi[0], m_phi[1]);
    } else {
        m_old_psi.extrapolate( time, m_phi[1]);
#ifdef DG_MANUFACTURED
        dg::blas1::copy( m_phi[0], m_temp0);
        dg::blas1::evaluate( m_temp0, dg::plus_equals(), manufactured::SGammaPhie{
            m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
            m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,time);
        std::vector<unsigned> number = m_multigrid.direct_solve(
            m_multi_invgammaP, m_phi[1], m_temp0, m_p.eps_gamma);
#else
        std::vector<unsigned> number = m_multigrid.direct_solve(
            m_multi_invgammaP, m_phi[1], m_phi[0], m_p.eps_gamma);
#endif //DG_MANUFACTURED
        m_old_psi.update( time, m_phi[1]);
        if(  number[0] == m_multigrid.max_iter())
            throw dg::Fail( m_p.eps_gamma);
    }
    //-------Compute Psi and derivatives
    dg::blas2::symv( m_dx_P, m_phi[0], m_dP[0][0]);
    dg::blas2::symv( m_dy_P, m_phi[0], m_dP[0][1]);
    if( !m_p.symmetric) dg::blas2::symv( m_dz, m_phi[0], m_dP[0][2]);
    dg::tensor::multiply3d( m_hh, //grad_perp
        m_dP[0][0], m_dP[0][1], m_dP[0][2], m_UE2, m_temp0, m_temp1);
    dg::blas1::subroutine( routines::ComputePsi(), m_phi[1],
        m_dP[0][0], m_dP[0][1], m_dP[0][2], m_UE2, m_temp0, m_temp1, m_binv);
#ifdef DG_MANUFACTURED
    dg::blas1::evaluate( m_phi[1], dg::plus_equals(), manufactured::SPhii{
        m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
        m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,time);
#endif //DG_MANUFACTURED
    //m_UE2 now contains u_E^2; also update derivatives
    dg::blas2::symv( m_dx_P, m_phi[1], m_dP[1][0]);
    dg::blas2::symv( m_dy_P, m_phi[1], m_dP[1][1]);
    if( !m_p.symmetric) dg::blas2::symv( m_dz, m_phi[1], m_dP[1][2]);
}
template<class Geometry, class IMatrix, class Matrix, class Container>
void Explicit<Geometry, IMatrix, Matrix, Container>::compute_apar(
    double time, std::array<std::array<Container,2>,2>& fields)
{
    //on input
    //fields[0][0] = n_e, fields[1][0]:= w_e
    //fields[0][1] = N_i, fields[1][1]:= W_i
    //----------Compute and set chi----------------------------//
    dg::blas1::axpby(  m_p.beta/m_p.mu[1], fields[0][1],
                      -m_p.beta/m_p.mu[0], fields[0][0], m_temp0);
    m_multigrid.project( m_temp0, m_multi_chi);
    for( unsigned u=0; u<m_p.stages; u++)
        m_multi_induction[u].set_chi( m_multi_chi[u]);

    //----------Compute right hand side------------------------//
    dg::blas1::pointwiseDot(  m_p.beta, fields[0][1], fields[1][1],
                             -m_p.beta, fields[0][0], fields[1][0],
                              0., m_temp0);
    //----------Invert Induction Eq----------------------------//
    m_old_apar.extrapolate( time, m_apar);
#ifdef DG_MANUFACTURED
    dg::blas1::evaluate( m_temp0, dg::plus_equals(), manufactured::SA{
        m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
        m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,time);
#endif //DG_MANUFACTURED
    std::vector<unsigned> number = m_multigrid.direct_solve(
        m_multi_induction, m_apar, m_temp0, m_p.eps_pol);
    m_old_apar.update( time, m_apar);
    if(  number[0] == m_multigrid.max_iter())
        throw dg::Fail( m_p.eps_pol);
    //----------Compute Derivatives----------------------------//
    dg::blas2::symv( m_dx_U, m_apar, m_dA[0]);
    dg::blas2::symv( m_dy_U, m_apar, m_dA[1]);
    if(!m_p.symmetric) dg::blas2::symv( m_dz, m_apar, m_dA[2]);

    //----------Compute Velocities-----------------------------//
    dg::blas1::axpby( 1., fields[1][0], -1./m_p.mu[0], m_apar, fields[1][0]);
    dg::blas1::axpby( 1., fields[1][1], -1./m_p.mu[1], m_apar, fields[1][1]);
}

template<class Geometry, class IMatrix, class Matrix, class Container>
void Explicit<Geometry, IMatrix, Matrix, Container>::compute_perp(
    double t,
    const std::array<std::array<Container,2>,2>& y,
    const std::array<std::array<Container,2>,2>& fields,
    std::array<std::array<Container,2>,2>& yp)
{
    //y[0] = N-1, y[1] = W; fields[0] = N, fields[1] = U
    for( unsigned i=0; i<2; i++)
    {
        ////////////////////perpendicular dynamics////////////////////////
        dg::blas2::symv( m_dx_N, y[0][i], m_dN[i][0]);
        dg::blas2::symv( m_dy_N, y[0][i], m_dN[i][1]);
        if(!m_p.symmetric) dg::blas2::symv( m_dz, y[0][i], m_dN[i][2]);
        dg::blas2::symv( m_dx_U, fields[1][i], m_dU[i][0]);
        dg::blas2::symv( m_dy_U, fields[1][i], m_dU[i][1]);
        if(!m_p.symmetric) dg::blas2::symv( m_dz, fields[1][i], m_dU[i][2]);
        if( m_p.beta == 0){
            dg::blas1::subroutine( routines::ComputePerpDrifts(
                m_p.mu[i], m_p.tau[i]),
                //species depdendent
                fields[0][i], m_dN[i][0], m_dN[i][1], m_dN[i][2],
                fields[1][i], m_dU[i][0], m_dU[i][1], m_dU[i][2],
                m_dP[i][0], m_dP[i][1], m_dP[i][2],
                //magnetic parameters
                m_b[0], m_b[1], m_b[2],
                m_curv[0], m_curv[1], m_curv[2],
                m_curvKappa[0], m_curvKappa[1], m_curvKappa[2],
                m_divCurvKappa, yp[0][i], yp[1][i]
            );
        }
        if( m_p.beta != 0){
            dg::blas1::subroutine( routines::ComputePerpDrifts(
                m_p.mu[i], m_p.tau[i]),
                //species depdendent
                fields[0][i], m_dN[i][0], m_dN[i][1], m_dN[i][2],
                fields[1][i], m_dU[i][0], m_dU[i][1], m_dU[i][2],
                m_dP[i][0], m_dP[i][1], m_dP[i][2],
                //induction
                m_apar, m_dA[0], m_dA[1], m_dA[2],
                //magnetic parameters
                m_b[0], m_b[1], m_b[2],
                m_curv[0], m_curv[1], m_curv[2],
                m_curvKappa[0], m_curvKappa[1], m_curvKappa[2],
                m_divCurvKappa, yp[0][i], yp[1][i]
            );
        }
    }
}

template<class Geometry, class IMatrix, class Matrix, class Container>
void Explicit<Geometry, IMatrix, Matrix, Container>::compute_parallel(
    double t,
    const std::array<std::array<Container,2>,2>& y,
    const std::array<std::array<Container,2>,2>& fields,
    std::array<std::array<Container,2>,2>& yp)
{
    //y[0] = N-1, y[1] = W; fields[0] = N, fields[1] = U
    for( unsigned i=0; i<2; i++)
    {
        //---------------------density--------------------------//
        //density: -Div ( NUb)
        m_ds_N.centered( y[0][i], m_dsN[i]);
        m_ds_U.backward( fields[1][i], m_dsU[i]);
        dg::blas1::pointwiseDot(-1., m_dsN[i], fields[1][i],
            -1., fields[0][i], m_dsU[i], 1., yp[0][i] );
        dg::blas1::pointwiseDot( -1., fields[0][i],fields[1][i],m_divb,
            1.,yp[0][i]);
        //density: + nu_par Delta_par N
        dg::blas1::pointwiseDot( m_p.nu_parallel, m_divb, m_dsN[i],
                                 1., yp[0][i]);
        m_ds_N.dss( y[0][i], m_dssN[i]);
        dg::blas1::axpby( m_p.nu_parallel, m_dssN[i], 1., yp[0][i]);
        //---------------------velocity-------------------------//
        // Burgers term: -0.5 ds U^2
        dg::blas1::pointwiseDot(fields[1][i], fields[1][i], m_temp1); //U^2
        m_ds_U.centered(-0.5, m_temp1, 1., yp[1][i]);
        // force terms: -tau/mu * ds lnN -1/mu * ds Phi
        // (These two terms converge slowly and require high z resolution)
        m_ds_N.forward(-m_p.tau[i]/m_p.mu[i], m_logn[i], 1.0, yp[1][i]);
        m_ds_P.forward(-1./m_p.mu[i], m_phi[i], 1.0, yp[1][i]);
        // diffusion: + nu_par Delta_par U
        dg::blas1::pointwiseDot(m_p.nu_parallel, m_divb, m_dsU[i],
                                1., yp[1][i]);
        m_ds_U.dss( fields[1][i], m_dssU[i]);
        dg::blas1::axpby( m_p.nu_parallel, m_dssU[i], 1., yp[1][i]);
    }
}

template<class Geometry, class IMatrix, class Matrix, class Container>
void Explicit<Geometry, IMatrix, Matrix, Container>::operator()(
    double t,
    const std::array<std::array<Container,2>,2>& y,
    std::array<std::array<Container,2>,2>& yp)
{
    /* y[0][0] := n_e - 1
       y[0][1] := N_i - 1
       y[1][0] := w_e
       y[1][1] := W_i
    */

    dg::Timer timer;
    double accu = 0.;//accumulated time
    timer.tic();
    // set m_phi[0]
    compute_phi( t, y[0]);

    // set m_phi[1], m_dP[0], m_dP[1] and m_UE2 --- needs m_phi[0]
    compute_psi( t);

    timer.toc();
    accu += timer.diff();
    #ifdef MPI_VERSION
        int rank;
        MPI_Comm_rank( MPI_COMM_WORLD, &rank);
        if(rank==0)
    #endif
    std::cout << "## Compute phi and psi               took "<<timer.diff()<<"s\t A: "<<accu<<"s\n";
    timer.tic();

    // Transform n-1 to n and n to logn
    dg::blas1::subroutine( routines::ComputeLogN(), y[0], m_fields[0], m_logn);

    // Compute Apar and m_U if necessary --- reads and updates m_fields[1]
    dg::blas1::copy( y[1], m_fields[1]);
    if( m_p.beta != 0)
        compute_apar( t, m_fields);

#if FELTORPERP == 1

    // Set perpendicular dynamics in yp
    compute_perp( t, y, m_fields, yp);

#else

    dg::blas1::copy( 0., yp);

#endif

    timer.toc();
    accu += timer.diff();
    #ifdef MPI_VERSION
        if(rank==0)
    #endif
    std::cout << "## Compute Apar and perp dynamics    took "<<timer.diff()<<"s\t A: "<<accu<<"s\n";
    timer.tic();

    // Add parallel dynamics --- needs m_logn
#if FELTORPARALLEL == 1
    compute_parallel( t, y, m_fields, yp);
#endif

    //Add source terms
    if( m_omega_source != 0 || m_omega_damping != 0)
    {
        if( m_fixed_profile )
            dg::blas1::subroutine( routines::ComputeSource(), m_s[0][0], y[0][0],
                m_profne, m_source, m_omega_source);
        else
            dg::blas1::axpby( m_omega_source, m_source, 0., m_s[0][0]);
        // -w_d ~n
        dg::blas1::pointwiseDot( -m_omega_damping, m_damping, y[0][0], 1.,  m_s[0][0]);
        // - w_d U
        dg::blas1::pointwiseDot( -m_omega_damping, m_damping, m_fields[1][0], 0.,  m_s[1][0]);
        dg::blas1::pointwiseDot( -m_omega_damping, m_damping, m_fields[1][1], 0.,  m_s[1][1]);
        //compute FLR corrections S_N = (1-0.5*mu*tau*Lap)*S_n
        dg::blas2::gemv( m_lapperpN, m_s[0][0], m_temp0);
        dg::blas1::axpby( 1., m_s[0][0], 0.5*m_p.tau[1]*m_p.mu[1], m_temp0, m_s[0][1]);
        // potential part of FLR correction S_N += -div*(mu S_n grad*Phi/B^2)
        dg::blas1::pointwiseDot( m_p.mu[1], m_s[0][0], m_binv, m_binv, 0., m_temp0);
        m_lapperpP.multiply_sigma( 1., m_temp0, m_phi[0], 1., m_s[0][1]);

        dg::blas1::axpby( 1., m_s, 1.0, yp);
    }


    if( m_full_system)
    {
#if FELTORPERP == 1
        /* y[0] := n_e - 1
           y[1] := N_i - 1
        */
        for( unsigned i=0; i<2; i++)
        {
            if( m_p.perp_diff == "hyperviscous")
            {
                dg::blas2::symv( m_lapperpN, y[0][i], m_temp0);
                dg::blas2::symv( -m_p.nu_perp, m_lapperpN, m_temp0, 1., yp[0][i]);
            }
            else // m_p.perp_diff == "viscous"
                dg::blas2::symv( -m_p.nu_perp, m_lapperpN, y[0][i],  1., yp[0][i]);
        }
        /* fields[1][0] := u_e
           fields[1][1] := U_i
        */
        for( unsigned i=0; i<2; i++)
        {
            if( m_p.perp_diff == "hyperviscous")
            {
                dg::blas2::symv( m_lapperpU, m_fields[1][i], m_temp0);
                dg::blas2::symv( -m_p.nu_perp, m_lapperpU, m_temp0, 1., yp[1][i]);
            }
            else // m_p.perp_diff == "viscous"
                dg::blas2::symv( -m_p.nu_perp, m_lapperpU,
                    m_fields[1][i],  1., yp[1][i]);
        }
#endif
        //------------------Add Resistivity--------------------------//
        dg::blas1::subroutine( routines::AddResistivity( m_p.eta, m_p.mu),
            m_fields[0][0], m_fields[0][1],
            m_fields[1][0], m_fields[1][1], yp[1][0], yp[1][1]);
    }
#ifdef DG_MANUFACTURED
    dg::blas1::evaluate( yp[0][0], dg::plus_equals(), manufactured::SNe{
        m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
        m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,t);
    dg::blas1::evaluate( yp[0][1], dg::plus_equals(), manufactured::SNi{
        m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
        m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,t);
    dg::blas1::evaluate( yp[1][0], dg::plus_equals(), manufactured::SUe{
        m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
        m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,t);
    dg::blas1::evaluate( yp[1][1], dg::plus_equals(), manufactured::SUi{
        m_p.mu[0],m_p.mu[1],m_p.tau[0],m_p.tau[1],m_p.eta,
        m_p.beta,m_p.nu_perp,m_p.nu_parallel},m_R,m_Z,m_P,t);
#endif //DG_MANUFACTURED
    timer.toc();
    accu += timer.diff();
    #ifdef MPI_VERSION
        if(rank==0)
    #endif
    std::cout << "## Add parallel dynamics and sources took "<<timer.diff()<<"s\t A: "<<accu<<"\n";
}
} //namespace feltor
