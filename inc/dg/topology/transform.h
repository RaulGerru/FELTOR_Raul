#pragma once
#include "topological_traits.h"
#include "multiply.h"
#include "base_geometry.h"
#include "weights.h"


namespace dg
{
/**
 * @brief Pull back a function defined in physical coordinates to the curvilinear (computational) coordinate system
 *
 * Pullback is equivalent to the following:
 *
 * -# generate the list of physical space coordinates (e.g. in 2d \f$ x_i = x(\zeta_i, \eta_i),\ y_i = y(\zeta_i, \eta_i)\f$ for all \c i) using the map member of the grid e.g. aRealGeometry2d::map()
 * -#  evaluate the given function or functor at these coordinates and store the result in the output vector (e.g. in 2d  \f$ v_i = f(x_i,y_i)\f$ for all \c i)
 *.

 @note the grid defines what its physical coordinates are, i.e. it could be either Cartesian or Cylindrical coordinates
 * @tparam Functor The binary (for 2d grids) or ternary (for 3d grids) function or functor with signature: <tt>real_type ( real_type x, real_type y) ; real_type ( real_type x, real_type y, real_type z) </tt>
 * @param f The function defined in physical coordinates
 * @param g a two- or three dimensional Geometry (\c g.map() is used to evaluate \c f)
 * @note Template deduction for the Functor will fail if you overload functions with different
 dimensionality (e.g. real_type sine( real_type x) and real_type sine(real_type x, real_type y) )
 * You will want to rename those uniquely
 *
 * @return The output vector \c v as a host vector
 * @ingroup pullback
 * @sa If the function is defined in computational space coordinates, then use \c dg::evaluate
 */
template< class Functor, class real_type>
thrust::host_vector<real_type> pullback( const Functor& f, const aRealGeometry2d<real_type>& g)
{
    std::vector<thrust::host_vector<real_type> > map = g.map();
    thrust::host_vector<real_type> vec( g.size());
    for( unsigned i=0; i<g.size(); i++)
        vec[i] = f( map[0][i], map[1][i]);
    return vec;
}

///@copydoc pullback(const Functor&,const aRealGeometry2d&)
///@ingroup pullback
template< class Functor, class real_type>
thrust::host_vector<real_type> pullback( const Functor& f, const aRealGeometry3d<real_type>& g)
{
    std::vector<thrust::host_vector<real_type> > map = g.map();
    thrust::host_vector<real_type> vec( g.size());
    for( unsigned i=0; i<g.size(); i++)
        vec[i] = f( map[0][i], map[1][i], map[2][i]);
    return vec;
}

#ifdef MPI_VERSION

///@copydoc pullback(const Functor&,const aRealGeometry2d&)
///@ingroup pullback
template< class Functor, class real_type>
MPI_Vector<thrust::host_vector<real_type> > pullback( const Functor& f, const aRealMPIGeometry2d<real_type>& g)
{
    std::vector<MPI_Vector<thrust::host_vector<real_type> > > map = g.map();
    thrust::host_vector<real_type> vec( g.local().size());
    for( unsigned i=0; i<g.local().size(); i++)
        vec[i] = f( map[0].data()[i], map[1].data()[i]);
    return MPI_Vector<thrust::host_vector<real_type> >( vec, g.communicator());
}

///@copydoc pullback(const Functor&,const aRealGeometry2d&)
///@ingroup pullback
template< class Functor, class real_type>
MPI_Vector<thrust::host_vector<real_type> > pullback( const Functor& f, const aRealMPIGeometry3d<real_type>& g)
{
    std::vector<MPI_Vector<thrust::host_vector<real_type> > > map = g.map();
    thrust::host_vector<real_type> vec( g.local().size());
    for( unsigned i=0; i<g.local().size(); i++)
        vec[i] = f( map[0].data()[i], map[1].data()[i], map[2].data()[i]);
    return MPI_Vector<thrust::host_vector<real_type> >( vec, g.communicator());
}

#endif //MPI_VERSION

/**
 * @brief Push forward a vector from cylindrical or Cartesian to a new coordinate system
 *
 * Computes \f[ v^x(x,y) = x_R (x,y) v^R(R(x,y), Z(x,y)) + x_Z v^Z(R(x,y), Z(x,y)) \\
                v^y(x,y) = y_R (x,y) v^R(R(x,y), Z(x,y)) + y_Z v^Z(R(x,y), Z(x,y)) \f]
   where \f$ x_R = \frac{\partial x}{\partial R}\f$, ...
 * @tparam Functor1 Binary or Ternary functor
 * @tparam Functor2 Binary or Ternary functor
 * @copydoc hide_container_geometry
 * @param vR input R-component in cylindrical coordinates
 * @param vZ input Z-component in cylindrical coordinates
 * @param vx x-component of vector (gets properly resized)
 * @param vy y-component of vector (gets properly resized)
 * @param g The geometry object
 * @ingroup pullback
 */
template<class Functor1, class Functor2, class container, class Geometry>
void pushForwardPerp( const Functor1& vR, const Functor2& vZ,
        container& vx, container& vy,
        const Geometry& g)
{
    using host_vec = get_host_vector<Geometry>;
    host_vec out1 = pullback( vR, g);
    host_vec out2 = pullback( vZ, g);
    dg::tensor::multiply2d(g.jacobian(), out1, out2, out1, out2);
    dg::assign( out1, vx);
    dg::assign( out2, vy);
}

/**
 * @brief Push forward a vector from cylindrical or Cartesian to a new coordinate system
 *
 * Computes \f[ v^x(x,y) = x_R (x,y) v^R(R(x,y), Z(x,y)) + x_Z v^Z(R(x,y), Z(x,y)) \\
                v^y(x,y) = y_R (x,y) v^R(R(x,y), Z(x,y)) + y_Z v^Z(R(x,y), Z(x,y)) \f]
   where \f$ x_R = \frac{\partial x}{\partial R}\f$, ...
 * @tparam Functor1 Binary or Ternary functor
 * @tparam Functor2 Binary or Ternary functor
 * @tparam Functor3 Binary or Ternary functor
 * @copydoc hide_container_geometry
 * @param vR input R-component in cartesian or cylindrical coordinates
 * @param vZ input Z-component in cartesian or cylindrical coordinates
 * @param vPhi input Z-component in cartesian or cylindrical coordinates
 * @param vx x-component of vector (gets properly resized)
 * @param vy y-component of vector (gets properly resized)
 * @param vz z-component of vector (gets properly resized)
 * @param g The geometry object
 * @ingroup pullback
 */
template<class Functor1, class Functor2, class Functor3, class container, class Geometry>
void pushForward( const Functor1& vR, const Functor2& vZ, const Functor3& vPhi,
        container& vx, container& vy, container& vz,
        const Geometry& g)
{
    using host_vec = get_host_vector<Geometry>;
    host_vec out1 = pullback( vR, g);
    host_vec out2 = pullback( vZ, g);
    host_vec out3 = pullback( vPhi, g);
    dg::tensor::multiply3d(g.jacobian(), out1, out2, out3, out1, out2, out3);
    dg::assign( out1, vx);
    dg::assign( out2, vy);
    dg::assign( out3, vz);
}

/**
 * @brief Push forward a symmetric 2d tensor from cylindrical or Cartesian to a new coordinate system
 *
 * Computes \f[
 \chi^{xx}(x,y) = x_R x_R \chi^{RR} + 2x_Rx_Z \chi^{RZ} + x_Zx_Z\chi^{ZZ} \\
 \chi^{xy}(x,y) = x_R x_R \chi^{RR} + (x_Ry_Z+y_Rx_Z) \chi^{RZ} + x_Zx_Z\chi^{ZZ} \\
 \chi^{yy}(x,y) = y_R y_R \chi^{RR} + 2y_Ry_Z \chi^{RZ} + y_Zy_Z\chi^{ZZ} \\
               \f]
   where \f$ x_R = \frac{\partial x}{\partial R}\f$, ...
 * @tparam FunctorRR Binary or Ternary functor
 * @tparam FunctorRZ Binary or Ternary functor
 * @tparam FunctorZZ Binary or Ternary functor
 * @copydoc hide_container_geometry
 * @param chiRR input RR-component in cylindrical coordinates
 * @param chiRZ input RZ-component in cylindrical coordinates
 * @param chiZZ input ZZ-component in cylindrical coordinates
 * @param chi tensor (gets properly resized)
 * @param g The geometry object
 * @ingroup pullback
 */
template<class FunctorRR, class FunctorRZ, class FunctorZZ, class container, class Geometry>
void pushForwardPerp( const FunctorRR& chiRR, const FunctorRZ& chiRZ, const FunctorZZ& chiZZ,
        SparseTensor<container>& chi,
        const Geometry& g)
{
    using host_vec = get_host_vector<Geometry>;
    host_vec chiRR_ = pullback( chiRR, g);
    host_vec chiRZ_ = pullback( chiRZ, g);
    host_vec chiZZ_ = pullback( chiZZ, g);

    const dg::SparseTensor<container> jac = g.jacobian();
    std::vector<container> values( 5);
    dg::assign( dg::evaluate( dg::zero,g), values[0]);
    dg::assign( dg::evaluate( dg::one, g), values[1]);
    dg::assign( chiRR_, values[2]);
    dg::assign( chiRZ_, values[3]);
    dg::assign( chiZZ_, values[4]);
    chi.idx(0,0)=2, chi.idx(0,1)=chi.idx(1,0)=3, chi.idx(1,1)=4;
    chi.idx(2,0)=chi.idx(2,1)=chi.idx(0,2)=chi.idx(1,2) = 0;
    chi.idx(2,2)=1;
    chi.values() = values;
    //we do not need 3rd dimension here

    container tmp00(jac.value(0,0)), tmp01(tmp00), tmp10(tmp00), tmp11(tmp00);
    // multiply Chi*t -> tmp
    dg::tensor::multiply2d( chi, jac.value(0,0), jac.value(1,0), tmp00, tmp10);
    dg::tensor::multiply2d( chi, jac.value(0,1), jac.value(1,1), tmp01, tmp11);
    // multiply tT * tmp -> Chi
    SparseTensor<container> transpose = jac.transpose();
    dg::tensor::multiply2d( transpose, tmp00, tmp01, chi.values()[2], chi.values()[3]);
    dg::tensor::multiply2d( transpose, tmp10, tmp11, chi.values()[3], chi.values()[4]);
}

namespace create{
///@addtogroup metric
///@{



/**
 * @brief Create the volume element on the grid (including weights!!)
 *
 * This is the same as the weights multiplied by the volume form \f$ \sqrt{g}\f$
 * @copydoc hide_geometry
 * @param g Geometry object
 *
 * @return  The volume form
 */
template< class Geometry>
get_host_vector<Geometry> volume( const Geometry& g)
{
    using host_vector = get_host_vector<Geometry>;
    host_vector vol = dg::tensor::volume(g.metric());
    host_vector weights = dg::create::weights( g);
    dg::blas1::pointwiseDot( weights, vol, vol);
    return vol;
}

/**
 * @brief Create the inverse volume element on the grid (including weights!!)
 *
 * This is the same as the inv_weights divided by the volume form \f$ \sqrt{g}\f$
 * @copydoc hide_geometry
 * @param g Geometry object
 *
 * @return  The inverse volume form
 */
template< class Geometry>
get_host_vector<Geometry> inv_volume( const Geometry& g)
{
    using host_vector = get_host_vector<Geometry>;
    using real_type = get_value_type<host_vector>;
    host_vector vol = volume(g);
    dg::blas1::transform( vol, vol, dg::INVERT<real_type>());
    return vol;
}

///@}
}//namespace create

} //namespace dg
