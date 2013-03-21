#ifndef _DG_BLAS_PRECONDITIONER_
#define _DG_BLAS_PRECONDITIONER_

#include <thrust/tuple.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/transform.h>
#include <thrust/inner_product.h>

#include "../preconditioner.cuh"
#include "thrust_vector.cuh" //load thrust_vector BLAS1 routines
#include "../vector_categories.h"

namespace dg{
namespace blas2{
namespace detail{

template< class Preconditioner> 
struct Diagonal_Symv_Functor
{
    typedef typename Preconditioner::value_type value_type;
    typedef thrust::tuple< value_type, int> Pair;

    Diagonal_Symv_Functor( value_type alpha, value_type beta, const Preconditioner& p ): p_(p), alpha(alpha), beta(beta) {}
    __host__ __device__
        value_type operator()(const value_type& x,  const Pair& p)
        {
            value_type y = alpha*x *p_(thrust::get<1>(p))
                        + beta*thrust::get<0>(p);
            return y;
        }
  private:
    const Preconditioner p_;
    value_type alpha, beta;
};

template< class Preconditioner> 
struct Diagonal_Dot_Functor
{
    typedef typename Preconditioner::value_type value_type;
    typedef thrust::tuple< value_type, int> Pair; 

    Diagonal_Dot_Functor( const Preconditioner& p): p_(p){}
    __host__ __device__
    value_type operator()( const value_type& x, const Pair& p) 
    {
        //generalized Multiplication
        return x*thrust::get<0>(p)*p_(thrust::get<1>(p));
    }

  private:
    const Preconditioner p_;
};



template< class Matrix, class Vector>
inline typename Matrix::value_type doDot( const Vector& x, const Matrix& m, const Vector& y, DiagonalPreconditionerTag, ThrustVectorTag)
{
    return thrust::inner_product(  x.begin(), x.end(), 
                            thrust::make_zip_iterator( thrust::make_tuple( y.begin(), thrust::make_counting_iterator(0)) ), 
                            0.0,
                            thrust::plus<double>(),
                            detail::Diagonal_Dot_Functor<Matrix>( m)
                            );
}

template< class Matrix, class Vector>
inline typename Matrix::value_type doDot( const Matrix& m, const Vector& x, dg::DiagonalPreconditionerTag, dg::ThrustVectorTag)
{
    return doDot( x,m,x, dg::DiagonalPreconditionerTag(), dg::ThrustVectorTag());
}

template< class Matrix, class Vector>
inline void doSymv(  
              typename Matrix::value_type alpha, 
              const Matrix& m,
              const Vector& x, 
              typename Matrix::value_type beta, 
              Vector& y, 
              DiagonalPreconditionerTag,
              ThrustVectorTag)
{
    //std::cout << "Hello Preconditioner!\n";
    if( alpha == 0)
    {
        if( beta == 1) 
            return;
        dg::blas1::detail::doAxpby( 0., x, beta, y, dg::ThrustVectorTag());
        return;
    }
    thrust::transform( x.begin(), x.end(), 
                       thrust::make_zip_iterator( 
                            thrust::make_tuple( y.begin(), thrust::make_counting_iterator<int>(0)) ), 
                       y.begin(),
                       detail::Diagonal_Symv_Functor<Matrix>( alpha, beta, m)
                      );
}
template< class Matrix, class Vector>
inline void doSymv(  
              const Matrix& m, 
              const Vector& x,
              Vector& y, 
              DiagonalPreconditionerTag,
              ThrustVectorTag)
{
    doSymv( 1., m, x, 0., y, dg::DiagonalPreconditionerTag(), dg::ThrustVectorTag());
}

//identities
template< class Vector>
inline void doSymv( const Identity<typename Vector::value_type>& m, const Vector& x, Vector& y, IdentityTag, ThrustVectorTag)
{
    dg::blas1::detail::doAxpby( 1., x, 1., y, dg::ThrustVectorTag());
}
                    
template< class Vector>
inline void doSymv(  
              typename Vector::value_type alpha, 
              const Identity<typename Vector::value_type>& m,
              const Vector& x, 
              typename Vector::value_type beta, 
              Vector& y, 
              IdentityTag,
              ThrustVectorTag)
{
    //std::cout << "Hello identity!\n";
    dg::blas1::detail::doAxpby( alpha, x, beta, y, dg::ThrustVectorTag());
}

template< class Vector>
inline typename Vector::value_type doDot( 
                const Vector& x, 
                const Identity<typename Vector::value_type>& m, 
                const Vector& y, 
                IdentityTag, ThrustVectorTag)
{
    return dg::blas1::detail::doDot( x, y, dg::ThrustVectorTag());
}

template< class Vector>
inline typename Vector::value_type doDot( 
                const Identity<typename Vector::value_type>& m, 
                const Vector& x, dg::IdentityTag, dg::ThrustVectorTag)
{
    return dg::blas1::detail::doDot( x, x, dg::ThrustVectorTag());
}

}//namespace detail
} //namespace blas2
} //namespace dg
#endif //_DG_BLAS_PRECONDITIONER_
