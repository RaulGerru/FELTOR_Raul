#pragma once

#include "operator.h"
#include "dg/functors.h"
#include "dg/blas1.h"
#include "tensor.h"

namespace dg
{
///@brief Utility functions used in connection with the SparseTensor class
namespace tensor
{

///@addtogroup tensor
///@{

/**
 * @brief \f$ t^{ij} = \mu t^{ij} \ \forall i,j \f$
 *
 * Scale tensor with a Scalar or a Vector
 * @param t input (contains result on output)
 * @param mu all elements in t are scaled with mu
 * @copydoc hide_ContainerType
 */
template<class ContainerType0, class ContainerType1>
void scal( SparseTensor<ContainerType0>& t, const ContainerType1& mu)
{
    unsigned size=t.values().size();
    for( unsigned i=0; i<size; i++)
        dg::blas1::pointwiseDot( mu, t.values()[i], t.values()[i]);
}

///@cond
namespace detail
{
template<class value_type>
struct Multiply{
    DG_DEVICE
    void operator() ( value_type t00, value_type t01,
                      value_type t10, value_type t11,
                      value_type in0, value_type in1,
                      value_type& out0, value_type& out1) const
    {
        value_type tmp0 = DG_FMA(t00,in0 , t01*in1);
        value_type tmp1 = DG_FMA(t10,in0 , t11*in1);
        out1 = tmp1;
        out0 = tmp0;
    }
    DG_DEVICE
    void operator() ( value_type t00, value_type t01, value_type t02,
                      value_type t10, value_type t11, value_type t12,
                      value_type t20, value_type t21, value_type t22,
                      value_type in0, value_type in1, value_type in2,
                      value_type& out0, value_type& out1, value_type& out2) const
    {
        value_type tmp0 = DG_FMA( t00,in0 , (DG_FMA( t01,in1 , t02*in2)));
        value_type tmp1 = DG_FMA( t10,in0 , (DG_FMA( t11,in1 , t12*in2)));
        value_type tmp2 = DG_FMA( t20,in0 , (DG_FMA( t21,in1 , t22*in2)));
        out2 = tmp2;
        out1 = tmp1;
        out0 = tmp0;
    }
};
template<class value_type>
struct Determinant
{
    DG_DEVICE
    value_type operator()( value_type in) const{
        return 1./sqrt(in);
    }
    DG_DEVICE
    value_type operator() ( value_type t00, value_type t01,
                            value_type t10, value_type t11) const
    {
        return DG_FMA( t00,t11 , (-t10*t01));
    }
    DG_DEVICE
    value_type operator() ( value_type t00, value_type t01, value_type t02,
                            value_type t10, value_type t11, value_type t12,
                            value_type t20, value_type t21, value_type t22) const
    {
        return t00*this->operator()(t11, t12, t21, t22)
              -t01*this->operator()(t10, t12, t20, t22)
              +t02*this->operator()(t10, t11, t20, t21);
    }
};
template<class value_type>
struct InverseMultiply{
    DG_DEVICE
    void operator() ( value_type t00, value_type t01,
                      value_type t10, value_type t11,
                      value_type in0, value_type in1,
                      value_type& out0, value_type& out1) const
    {
        value_type dett = DG_FMA( t00,t11 , (-t10*t01));
        value_type tmp0 = DG_FMA( in0,t11 , (-in1*t01));
        value_type tmp1 = DG_FMA( t00,in1 , (-t10*in0));
        out1 = tmp1/dett;
        out0 = tmp0/dett;
    }
    DG_DEVICE
    void operator() ( value_type t00, value_type t01, value_type t02,
                      value_type t10, value_type t11, value_type t12,
                      value_type t20, value_type t21, value_type t22,
                      value_type in0, value_type in1, value_type in2,
                      value_type& out0, value_type& out1, value_type& out2) const
    {
        value_type dett = det( t00,t01,t02, t10,t11,t12, t20,t21,t22);

        value_type tmp0 = det( in0,t01,t02, in1,t11,t12, in2,t21,t22);
        value_type tmp1 = det( t00,in0,t02, t10,in1,t12, t20,in2,t22);
        value_type tmp2 = det( t00,t01,in0, t10,t11,in1, t20,t21,in2);
        out2 = tmp2/dett;
        out1 = tmp1/dett;
        out0 = tmp0/dett;
    }
    private:
    DG_DEVICE
    value_type det( value_type t00, value_type t01, value_type t02,
                    value_type t10, value_type t11, value_type t12,
                    value_type t20, value_type t21, value_type t22)const
    {
        return t00*DG_FMA(t11, t22, (-t12*t21))
              -t01*DG_FMA(t10, t22, (-t20*t12))
              +t02*DG_FMA(t10, t21, (-t20*t11));
    }
};
}//namespace detail
///@endcond
/**
 * @brief \f$ w^i = \sum_{i=0}^1t^{ij}v_j \text{ for } i\in \{0,1\}\f$
 *
 * Multiply a tensor with a vector in 2d.
 * Ignore the 3rd dimension in \c t.
 * @param t input Tensor
 * @param in0 (input) first component  of \c v  (may alias out0)
 * @param in1 (input) second component of \c v  (may alias out1)
 * @param out0 (output) first component  of \c w (may alias in0)
 * @param out1 (output) second component of \c w (may alias in1)
 * @note This function is just a shortcut for a call to \c dg::blas1::subroutine with the appropriate functor
 * @copydoc hide_ContainerType
 */
template<class ContainerType0, class ContainerType1, class ContainerType2, class ContainerType3, class ContainerType4>
void multiply2d( const SparseTensor<ContainerType0>& t, const ContainerType1& in0, const ContainerType2& in1, ContainerType3& out0, ContainerType4& out1)
{
    dg::blas1::subroutine( detail::Multiply<get_value_type<ContainerType0>>(),
                         t.value(0,0), t.value(0,1),
                         t.value(1,0), t.value(1,1),
                         in0,  in1,
                         out0, out1);
}

/**
 * @brief \f$ w^i = \sum_{i=0}^2t^{ij}v_j \text{ for } i\in \{0,1,2\}\f$
 *
 * Multiply a tensor with a vector in 3d.
 * @param t input Tensor
 * @param in0 (input)  first component of \c v  (may alias out0)
 * @param in1 (input)  second component of \c v (may alias out1)
 * @param in2 (input)  third component of \c v  (may alias out2)
 * @param out0 (output)  first component of \c w  (may alias in0)
 * @param out1 (output)  second component of \c w (may alias in1)
 * @param out2 (output)  third component of \c w  (may alias in2)
 * @note This function is just a shortcut for a call to \c dg::blas1::subroutine with the appropriate functor
 * @copydoc hide_ContainerType
 */
template<class ContainerType0, class ContainerType1, class ContainerType2, class ContainerType3, class ContainerType4, class ContainerType5, class ContainerType6>
void multiply3d( const SparseTensor<ContainerType0>& t, const ContainerType1& in0, const ContainerType2& in1, const ContainerType3& in2, ContainerType4& out0, ContainerType5& out1, ContainerType6& out2)
{
    dg::blas1::subroutine( detail::Multiply<get_value_type<ContainerType0>>(),
                         t.value(0,0), t.value(0,1), t.value(0,2),
                         t.value(1,0), t.value(1,1), t.value(1,2),
                         t.value(2,0), t.value(2,1), t.value(2,2),
                         in0, in1, in2,
                         out0, out1, out2);
}

/**
 * @brief \f$ v_j = \sum_{i=0}^1(t^{-1})_{ji}w^i \text{ for } i\in \{0,1\}\f$
 *
 * Multiply the inverse of a tensor \c t with a vector in 2d.
 * Ignore the 3rd dimension in \c t. The inverse of \c t is computed inplace.
 * @param t input Tensor
 * @param in0 (input) first component of \c w    (may alias out0)
 * @param in1 (input) second component of \c w   (may alias out1)
 * @param out0 (output) first component of \c v  (may alias in0)
 * @param out1 (output) second component of \c v (may alias in1)
 * @copydoc hide_ContainerType
 */
template<class ContainerType0, class ContainerType1, class ContainerType2, class ContainerType3, class ContainerType4>
void inv_multiply2d( const SparseTensor<ContainerType0>& t, const ContainerType1& in0, const ContainerType2& in1, ContainerType3& out0, ContainerType4& out1)
{
    dg::blas1::subroutine( detail::InverseMultiply<get_value_type<ContainerType0>>(),
                         t.value(0,0), t.value(0,1),
                         t.value(1,0), t.value(1,1),
                         in0,  in1,
                         out0, out1);
}

/**
 * @brief \f$ v_j = \sum_{i=0}^2(t^{-1})_{ji}w^i \text{ for } i\in \{0,1,2\}\f$i
 *
 * Multiply the inverse of a tensor with a vector in 3d.
 * The inverse of \c t is computed inplace.
 * @param t input Tensor
 * @param in0 (input)  first component  of \c w (may alias out0)
 * @param in1 (input)  second component of \c w (may alias out1)
 * @param in2 (input)  third component  of \c w (may alias out2)
 * @param out0 (output)  first component  of \c v (may alias in0)
 * @param out1 (output)  second component of \c v (may alias in1)
 * @param out2 (output)  third component  of \c v (may alias in2)
 * @note This function is just a shortcut for a call to \c dg::blas1::subroutine with the appropriate functor
 * @copydoc hide_ContainerType
 */
template<class ContainerType0, class ContainerType1, class ContainerType2, class ContainerType3, class ContainerType4, class ContainerType5, class ContainerType6>
void inv_multiply3d( const SparseTensor<ContainerType0>& t, const ContainerType1& in0, const ContainerType2& in1, const ContainerType3& in2, ContainerType4& out0, ContainerType5& out1, ContainerType6& out2)
{
    dg::blas1::subroutine( detail::InverseMultiply<get_value_type<ContainerType0>>(),
                         t.value(0,0), t.value(0,1), t.value(0,2),
                         t.value(1,0), t.value(1,1), t.value(1,2),
                         t.value(2,0), t.value(2,1), t.value(2,2),
                         in0, in1, in2,
                         out0, out1, out2);
}

/**
* @brief \f$\det_{2d}( t)\f$
*
* Compute the minor determinant of a tensor \f$ \det_{2d}(t) := t_{00}t_{01}-t_{10}t_{11}\f$.
* @param t the input tensor
* @return the upper left minor determinant of \c t
* @copydoc hide_ContainerType
*/
template<class ContainerType>
ContainerType determinant2d( const SparseTensor<ContainerType>& t)
{
    ContainerType det = t.value(0,0);
    dg::blas1::evaluate( det, dg::equals(), detail::Determinant<get_value_type<ContainerType>>(),
                           t.value(0,0), t.value(0,1),
                           t.value(1,0), t.value(1,1));
    return det;
}

/**
* @brief \f$\det( t)\f$
*
* Compute the determinant of a 3d tensor:
* \f$ \det(t) := t_{00}t_{11}t_{22} + t_{01}t_{12}t_{20} + \ldots - t_{22}t_{10}t_{01}\f$.
* @param t the input tensor
* @return the determinant of t
* @copydoc hide_ContainerType
*/
template<class ContainerType>
ContainerType determinant( const SparseTensor<ContainerType>& t)
{
    ContainerType det = t.value(0,0);
    dg::blas1::evaluate( det, dg::equals(), detail::Determinant<get_value_type<ContainerType>>(),
                           t.value(0,0), t.value(0,1), t.value(0,2),
                           t.value(1,0), t.value(1,1), t.value(1,2),
                           t.value(2,0), t.value(2,1), t.value(2,2));
    return det;
}

/**
 * @brief \f$ \sqrt{\det_{2d}(t)}^{-1}\f$
 *
 * Compute the sqrt of the inverse minor determinant of a tensor.
 * This is a convenience function that is equivalent to
 * @code
    ContainerType vol=determinant2d(t);
    dg::blas1::transform(vol, vol, dg::INVERT<>());
    dg::blas1::transform(vol, vol, dg::SQRT<>());
    @endcode
 * @param t the input tensor
 * @return the inverse square root of the determinant of \c t
 * @copydoc hide_ContainerType
 */
template<class ContainerType>
ContainerType volume2d( const SparseTensor<ContainerType>& t)
{
    ContainerType vol=determinant2d(t);
    dg::blas1::transform(vol, vol, detail::Determinant<get_value_type<ContainerType>>());
    return vol;
}

/**
 * @brief \f$ \sqrt{\det(t)}^{-1}\f$
 *
 * Compute the sqrt of the inverse determinant of a 3d tensor.
 * This is a convenience function that is equivalent to
 * @code
    ContainerType vol=determinant(t);
    dg::blas1::transform(vol, vol, dg::INVERT<>());
    dg::blas1::transform(vol, vol, dg::SQRT<>());
    @endcode
 * @param t the input tensor
 * @return the inverse square root of the determinant of \c t
 * @copydoc hide_ContainerType
 */
template<class ContainerType>
ContainerType volume( const SparseTensor<ContainerType>& t)
{
    ContainerType vol=determinant(t);
    dg::blas1::transform(vol, vol, detail::Determinant<get_value_type<ContainerType>>());
    return vol;
}

///@}

}//namespace tensor
}//namespace dg
