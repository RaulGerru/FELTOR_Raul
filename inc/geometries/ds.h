#pragma once

#include "dg/blas.h"
#include "dg/topology/geometry.h"
#include "dg/topology/derivatives.h"
#include "fieldaligned.h"
#ifdef MPI_VERSION
#include "dg/topology/mpi_derivatives.h"
#include "mpi_fieldaligned.h"
#endif //MPI_VERSION
#include "magnetic_field.h"

/*!@file
 *
 * This file includes the appropriate headers for parallel derivatives
 */

namespace dg{
namespace geo{

    /*!@class hide_ds_parameters2
    * @param f The vector to derive
    * @param g contains result on output (write only)
    * @note the vector sizes need to equal the grid size in the constructor
    */
    /*!@class hide_ds_parameters4
    * @param alpha Scalar
    * @param f The vector to derive
    * @param beta Scalar
    * @param g contains result on output (write only)
    * @note the vector sizes need to equal the grid size in the constructor
    */
/*!@class hide_ds_attention
@attention The \c div and \c symv member functions reliably converge only if fieldlines
do not(!) intersect the boundary and then only if the \c mx and \c my
    parameters are sufficiently high
*/

/**
* @brief Class for the evaluation of parallel derivatives
*
* This class discretizes the operators
\f$ \nabla_\parallel = \vec{v}\cdot \nabla = v^\zeta\partial_\zeta + v^\eta\partial_\eta + v^\varphi\partial_\varphi \f$,
\f$\nabla_\parallel^\dagger = -\nabla\cdot(\vec v .)\f$ and
\f$\Delta_\parallel=-\nabla_\parallel^\dagger\cdot\nabla_\parallel\f$
in arbitrary coordinates
@snippet ds_t.cu doxygen
 * @note The parallel Laplacian cannot be inverted as long as there are
 * closed fieldlines somewhere in the domain (which is virtually always true). There is therefore no norm parameter in the class.
@attention The \c div and \c symv member functions reliably work only if fieldlines
do not(!) intersect the boundary and then only if the \c mx and \c my
    parameters are sufficiently high
* @ingroup fieldaligned
* @tparam ProductGeometry must be either \c dg::aProductGeometry3d or \c dg::aProductMPIGeometry3d or any derivative
* @tparam IMatrix The type of the interpolation matrix
    - \c dg::IHMatrix, or \c dg::IDMatrix, \c dg::MIHMatrix, or \c dg::MIDMatrix
* @tparam Matrix The matrix class of the jump matrix
    - \c dg::HMatrix, or \c dg::DMatrix, \c dg::MHMatrix, or \c dg::MDMatrix
* @tparam container The container-class on which the interpolation matrix operates on
    - \c dg::HVec, or \c dg::DVec, \c dg::MHVec, or \c dg::MDVec
* @sa The pdf <a href="./parallel.pdf" target="_blank">parallel derivative</a> writeup
*/
template< class ProductGeometry, class IMatrix, class Matrix, class container >
struct DS
{
    typedef dg::geo::Fieldaligned<ProductGeometry, IMatrix, container> FA; //!< conveniently abbreviates underlying \c Fieldaligned type
    ///@brief No memory allocation; all member calls except construct are invalid
    DS(){}

    /**
     * @brief Create the magnetic unit vector field and construct

     * @copydoc hide_fieldaligned_physics_parameters
     * @param dir indicate the direction in the bracket operator and in symv
     * @copydoc hide_fieldaligned_numerics_parameters
     * @sa \c Fieldaligned
     */
    template <class Limiter>
    DS(const dg::geo::TokamakMagneticField& vec, const ProductGeometry& grid,
        dg::bc bcx = dg::NEU,
        dg::bc bcy = dg::NEU,
        Limiter limit = FullLimiter(),
        dg::direction dir = dg::centered,
        double eps = 1e-5,
        unsigned mx=10, unsigned my=10,
        double deltaPhi=-1):
        DS( FA( vec, grid, bcx, bcy, limit, eps, mx, my, deltaPhi), dir)
    {
    }
    /**
     * @brief Use the given vector field to construct
     *
     * @copydoc hide_fieldaligned_physics_parameters
     * @param dir indicate the direction in the bracket operator and in symv
     * @copydoc hide_fieldaligned_numerics_parameters
     * @sa \c Fieldaligned
     */
    template<class Limiter>
    DS(const dg::geo::CylindricalVectorLvl0& vec, const ProductGeometry& grid,
        dg::bc bcx = dg::NEU,
        dg::bc bcy = dg::NEU,
        Limiter limit = FullLimiter(),
        dg::direction dir = dg::centered,
        double eps = 1e-5,
        unsigned mx=10, unsigned my=10,
        double deltaPhi=-1):
        DS( FA( vec, grid, bcx, bcy, limit, eps, mx, my, deltaPhi), dir)
    {
    }
    /**
     * @brief Re-construct from a given \c Fieldaligned object
     *
     * @param fieldaligned this object will be used in all further member calls
     * @param dir indicate the direction in the bracket operator and in symv
     */
    DS( FA fieldaligned, dg::direction dir = dg::centered);
    /**
    * @brief Perfect forward parameters to one of the constructors
    * @tparam Params deduced by the compiler
    * @param ps parameters forwarded to constructors
    */
    template<class ...Params>
    void construct( Params&& ...ps)
    {
        //construct and swap
        *this = DS( std::forward<Params>( ps)...);
    }

    /*!@brief Set the direction used in the operator() and symv member
     * @param dir new direction
     */
    void set_direction( dg::direction dir){
        m_dir = dir;
    }

    ///@copydoc Fieldaligned::set_boundaries(dg::bc,double,double)
    void set_boundaries( dg::bc bcz, double left, double right){
        m_fa.set_boundaries( bcz, left, right);
    }
    ///@copydoc Fieldaligned::set_boundaries(dg::bc,const container&,const container&)
    void set_boundaries( dg::bc bcz, const container& left, const container& right){
        m_fa.set_boundaries( bcz, left, right);
    }
    ///@copydoc Fieldaligned::set_boundaries(dg::bc,const container&,double,double)
    void set_boundaries( dg::bc bcz, const container& global, double scal_left, double scal_right){
        m_fa.set_boundaries( bcz, global, scal_left, scal_right);
    }

    /**
    * @brief forward derivative \f$ g = \alpha \vec v \cdot \nabla f + \beta g\f$
    *
    * forward derivative \f$ g_i = \alpha \frac{1}{h_z}(f_{i+1} - f_{i}) + \beta g_i\f$
    * @copydoc hide_ds_parameters4
    */
    void forward( double alpha, const container& f, double beta, container& g){
        do_forward( alpha, f, beta, g);
    }
    /**
    * @brief backward derivative \f$ g = \alpha \vec v \cdot \nabla f + \beta g\f$
    *
    * backward derivative \f$ g_i = \alpha \frac{1}{2h_z}(f_{i} - f_{i-1}) + \beta g_i \f$
    * @copydoc hide_ds_parameters4
    */
    void backward( double alpha, const container& f, double beta, container& g){
        do_backward( alpha, f, beta, g);
    }
    /**
    * @brief centered derivative \f$ g = \alpha \vec v \cdot \nabla f + \beta g\f$
    *
    * centered derivative \f$ g_i = \alpha \frac{1}{2h_z}(f_{i+1} - f_{i-1}) + \beta g_i\f$
    * @copydoc hide_ds_parameters4
    */
    void centered( double alpha, const container& f, double beta, container& g){
        do_centered( alpha, f, beta, g);
    }
    /**
    * @brief backward derivative \f$ g = \vec v \cdot \nabla f \f$
    *
    * backward derivative \f$ g_i = \frac{1}{2h_z}(f_{i} - f_{i-1}) \f$
    * @copydoc hide_ds_parameters2
    */
    void backward( const container& f, container& g){
        do_backward(1.,f,0.,g);
    }
    /**
    * @brief forward derivative \f$ g = \vec v \cdot \nabla f \f$
    *
    * forward derivative \f$ g_i = \frac{1}{h_z}(f_{i+1} - f_{i})\f$
    * @copydoc hide_ds_parameters2
    */
    void forward( const container& f, container& g){
        do_forward(1.,f,0.,g);
    }
    /**
    * @brief centered derivative \f$ g = \vec v \cdot \nabla f \f$
    *
    * centered derivative \f$ g_i = \frac{1}{2h_z}(f_{i+1} - f_{i-1})\f$
    * @copydoc hide_ds_parameters2
    */
    void centered( const container& f, container& g){
        do_centered(1.,f,0.,g);
    }

    ///@brief forward divergence \f$ g = \alpha \nabla\cdot(\vec v f) + \beta g\f$
    ///@copydoc hide_ds_parameters4
    ///@copydoc hide_ds_attention
    ///@note divForward is the negative adjoint of backward
    void divForward( double alpha, const container& f, double beta, container& g){
        do_divForward( alpha, f, beta, g);
    }
    ///@brief backward divergence \f$ g = \alpha \nabla\cdot(\vec v f) + \beta g\f$
    ///@copydoc hide_ds_parameters4
    ///@copydoc hide_ds_attention
    ///@note divBackward is the negative adjoint of forward
    void divBackward( double alpha, const container& f, double beta, container& g){
        do_divBackward( alpha, f, beta, g);
    }
    ///@brief centered divergence \f$ g = \alpha \nabla\cdot(\vec v f) + \beta g\f$
    ///@copydoc hide_ds_parameters4
    ///@copydoc hide_ds_attention
    ///@note divCentered is the negative adjoint of centered
    void divCentered(double alpha, const container& f, double beta, container& g){
        do_divCentered( alpha, f, beta, g);
    }
    ///@brief forward divergence \f$ g = \nabla\cdot(\vec v f)\f$
    ///@copydoc hide_ds_parameters2
    ///@copydoc hide_ds_attention
    ///@note divForward is the negative adjoint of backward
    void divForward(const container& f, container& g){
        do_divForward( 1.,f,0.,g);
    }
    ///@brief backward divergence \f$ g = \nabla\cdot(\vec v f)\f$
    ///@copydoc hide_ds_parameters2
    ///@copydoc hide_ds_attention
    ///@note divBackward is the negative adjoint of forward
    void divBackward(const container& f, container& g){
        do_divBackward( 1.,f,0.,g);
    }
    ///@brief centered divergence \f$ g = \nabla\cdot(\vec v f)\f$
    ///@copydoc hide_ds_parameters2
    ///@copydoc hide_ds_attention
    ///@note divCentered is the negative adjoint of centered
    void divCentered(const container& f, container& g){
        do_divCentered( 1.,f,0.,g);
    }

    /**
    * @brief Discretizes \f$ g = \vec v\cdot \nabla f \f$
    *
    * dependent on dir given in constructor redirects to either \c forward(), \c backward() or \c centered()
    * @copydoc hide_ds_parameters2
    */
    void operator()( const container& f, container& g){
        ds( m_dir, 1., f, 0., g);
    }
    /**
    * @brief Discretizes \f$ g = \alpha \vec v\cdot \nabla f + \beta g \f$
    *
    * dependent on dir given in constructor redirects to either \c forward(), \c backward() or \c centered()
    * @copydoc hide_ds_parameters4
    */
    void operator()(double alpha, const container& f, double beta, container& g){
        ds(m_dir, alpha, f, beta, g);
    }


    /**
    * @brief Discretizes \f$ g = \vec v\cdot \nabla f \f$
    *
    * @param dir redirects to either \c forward(), \c backward() or \c centered()
    * @copydoc hide_ds_parameters2
    */
    void ds(dg::direction dir,  const container& f, container& g){
        ds(dir, 1., f, 0., g);
    }
    /**
    * @brief Discretizes \f$ g = \alpha \vec v\cdot \nabla f + \beta g \f$
    *
    * @param dir redirects to either \c forward(), \c backward() or \c centered()
    * @copydoc hide_ds_parameters4
    */
    void ds(dg::direction dir, double alpha, const container& f, double beta, container& g);
    /**
    * @brief Discretizes \f$ g = \nabla \cdot ( \vec v f) \f$
    *
    * @param dir redirects to either \c divForward(), \c divBackward() or \c divCentered()
    * @copydoc hide_ds_parameters2
     * @copydoc hide_ds_attention
    */
    void div(dg::direction dir,  const container& f, container& g){
        div(dir, 1., f, 0., g);
    }
    /**
    * @brief Discretizes \f$ g = \alpha \nabla \cdot( \vec v f) + \beta g \f$
    *
    * @param dir redirects to either \c divForward(), \c divBackward() or \c divCentered()
    * @copydoc hide_ds_parameters4
     * @copydoc hide_ds_attention
    */
    void div(dg::direction dir, double alpha, const container& f, double beta, container& g);

    /**
     * @brief Discretizes \f$ g = \nabla\cdot ( \vec v \vec v \cdot \nabla f )\f$
     *
     * If direction given in constructor is centered then centered followed by divCentered and adding jump terms is called, else a symmetric forward/backward discretization is chosen.
     * @copydoc hide_ds_parameters2
     * @copydoc hide_ds_attention
     */
    void symv( const container& f, container& g){ do_symv( 1., f, 0., g);}
    /**
     * @brief Discretizes \f$ g = \alpha \nabla\cdot ( \vec v \vec v \cdot \nabla f ) + \beta g\f$ as a symmetric matrix
     *
     * if direction given in constructor is centered then centered followed by divCentered and adding jump terms is called, else a symmetric forward/backward discretization is chosen.
     * @copydoc hide_ds_parameters4
     * @copydoc hide_ds_attention
     */
    void symv( double alpha, const container& f, double beta, container& g){ do_symv( alpha, f, beta, g);}
    /**
     * @brief Discretizes \f$ g = (\vec v\cdot \nabla)^2 f \f$
     *
     * The formula used is \f[ \nabla_\parallel^2 f = 2\left(\frac{f^+}{h_z^+ h_z^0} - \frac{f^0}{h_z^- h_z^+} + \frac{f^-}{h_z^-h_z^0}\right) \f]
     * @copydoc hide_ds_parameters2
     */
    void dss( const container& f, container& g){ do_dss( 1., f, 0., g);}
    /**
     * @brief Discretizes \f$ g = \alpha (\vec v\cdot \nabla)^2 f + \beta g \f$
     *
     * The formula used is \f[ \nabla_\parallel^2 f = 2\left(\frac{f^+}{h_z^+ h_z^0} - \frac{f^0}{h_z^- h_z^+} + \frac{f^-}{h_z^-h_z^0}\right) \f]
     * @copydoc hide_ds_parameters4
     */
    void dss( double alpha, const container& f, double beta, container& g){ do_dss( alpha, f, beta, g);}

    const container& weights()const {
        return m_vol3d;
    }
    const container& inv_weights()const {
        return m_inv3d;
    }
    const container& precond()const {
        return m_inv3d;
    }

    /**
    * @brief access the underlying Fieldaligned object for evaluate
    *
    * @return acces to fieldaligned object
    */
    const FA& fieldaligned() const{return m_fa;}
    private:
    void do_forward(double alpha, const container& f, double beta, container& dsf);
    void do_backward(double alpha, const container& f, double beta, container& dsf);
    void do_centered(double alpha, const container& f, double beta, container& dsf);
    void do_divForward(double alpha, const container& f, double beta, container& dsf);
    void do_divBackward(double alpha, const container& f, double beta, container& dsf);
    void do_divCentered(double alpha, const container& f, double beta, container& dsf);
    void do_symv(double alpha, const container& f, double beta, container& dsf);
    void do_dss(double alpha, const container& f, double beta, container& dsf);


    Fieldaligned<ProductGeometry, IMatrix, container> m_fa;
    container m_temp;
    container m_tempP, m_temp0, m_tempM;
    container m_vol3d, m_inv3d, m_weights_wo_vol;
    dg::direction m_dir;
    Matrix m_jumpX, m_jumpY;
};

///@cond
////////////////////////////////////DEFINITIONS////////////////////////////////////////

template<class Geometry, class I, class M, class container>
DS<Geometry, I, M,container>::DS( Fieldaligned<Geometry, I, container> fa, dg::direction dir): m_fa(fa)
{
    dg::assign( dg::create::volume(     fa.grid()), m_vol3d);
    dg::assign( dg::create::weights(    fa.grid()), m_weights_wo_vol);
    dg::assign( dg::create::inv_volume( fa.grid()), m_inv3d);
    dg::blas2::transfer( dg::create::jumpX( fa.grid(), fa.bcx()), m_jumpX);
    dg::blas2::transfer( dg::create::jumpY( fa.grid(), fa.bcy()), m_jumpY);
    m_temp = m_vol3d, m_tempP = m_temp, m_temp0 = m_temp, m_tempM = m_temp;
}

template<class G, class I, class M, class container>
inline void DS<G,I,M,container>::ds( dg::direction dir, double alpha, const container& f, double beta, container& dsf) {
    switch( dir){
        case dg::centered:
        return do_centered( alpha, f, beta, dsf);
        case dg::forward:
        return do_forward( alpha, f, beta, dsf);
        case dg::backward:
        return do_backward( alpha, f, beta, dsf);
    }
}
template<class G, class I, class M, class container>
inline void DS<G,I,M,container>::div( dg::direction dir, double alpha, const container& f, double beta, container& dsf) {
    switch( dir){
        case dg::centered:
        return do_divCentered( alpha, f, beta, dsf);
        case dg::forward:
        return do_divForward( alpha, f, beta, dsf);
        case dg::backward:
        return do_divBackward( alpha, f, beta, dsf);
    }
}

template<class G, class I, class M, class container>
void DS<G,I,M,container>::do_forward( double alpha, const container& f, double beta, container& dsf)
{
    //direct
    m_fa(einsPlus, f, m_tempP);
    dg::blas1::pointwiseDot( alpha, m_tempP, m_fa.hp_inv(), -alpha, f, m_fa.hp_inv(), beta, dsf);
}
template<class G,class I, class M, class container>
void DS<G,I,M,container>::do_backward( double alpha, const container& f, double beta, container& dsf)
{
    //direct
    m_fa(einsMinus, f, m_tempM);
    dg::blas1::pointwiseDot( alpha, f, m_fa.hm_inv(), -alpha, m_tempM, m_fa.hm_inv(), beta, dsf);
}
template<class G, class I, class M, class container>
void DS<G, I,M,container>::do_centered( double alpha, const container& f, double beta, container& dsf)
{
    //direct discretisation
    m_fa(einsPlus, f, m_tempP);
    m_fa(einsMinus, f, m_tempM);
    dg::blas1::pointwiseDot( alpha, m_tempP, m_fa.h0_inv(), -alpha, m_tempM, m_fa.h0_inv(), beta, dsf);
}
template<class G, class I, class M, class container>
void DS<G,I,M,container>::do_divBackward( double alpha, const container& f, double beta, container& dsf)
{
    //adjoint discretisation
    dg::blas1::pointwiseDot( 1., m_vol3d, f, m_fa.hp_inv(), 0., m_temp0);
    m_fa(einsPlusT, m_temp0, m_tempP);
    dg::blas1::pointwiseDot( alpha, m_temp0, m_inv3d, -alpha, m_tempP, m_inv3d, beta, dsf);
}
template<class G,class I, class M, class container>
void DS<G,I,M,container>::do_divForward( double alpha, const container& f, double beta, container& dsf)
{
    //adjoint discretisation
    dg::blas1::pointwiseDot( 1., m_vol3d, f, m_fa.hm_inv(),0., m_temp0);
    m_fa(einsMinusT, m_temp0, m_tempM);
    dg::blas1::pointwiseDot( alpha, m_tempM, m_inv3d, -alpha, m_temp0, m_inv3d, beta, dsf);
}
template<class G, class I, class M, class container>
void DS<G, I,M,container>::do_divCentered( double alpha, const container& f, double beta, container& dsf)
{
    //adjoint discretisation
    dg::blas1::pointwiseDot( 1., m_vol3d, f, m_fa.h0_inv(), 0.,m_temp0);
    m_fa(einsPlusT,  m_temp0, m_tempP);
    m_fa(einsMinusT, m_temp0, m_tempM);
    dg::blas1::pointwiseDot( alpha, m_tempM, m_inv3d, -alpha, m_tempP, m_inv3d, beta, dsf);

}

namespace detail{
struct ComputeDSS{
    ComputeDSS( double alpha, double beta):m_alpha(alpha), m_beta(beta){}
    DG_DEVICE
    void operator()( double& dssf, double fp, double f, double fm, double hp_inv, double h0_inv, double hm_inv) const{
        dssf = m_alpha*( 2.*fp*hp_inv*h0_inv - 2.*f*hp_inv*hm_inv + 2*fm*hm_inv*h0_inv) + m_beta*dssf;
        //dssf = m_alpha*(fp - 2.*f + fm)*h_inv*h_inv + m_beta*dssf;
    }
    private:
    double m_alpha, m_beta;
};
struct ComputeSymv{
    DG_DEVICE
    void operator()( double& fp, double fm, double h_inv, double vol3d) const{
        fp = ( fp-fm)*h_inv;
        fp = vol3d*fp*h_inv;
    }
    DG_DEVICE
    void operator()( double& fp, double& fm, double f0, double hp_inv, double hm_inv, double vol3d) const{
        fp = ( fp-f0)*hp_inv;
        fp = 0.5*vol3d*fp*hp_inv;
        fm = ( f0-fm)*hm_inv;
        fm = 0.5*vol3d*fm*hm_inv;
    }
};
struct ComputeSymvEnd{
    DG_DEVICE
    void operator()( double& fm, double fp, double weights) const{
        fm = ( fp-fm)/weights;
    }
    DG_DEVICE
    void operator()( double& efm, double fm, double fp, double efp, double weights) const{
        efm = ( efm- fm + fp -efp)/weights;
    }
};

}//namespace detail

template<class G,class I, class M, class container>
void DS<G,I,M,container>::do_symv( double alpha, const container& f, double beta, container& dsTdsf)
{

    if(m_dir == dg::centered) //does not converge with BC!!
    {
        m_fa(einsPlus, f, m_tempP);
        m_fa(einsMinus, f, m_tempM);
        dg::blas1::subroutine( detail::ComputeSymv(), m_tempP, m_tempM, m_fa.h0_inv(), m_vol3d);
        m_fa(einsPlusT,  m_tempP, m_temp);
        m_fa(einsMinusT, m_tempP, m_tempM);
        dg::blas1::subroutine( detail::ComputeSymvEnd(), m_temp,
            m_tempM, m_weights_wo_vol);
    }
    else
    {
        m_fa(einsPlus, f, m_tempP);
        m_fa(einsMinus, f, m_tempM);
        dg::blas1::subroutine( detail::ComputeSymv(), m_tempP, m_tempM, f,
            m_fa.hp_inv(), m_fa.hm_inv(), m_vol3d);
        m_fa(einsPlusT, m_tempP, m_temp0);
        m_fa(einsMinusT, m_tempM, m_temp);
        dg::blas1::subroutine( detail::ComputeSymvEnd(), m_temp,
            m_tempM, m_tempP, m_temp0, m_weights_wo_vol);
    }

    //     add jump terms
    dg::blas2::symv( -1., m_jumpX, f, 1., m_temp);
    dg::blas2::symv( -1., m_jumpY, f, 1., m_temp);
    //now volume without weights is missing

    dg::blas1::pointwiseDot( alpha, m_inv3d, m_weights_wo_vol, m_temp, beta, dsTdsf);
}

template<class G,class I, class M, class container>
void DS<G,I,M,container>::do_dss( double alpha, const container& f, double beta, container& dssf)
{
    m_fa(einsPlus,  f, m_tempP);
    m_fa(einsMinus, f, m_tempM);
    dg::blas1::subroutine( detail::ComputeDSS( alpha, beta),
            dssf, m_tempP, f, m_tempM, m_fa.hp_inv(), m_fa.h0_inv(), m_fa.hm_inv());
}
///@endcond


}//namespace geo

///@cond
template< class G, class I, class M, class V>
struct TensorTraits< geo::DS<G,I,M, V> >
{
    using value_type = double;
    using tensor_category = SelfMadeMatrixTag;
};
///@endcond
}//namespace dg
