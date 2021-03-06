#pragma once

#include "fluxfunctions.h"

/*!@file
 *
 * MagneticField objects
 */
namespace dg
{
namespace geo
{
/*!@class hide_toroidal_approximation_note
 @note We implicitly assume the toroidal field line approximation, i.e. all curvature
 and other perpendicular terms assume that the perpendicular
 direction lies within the
 R-Z planes of a cylindrical grid (The plane \f$ \perp \hat{ e}_\varphi\f$ )
 */

///@addtogroup magnetic
///@{

/**
* @brief A tokamak field as given by R0, Psi and Ipol

 This is the representation of toroidally axisymmetric magnetic fields that can be modeled in the form
 \f$
 \vec B(R,Z,\varphi) = \frac{R_0}{R} \left( I(\psi_p) \hat e_\varphi + \nabla \psi_p \times \hat e_\varphi\right)
 \f$
 where \f$ R_0\f$ is a normalization constant, \f$ I\f$ the poloidal current
 and \f$ \psi_p\f$ the poloidal flux function.
 @snippet ds_t.cu doxygen
*/
struct TokamakMagneticField
{
    ///as long as the field stays empty the access functions are undefined
    TokamakMagneticField(){}
    TokamakMagneticField( double R0, const CylindricalFunctorsLvl2& psip, const
            CylindricalFunctorsLvl1& ipol): R0_(R0), psip_(psip), ipol_(ipol){}
    void set( double R0, const CylindricalFunctorsLvl2& psip, const
            CylindricalFunctorsLvl1& ipol)
    {
        R0_=R0;
        psip_=psip;
        ipol_=ipol;
    }
    /// \f$ R_0 \f$
    double R0()const {return R0_;}
    /// \f$ \psi_p(R,Z)\f$, where R, Z are cylindrical coordinates
    const CylindricalFunctor& psip()const{return psip_.f();}
    /// \f$ \partial_R \psi_p(R,Z)\f$, where R, Z are cylindrical coordinates
    const CylindricalFunctor& psipR()const{return psip_.dfx();}
    /// \f$ \partial_Z \psi_p(R,Z)\f$, where R, Z are cylindrical coordinates
    const CylindricalFunctor& psipZ()const{return psip_.dfy();}
    /// \f$ \partial_R\partial_R \psi_p(R,Z)\f$, where R, Z are cylindrical coordinates
    const CylindricalFunctor& psipRR()const{return psip_.dfxx();}
    /// \f$ \partial_R\partial_Z \psi_p(R,Z)\f$, where R, Z are cylindrical coordinates
    const CylindricalFunctor& psipRZ()const{return psip_.dfxy();}
    /// \f$ \partial_Z\partial_Z \psi_p(R,Z)\f$, where R, Z are cylindrical coordinates
    const CylindricalFunctor& psipZZ()const{return psip_.dfyy();}
    /// \f$ I(\psi_p) \f$ the current
    const CylindricalFunctor& ipol()const{return ipol_.f();}
    /// \f$ \partial_R I(\psi_p) \f$
    const CylindricalFunctor& ipolR()const{return ipol_.dfx();}
    /// \f$ \partial_Z I(\psi_p) \f$
    const CylindricalFunctor& ipolZ()const{return ipol_.dfy();}

    const CylindricalFunctorsLvl2& get_psip() const{return psip_;}
    const CylindricalFunctorsLvl1& get_ipol() const{return ipol_;}

    private:
    double R0_;
    CylindricalFunctorsLvl2 psip_;
    CylindricalFunctorsLvl1 ipol_;
};

///@cond
CylindricalFunctorsLvl1 periodify( const CylindricalFunctorsLvl1& in, double R0, double R1, double Z0, double Z1, bc bcx, bc bcy)
{
    return CylindricalFunctorsLvl1(
            Periodify( in.f(),   R0, R1, Z0, Z1, bcx, bcy),
            Periodify( in.dfx(), R0, R1, Z0, Z1, inverse(bcx), bcy),
            Periodify( in.dfy(), R0, R1, Z0, Z1, bcx, inverse(bcy)));
}
CylindricalFunctorsLvl2 periodify( const CylindricalFunctorsLvl2& in, double R0, double R1, double Z0, double Z1, bc bcx, bc bcy)
{
    return CylindricalFunctorsLvl2(
            Periodify( in.f(),   R0, R1, Z0, Z1, bcx, bcy),
            Periodify( in.dfx(), R0, R1, Z0, Z1, inverse(bcx), bcy),
            Periodify( in.dfy(), R0, R1, Z0, Z1, bcx, inverse(bcy)),
            Periodify( in.dfxx(), R0, R1, Z0, Z1, bcx, bcy),
            Periodify( in.dfxy(), R0, R1, Z0, Z1, inverse(bcx), inverse(bcy)),
            Periodify( in.dfyy(), R0, R1, Z0, Z1, bcx, bcy));
}
///@endcond
/**
 * @brief Use dg::geo::Periodify to periodify every function the magnetic field
 *
 * Note that derivatives are periodified with dg::inverse boundary conditions
 * @param mag The magnetic field to periodify
 * @param R0 left boundary in R
 * @param R1 right boundary in R
 * @param Z0 lower boundary in Z
 * @param Z1 upper boundary in Z
 * @param bcx boundary condition in x (determines how function is periodified)
 * @param bcy boundary condition in y (determines how function is periodified)
 * @note So far this was only tested for Neumann boundary conditions. It is uncertain if Dirichlet boundary conditions work
 *
 * @return new periodified magnetic field
 */
TokamakMagneticField periodify( const TokamakMagneticField& mag, double R0, double R1, double Z0, double Z1, dg::bc bcx, dg::bc bcy)
{
    //what if Dirichlet BC in the current? Won't that generate a NaN?
    return TokamakMagneticField( mag.R0(),
            periodify( mag.get_psip(), R0, R1, Z0, Z1, bcx, bcy),
            //what if Dirichlet BC in the current? Won't that generate a NaN?
            periodify( mag.get_ipol(), R0, R1, Z0, Z1, bcx, bcy));
}

///@brief \f$   |B| = R_0\sqrt{I^2+(\nabla\psi)^2}/R   \f$
struct Bmodule : public aCylindricalFunctor<Bmodule>
{
    Bmodule( const TokamakMagneticField& mag): mag_(mag)  { }
    double do_compute(double R, double Z) const
    {
        double psipR = mag_.psipR()(R,Z), psipZ = mag_.psipZ()(R,Z), ipol = mag_.ipol()(R,Z);
        return mag_.R0()/R*sqrt(ipol*ipol+psipR*psipR +psipZ*psipZ);
    }
  private:
    TokamakMagneticField mag_;
};

/**
 * @brief \f$  |B|^{-1} = R/R_0\sqrt{I^2+(\nabla\psi)^2}    \f$

    \f$   \frac{1}{\hat{B}} =
        \frac{\hat{R}}{\hat{R}_0}\frac{1}{ \sqrt{ \hat{I}^2  + \left(\frac{\partial \hat{\psi}_p }{ \partial \hat{R}}\right)^2
        + \left(\frac{\partial \hat{\psi}_p }{ \partial \hat{Z}}\right)^2}}  \f$
 */
struct InvB : public aCylindricalFunctor<InvB>
{
    InvB(  const TokamakMagneticField& mag): mag_(mag){ }
    double do_compute(double R, double Z) const
    {
        double psipR = mag_.psipR()(R,Z), psipZ = mag_.psipZ()(R,Z), ipol = mag_.ipol()(R,Z);
        return R/(mag_.R0()*sqrt(ipol*ipol + psipR*psipR +psipZ*psipZ)) ;
    }
  private:
    TokamakMagneticField mag_;
};

/**
 * @brief \f$   \ln{|B|}  \f$
 *
   \f$   \ln{(   \hat{B})} = \ln{\left[
          \frac{\hat{R}_0}{\hat{R}} \sqrt{ \hat{I}^2  + \left(\frac{\partial \hat{\psi}_p }{ \partial \hat{R}}\right)^2
          + \left(\frac{\partial \hat{\psi}_p }{ \partial \hat{Z}}\right)^2} \right] } \f$
 */
struct LnB : public aCylindricalFunctor<LnB>
{
    LnB(const TokamakMagneticField& mag): mag_(mag) { }
    double do_compute(double R, double Z) const
    {
        double psipR = mag_.psipR()(R,Z), psipZ = mag_.psipZ()(R,Z), ipol = mag_.ipol()(R,Z);
        return log(mag_.R0()/R*sqrt(ipol*ipol + psipR*psipR +psipZ*psipZ)) ;
    }
  private:
    TokamakMagneticField mag_;
};

/**
 * @brief \f$  \frac{\partial |B| }{ \partial R}  \f$
 *
 \f$  \frac{\partial \hat{B} }{ \partial \hat{R}} =
      -\frac{1}{\hat B \hat R}
      +  \frac{\hat I \left(\frac{\partial\hat I}{\partial\hat R} \right)
      + \left(\frac{\partial \hat{\psi}_p }{ \partial \hat{Z}} \right)\left(\frac{\partial^2  \hat{\psi}_p }{ \partial \hat{R} \partial\hat{Z}}\right)
      + \left( \frac{\partial \hat{\psi}_p }{ \partial \hat{R}}\right)\left( \frac{\partial^2  \hat{\psi}_p }{ \partial \hat{R}^2}\right)}
      {\hat{R}^2 \hat{R}_0^{-2}\hat{B}} \f$
 */
struct BR: public aCylindricalFunctor<BR>
{
    BR(const TokamakMagneticField& mag): invB_(mag), mag_(mag) { }
    double do_compute(double R, double Z) const
    {
        double Rn;
        Rn = R/mag_.R0();
        return -1./R/invB_(R,Z) + invB_(R,Z)/Rn/Rn*(mag_.ipol()(R,Z)*mag_.ipolR()(R,Z) + mag_.psipR()(R,Z)*mag_.psipRR()(R,Z) + mag_.psipZ()(R,Z)*mag_.psipRZ()(R,Z));
    }
  private:
    InvB invB_;
    TokamakMagneticField mag_;
};

/**
 * @brief \f$  \frac{\partial |B| }{ \partial Z}  \f$
 *
  \f$  \frac{\partial \hat{B} }{ \partial \hat{Z}} =
     \frac{ \hat I \left(\frac{\partial \hat I}{\partial\hat Z}    \right)+
     \left(\frac{\partial \hat{\psi}_p }{ \partial \hat{R}} \right)\left(\frac{\partial^2  \hat{\psi}_p }{ \partial \hat{R} \partial\hat{Z}}\right)
          + \left( \frac{\partial \hat{\psi}_p }{ \partial \hat{Z}} \right)\left(\frac{\partial^2  \hat{\psi}_p }{ \partial \hat{Z}^2} \right)}{\hat{R}^2 \hat{R}_0^{-2}\hat{B}} \f$
 */
struct BZ: public aCylindricalFunctor<BZ>
{
    BZ(const TokamakMagneticField& mag ): mag_(mag), invB_(mag) { }
    double do_compute(double R, double Z) const
    {
        double Rn;
        Rn = R/mag_.R0();
        return (invB_(R,Z)/Rn/Rn)*(mag_.ipol()(R,Z)*mag_.ipolZ()(R,Z) + mag_.psipR()(R,Z)*mag_.psipRZ()(R,Z) + mag_.psipZ()(R,Z)*mag_.psipZZ()(R,Z));
    }
  private:
    TokamakMagneticField mag_;
    InvB invB_;
};

///@brief Approximate \f$ \mathcal{K}^{R}_{\nabla B} \f$
///
/// \f$ \mathcal{\hat{K}}^{\hat{R}}_{\nabla B} =-\frac{1}{ \hat{B}^2}  \frac{\partial \hat{B}}{\partial \hat{Z}}  \f$
///@copydoc hide_toroidal_approximation_note
struct CurvatureNablaBR: public aCylindricalFunctor<CurvatureNablaBR>
{
    CurvatureNablaBR(const TokamakMagneticField& mag, int sign): invB_(mag), bZ_(mag) {
        if( sign >0)
            m_sign = +1.;
        else
            m_sign = -1;
    }
    double do_compute( double R, double Z) const
    {
        return -m_sign*invB_(R,Z)*invB_(R,Z)*bZ_(R,Z);
    }
    private:
    double m_sign;
    InvB invB_;
    BZ bZ_;
};

///@brief Approximate \f$  \mathcal{K}^{Z}_{\nabla B}  \f$
///
/// \f$  \mathcal{\hat{K}}^{\hat{Z}}_{\nabla B} =\frac{1}{ \hat{B}^2}   \frac{\partial \hat{B}}{\partial \hat{R}} \f$
///@copydoc hide_toroidal_approximation_note
struct CurvatureNablaBZ: public aCylindricalFunctor<CurvatureNablaBZ>
{
    CurvatureNablaBZ( const TokamakMagneticField& mag, int sign): invB_(mag), bR_(mag) {
        if( sign >0)
            m_sign = +1.;
        else
            m_sign = -1;
    }
    double do_compute( double R, double Z) const
    {
        return m_sign*invB_(R,Z)*invB_(R,Z)*bR_(R,Z);
    }
    private:
    double m_sign;
    InvB invB_;
    BR bR_;
};

///@brief Approximate \f$ \mathcal{K}^{R}_{\vec{\kappa}}=0 \f$
///
/// \f$ \mathcal{\hat{K}}^{\hat{R}}_{\vec{\kappa}} =0  \f$
///@copydoc hide_toroidal_approximation_note
struct CurvatureKappaR: public aCylindricalFunctor<CurvatureKappaR>
{
    CurvatureKappaR( ){ }
    CurvatureKappaR( const TokamakMagneticField& mag, int sign = +1){ }
    double do_compute( double R, double Z) const
    {
        return  0.;
    }
    private:
};

///@brief Approximate \f$  \mathcal{K}^{Z}_{\vec{\kappa}}  \f$
///
/// \f$  \mathcal{\hat{K}}^{\hat{Z}}_{\vec{\kappa}} = - \frac{1}{\hat{R} \hat{B}} \f$
///@copydoc hide_toroidal_approximation_note
struct CurvatureKappaZ: public aCylindricalFunctor<CurvatureKappaZ>
{
    CurvatureKappaZ( const TokamakMagneticField& mag, int sign): invB_(mag) {
        if( sign >0)
            m_sign = +1.;
        else
            m_sign = -1;
    }
    double do_compute( double R, double Z) const
    {
        return -m_sign*invB_(R,Z)/R;
    }
    private:
    double m_sign;
    InvB invB_;
};

///@brief Approximate \f$  \vec{\nabla}\cdot \mathcal{K}_{\vec{\kappa}}  \f$
///
///  \f$  \vec{\hat{\nabla}}\cdot \mathcal{\hat{K}}_{\vec{\kappa}}  = \frac{1}{\hat{R}  \hat{B}^2 } \partial_{\hat{Z}} \hat{B}\f$
///@copydoc hide_toroidal_approximation_note
struct DivCurvatureKappa: public aCylindricalFunctor<DivCurvatureKappa>
{
    DivCurvatureKappa( const TokamakMagneticField& mag, int sign): invB_(mag), bZ_(mag){
        if( sign >0)
            m_sign = +1.;
        else
            m_sign = -1;
    }
    double do_compute( double R, double Z) const
    {
        return m_sign*bZ_(R,Z)*invB_(R,Z)*invB_(R,Z)/R;
    }
    private:
    double m_sign;
    InvB invB_;
    BZ bZ_;
};

///@brief Approximate \f$  \vec{\nabla}\cdot \mathcal{K}_{\nabla B}  \f$
///
///  \f$  \vec{\hat{\nabla}}\cdot \mathcal{\hat{K}}_{\nabla B}  = -\frac{1}{\hat{R}  \hat{B}^2 } \partial_{\hat{Z}} \hat{B}\f$
///@copydoc hide_toroidal_approximation_note
struct DivCurvatureNablaB: public aCylindricalFunctor<DivCurvatureNablaB>
{
    DivCurvatureNablaB( const TokamakMagneticField& mag, int sign): div_(mag, sign){ }
    double do_compute( double R, double Z) const
    {
        return -div_(R,Z);
    }
    private:
    DivCurvatureKappa div_;
};
///@brief True \f$ \mathcal{K}^{R}_{\nabla B} \f$
///
/// \f$ \mathcal{K}^R_{\nabla B} =-\frac{R_0I}{ B^3R}  \frac{\partial B}{\partial Z}  \f$
struct TrueCurvatureNablaBR: public aCylindricalFunctor<TrueCurvatureNablaBR>
{
    TrueCurvatureNablaBR(const TokamakMagneticField& mag): R0_(mag.R0()), c_(mag), invB_(mag), bZ_(mag) { }
    double do_compute( double R, double Z) const
    {
        double invB = invB_(R,Z), ipol = c_.ipol()(R,Z);
        return -invB*invB*invB*ipol*R0_/R*bZ_(R,Z);
    }
    private:
    double R0_;
    TokamakMagneticField c_;
    InvB invB_;
    BZ bZ_;
};

///@brief True \f$ \mathcal{K}^{Z}_{\nabla B} \f$
///
/// \f$ \mathcal{K}^Z_{\nabla B} =\frac{R_0I}{ B^3R}  \frac{\partial B}{\partial R}  \f$
struct TrueCurvatureNablaBZ: public aCylindricalFunctor<TrueCurvatureNablaBZ>
{
    TrueCurvatureNablaBZ(const TokamakMagneticField& mag): R0_(mag.R0()), c_(mag), invB_(mag), bR_(mag) { }
    double do_compute( double R, double Z) const
    {
        double invB = invB_(R,Z), ipol = c_.ipol()(R,Z);
        return invB*invB*invB*ipol*R0_/R*bR_(R,Z);
    }
    private:
    double R0_;
    TokamakMagneticField c_;
    InvB invB_;
    BR bR_;
};

///@brief True \f$ \mathcal{K}^{\varphi}_{\nabla B} \f$
///
/// \f$ \mathcal{K}^\varphi_{\nabla B} =\frac{1}{ B^3R^2}\left( \frac{\partial\psi}{\partial Z} \frac{\partial B}{\partial Z} + \frac{\partial \psi}{\partial R}\frac{\partial B}{\partial R} \right) \f$
struct TrueCurvatureNablaBP: public aCylindricalFunctor<TrueCurvatureNablaBP>
{
    TrueCurvatureNablaBP(const TokamakMagneticField& mag): c_(mag), invB_(mag),bR_(mag), bZ_(mag) { }
    double do_compute( double R, double Z) const
    {
        double invB = invB_(R,Z);
        return c_.R0()*invB*invB*invB/R/R*(c_.psipZ()(R,Z)*bZ_(R,Z) + c_.psipR()(R,Z)*bR_(R,Z));
    }
    private:
    TokamakMagneticField c_;
    InvB invB_;
    BR bR_;
    BZ bZ_;
};

///@brief True \f$ \mathcal{K}^R_{\vec{\kappa}} \f$
struct TrueCurvatureKappaR: public aCylindricalFunctor<TrueCurvatureKappaR>
{
    TrueCurvatureKappaR( const TokamakMagneticField& mag):c_(mag), invB_(mag), bZ_(mag){ }
    double do_compute( double R, double Z) const
    {
        double invB = invB_(R,Z);
        return c_.R0()*invB*invB/R*(c_.ipolZ()(R,Z) - c_.ipol()(R,Z)*invB*bZ_(R,Z));
    }
    private:
    TokamakMagneticField c_;
    InvB invB_;
    BZ bZ_;
};

///@brief True \f$ \mathcal{K}^Z_{\vec{\kappa}} \f$
struct TrueCurvatureKappaZ: public aCylindricalFunctor<TrueCurvatureKappaZ>
{
    TrueCurvatureKappaZ( const TokamakMagneticField& mag):c_(mag), invB_(mag), bR_(mag){ }
    double do_compute( double R, double Z) const
    {
        double invB = invB_(R,Z);
        return c_.R0()*invB*invB/R*( - c_.ipolR()(R,Z) + c_.ipol()(R,Z)*invB*bR_(R,Z));
    }
    private:
    TokamakMagneticField c_;
    InvB invB_;
    BR bR_;
};
///@brief True \f$ \mathcal{K}^\varphi_{\vec{\kappa}} \f$
struct TrueCurvatureKappaP: public aCylindricalFunctor<TrueCurvatureKappaP>
{
    TrueCurvatureKappaP( const TokamakMagneticField& mag):c_(mag), invB_(mag), bR_(mag), bZ_(mag){ }
    double do_compute( double R, double Z) const
    {
        double invB = invB_(R,Z);
        return c_.R0()*invB*invB/R/R*(
            + invB*c_.psipZ()(R,Z)*bZ_(R,Z) + invB *c_.psipR()(R,Z)*bR_(R,Z)
            + c_.psipR()(R,Z)/R - c_.psipRR()(R,Z) - c_.psipZZ()(R,Z));
    }
    private:
    TokamakMagneticField c_;
    InvB invB_;
    BR bR_;
    BZ bZ_;
};

///@brief True \f$  \vec{\nabla}\cdot \mathcal{K}_{\vec{\kappa}}  \f$
struct TrueDivCurvatureKappa: public aCylindricalFunctor<TrueDivCurvatureKappa>
{
    TrueDivCurvatureKappa( const TokamakMagneticField& mag): c_(mag), invB_(mag), bR_(mag), bZ_(mag){}
    double do_compute( double R, double Z) const
    {
        double invB = invB_(R,Z);
        return c_.R0()*invB*invB*invB/R*( c_.ipolR()(R,Z)*bZ_(R,Z) - c_.ipolZ()(R,Z)*bR_(R,Z) );
    }
    private:
    TokamakMagneticField c_;
    InvB invB_;
    BR bR_;
    BZ bZ_;
};

///@brief True \f$  \vec{\nabla}\cdot \mathcal{K}_{\nabla B}  \f$
struct TrueDivCurvatureNablaB: public aCylindricalFunctor<TrueDivCurvatureNablaB>
{
    TrueDivCurvatureNablaB( const TokamakMagneticField& mag): div_(mag){}
    double do_compute( double R, double Z) const {
        return - div_(R,Z);
    }
    private:
    TrueDivCurvatureKappa div_;
};

/**
 * @brief \f$  \nabla_\parallel \ln{(B)} \f$
 *
 *    \f$  \hat{\nabla}_\parallel \ln{(\hat{B})} = \frac{1}{\hat{R}\hat{B}^2 } \left[ \hat{B}, \hat{\psi}_p\right]_{\hat{R}\hat{Z}} \f$
 */
struct GradLnB: public aCylindricalFunctor<GradLnB>
{
    GradLnB( const TokamakMagneticField& mag): mag_(mag), invB_(mag), bR_(mag), bZ_(mag) { }
    double do_compute( double R, double Z) const
    {
        double invB = invB_(R,Z);
        return mag_.R0()*invB*invB*(bR_(R,Z)*mag_.psipZ()(R,Z)-bZ_(R,Z)*mag_.psipR()(R,Z))/R ;
    }
    private:
    TokamakMagneticField mag_;
    InvB invB_;
    BR bR_;
    BZ bZ_;
};
/**
 * @brief \f$  \nabla \cdot \vec b \f$
 *
 * \f$  \nabla\cdot \vec b = -\nabla_\parallel \ln B \f$
 * @sa \c GradLnB
 */
struct Divb: public aCylindricalFunctor<Divb>
{
    Divb( const TokamakMagneticField& mag): m_gradLnB(mag) { }
    double do_compute( double R, double Z) const
    {
        return -m_gradLnB(R,Z);
    }
    private:
    GradLnB m_gradLnB;
};

///@brief \f$ B^\varphi = R_0I/R^2\f$
struct BFieldP: public aCylindricalFunctor<BFieldP>
{
    BFieldP( const TokamakMagneticField& mag): mag_(mag){}
    double do_compute( double R, double Z) const
    {
        return mag_.R0()*mag_.ipol()(R,Z)/R/R;
    }
    private:

    TokamakMagneticField mag_;
};

///@brief \f$ B^R = R_0\psi_Z /R\f$
struct BFieldR: public aCylindricalFunctor<BFieldR>
{
    BFieldR( const TokamakMagneticField& mag): mag_(mag){}
    double do_compute( double R, double Z) const
    {
        return  mag_.R0()/R*mag_.psipZ()(R,Z);
    }
    private:
    TokamakMagneticField mag_;

};

///@brief \f$ B^Z = -R_0\psi_R /R\f$
struct BFieldZ: public aCylindricalFunctor<BFieldZ>
{
    BFieldZ( const TokamakMagneticField& mag): mag_(mag){}
    double do_compute( double R, double Z) const
    {
        return -mag_.R0()/R*mag_.psipR()(R,Z);
    }
    private:
    TokamakMagneticField mag_;
};

///@brief \f$  B^{\theta} = B^R\partial_R\theta + B^Z\partial_Z\theta\f$
struct BFieldT: public aCylindricalFunctor<BFieldT>
{
    BFieldT( const TokamakMagneticField& mag):  R_0_(mag.R0()), fieldR_(mag), fieldZ_(mag){}
    double do_compute(double R, double Z) const
    {
        double r2 = (R-R_0_)*(R-R_0_) + Z*Z;
        return fieldR_(R,Z)*(-Z/r2) + fieldZ_(R,Z)*(R-R_0_)/r2;
    }
    private:
    double R_0_;
    BFieldR fieldR_;
    BFieldZ fieldZ_;
};

///@brief \f$ b^R = B^R/|B|\f$
struct BHatR: public aCylindricalFunctor<BHatR>
{
    BHatR( const TokamakMagneticField& mag): mag_(mag), invB_(mag){ }
    double do_compute( double R, double Z) const
    {
        return  invB_(R,Z)*mag_.R0()/R*mag_.psipZ()(R,Z);
    }
    private:
    TokamakMagneticField mag_;
    InvB invB_;

};

///@brief \f$ b^Z = B^Z/|B|\f$
struct BHatZ: public aCylindricalFunctor<BHatZ>
{
    BHatZ( const TokamakMagneticField& mag): mag_(mag), invB_(mag){ }
    double do_compute( double R, double Z) const
    {
        return  -invB_(R,Z)*mag_.R0()/R*mag_.psipR()(R,Z);
    }
    private:
    TokamakMagneticField mag_;
    InvB invB_;
};

///@brief \f$ b^\varphi = B^\varphi/|B|\f$
struct BHatP: public aCylindricalFunctor<BHatP>
{
    BHatP( const TokamakMagneticField& mag): mag_(mag), invB_(mag){ }
    double do_compute( double R, double Z) const
    {
        return invB_(R,Z)*mag_.R0()*mag_.ipol()(R,Z)/R/R;
    }
    private:
    TokamakMagneticField mag_;
    InvB invB_;
};

/**
 * @brief Contravariant components of the magnetic unit vector field
 * in cylindrical coordinates.
 * @param mag the tokamak magnetic field
 * @return the tuple BHatR, BHatZ, BHatP constructed from mag
 */
inline CylindricalVectorLvl0 createBHat( const TokamakMagneticField& mag){
    return CylindricalVectorLvl0( BHatR(mag), BHatZ(mag), BHatP(mag));
}

/**
 * @brief Contravariant components of the unit vector field (0, 0, +/- 1/R)
 * in cylindrical coordinates.
 * @param sign indicate positive or negative unit vector
 * @return the tuple dg::geo::Constant(0), dg::geo::Constant(0), \f$ 1/R \f$
 * @note This is equivalent to inserting a toroidal magnetic field into the \c dg::geo::createBHat function.
 */
inline CylindricalVectorLvl0 createEPhi( int sign ){
    if( sign > 0)
        return CylindricalVectorLvl0( Constant(0), Constant(0), [](double x, double y){ return 1./x;});
    return CylindricalVectorLvl0( Constant(0), Constant(0), [](double x, double y){ return -1./x;});
}
/**
 * @brief Approximate curvature vector field (CurvatureNablaBR, CurvatureNablaBZ, Constant(0))
 *
 * @param mag the tokamak magnetic field
 * @param sign indicate positive or negative unit vector in approximation
 * @return the tuple \c CurvatureNablaBR, \c CurvatureNablaBZ, \c dg::geo::Constant(0) constructed from \c mag
 * @note The contravariant components in cylindrical coordinates
 */
inline CylindricalVectorLvl0 createCurvatureNablaB( const TokamakMagneticField& mag, int sign){
    return CylindricalVectorLvl0( CurvatureNablaBR(mag, sign), CurvatureNablaBZ(mag, sign), Constant(0));
}
/**
 * @brief Approximate curvature vector field (CurvatureKappaR, CurvatureKappaZ, Constant(0))
 *
 * @param mag the tokamak magnetic field
 * @param sign indicate positive or negative unit vector in approximation
 * @return the tuple \c CurvatureKappaR, \c CurvatureKappaZ, \c dg::geo::Constant(0) constructed from \c mag
 * @note The contravariant components in cylindrical coordinates
 */
inline CylindricalVectorLvl0 createCurvatureKappa( const TokamakMagneticField& mag, int sign){
    return CylindricalVectorLvl0( CurvatureKappaR(mag, sign), CurvatureKappaZ(mag, sign), Constant(0));
}
/**
 * @brief True curvature vector field (TrueCurvatureKappaR, TrueCurvatureKappaZ, TrueCurvatureKappaP)
 *
 * @param mag the tokamak magnetic field
 * @return the tuple TrueCurvatureKappaR, TrueCurvatureKappaZ, TrueCurvatureKappaP constructed from mag
 * @note The contravariant components in cylindrical coordinates
 */
inline CylindricalVectorLvl0 createTrueCurvatureKappa( const TokamakMagneticField& mag){
    return CylindricalVectorLvl0( TrueCurvatureKappaR(mag), TrueCurvatureKappaZ(mag), TrueCurvatureKappaP(mag));
}
/**
 * @brief True curvature vector field (TrueCurvatureNablaBR, TrueCurvatureNablaBZ, TrueCurvatureNablaBP)
 *
 * @param mag the tokamak magnetic field
 * @return the tuple TrueCurvatureNablaBR, TrueCurvatureNablaBZ, TrueCurvatureNablaBP constructed from mag
 * @note The contravariant components in cylindrical coordinates
 */
inline CylindricalVectorLvl0 createTrueCurvatureNablaB( const TokamakMagneticField& mag){
    return CylindricalVectorLvl0( TrueCurvatureNablaBR(mag), TrueCurvatureNablaBZ(mag), TrueCurvatureNablaBP(mag));
}
/**
 * @brief Gradient Psip vector field (PsipR, PsipZ, 0)
 *
 * @param mag the tokamak magnetic field
 * @return the tuple PsipR, PsipZ, 0 constructed from mag
 * @note The contravariant components in cylindrical coordinates
 */
inline CylindricalVectorLvl0 createGradPsip( const TokamakMagneticField& mag){
    return CylindricalVectorLvl0( mag.psipR(), mag.psipZ(),Constant(0));
}

//Necessary to analytically compute Laplacians:
///@brief \f$ \nabla_\parallel b^R \f$
struct GradBHatR: public aCylindricalFunctor<GradBHatR>
{
    GradBHatR( const TokamakMagneticField& mag): bhatR_(mag), divb_(mag), mag_(mag){}
    double do_compute( double R, double Z) const
    {
        double ipol = mag_.ipol()(R,Z);
        double psipR = mag_.psipR()(R,Z), psipZ = mag_.psipZ()(R,Z);
        double psipZZ = mag_.psipZZ()(R,Z), psipRZ = mag_.psipRZ()(R,Z);
        return  divb_(R,Z)*bhatR_(R,Z) +
                ( psipZ*(psipRZ-psipZ/R) - psipZZ*psipR  )/
                    (ipol*ipol + psipR*psipR + psipZ*psipZ);
    }
    private:
    BHatR bhatR_;
    Divb divb_;
    TokamakMagneticField mag_;
};
///@brief \f$ \nabla_\parallel b^Z \f$
struct GradBHatZ: public aCylindricalFunctor<GradBHatZ>
{
    GradBHatZ( const TokamakMagneticField& mag): bhatZ_(mag), divb_(mag), mag_(mag){}
    double do_compute( double R, double Z) const
    {
        double ipol = mag_.ipol()(R,Z);
        double psipR = mag_.psipR()(R,Z), psipZ = mag_.psipZ()(R,Z);
        double psipRR = mag_.psipRR()(R,Z), psipRZ = mag_.psipRZ()(R,Z);

        return  divb_(R,Z)*bhatZ_(R,Z) +
                (psipR*(psipRZ+psipZ/R) - psipRR*psipZ)/
                    (ipol*ipol + psipR*psipR + psipZ*psipZ);
    }
    private:
    BHatZ bhatZ_;
    Divb divb_;
    TokamakMagneticField mag_;
};
///@brief \f$ \nabla_\parallel b^\varphi \f$
struct GradBHatP: public aCylindricalFunctor<GradBHatP>
{
    GradBHatP( const TokamakMagneticField& mag): bhatP_(mag), divb_(mag), mag_(mag){}
    double do_compute( double R, double Z) const
    {
        double ipol = mag_.ipol()(R,Z), ipolR = mag_.ipolR()(R,Z), ipolZ  = mag_.ipolZ()(R,Z);
        double psipR = mag_.psipR()(R,Z), psipZ = mag_.psipZ()(R,Z);

        return  divb_(R,Z)*bhatP_(R,Z) +
             (psipZ*(ipolR/R - 2.*ipol/R/R) - ipolZ/R*psipR)/
                    (ipol*ipol + psipR*psipR + psipZ*psipZ);
    }
    private:
    BHatP bhatP_;
    Divb divb_;
    TokamakMagneticField mag_;
};

///@brief \f$ \sqrt{\psi_p/ \psi_{p,\min}} \f$
struct RhoP: public aCylindricalFunctor<RhoP>
{
    RhoP( const TokamakMagneticField& mag): m_mag(mag){
        double RO = m_mag.R0(), ZO = 0;
        findOpoint( mag.get_psip(), RO, ZO);
        m_psipmin = m_mag.psip()(RO, ZO);
    }
    double do_compute( double R, double Z) const
    {
        return sqrt( 1.-m_mag.psip()(R,Z)/m_psipmin ) ;
    }
    private:
    double m_psipmin;
    TokamakMagneticField m_mag;

};

///@brief Inertia factor \f$ \mathcal I_0 \f$
struct Hoo : public dg::geo::aCylindricalFunctor<Hoo>
{
    Hoo( dg::geo::TokamakMagneticField mag): mag_(mag){}
    double do_compute( double R, double Z) const
    {
        double psipR = mag_.psipR()(R,Z), psipZ = mag_.psipZ()(R,Z), ipol = mag_.ipol()(R,Z);
        double psip2 = psipR*psipR+psipZ*psipZ;
        if( psip2 == 0)
            psip2 = 1e-16;
        return (ipol*ipol + psip2)/R/R/psip2;
    }
    private:
    dg::geo::TokamakMagneticField mag_;
};
///@}

} //namespace geo
} //namespace dg

