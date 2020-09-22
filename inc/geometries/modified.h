#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "dg/blas.h"

#include "dg/topology/functions.h"
#include "dg/functors.h"
#include "magnetic_field.h"


/*!@file
 *
 * Modified MagneticField objects
 */
namespace dg
{
namespace geo
{
namespace mod
{
    //modify with a polynomial Heaviside function

struct Psip: public aCylindricalFunctor<Psip>
{
    Psip( std::function<bool(double,double)> predicate, std::function<double(double,double)> psip, double psi0, double alpha, double sign = -1) :
        m_ipoly( psi0, alpha, sign), m_psip(psip), m_pred(predicate)
    { }
    double do_compute(double R, double Z) const
    {
        double psip = m_psip(R,Z);
        if( m_pred( R,Z))
            return m_ipoly( psip);
        else
            return psip;
    }
    private:
    dg::IPolynomialHeaviside m_ipoly;
    std::function<double(double,double)> m_psip;
    std::function<bool(double,double)> m_pred;
};
struct PsipR: public aCylindricalFunctor<PsipR>
{
    PsipR( std::function<bool(double,double)> predicate, std::function<double(double,double)> psip, std::function<double(double,double)> psipR, double psi0, double alpha, double sign = -1) :
        m_poly( psi0, alpha, sign), m_psip(psip), m_psipR(psipR), m_pred(predicate)
    { }
    double do_compute(double R, double Z) const
    {
        double psip  = m_psip(R,Z);
        double psipR = m_psipR(R,Z);
        if( m_pred( R,Z))
            return psipR*m_poly( psip);
        else
            return psipR;
    }
    private:
    dg::PolynomialHeaviside m_poly;
    std::function<double(double,double)> m_psip, m_psipR;
    std::function<bool(double,double)> m_pred;
};
struct PsipZ: public aCylindricalFunctor<PsipZ>
{
    PsipZ( std::function<bool(double,double)> predicate, std::function<double(double,double)> psip, std::function<double(double,double)> psipZ, double psi0, double alpha, double sign = -1) :
        m_poly( psi0, alpha, sign), m_psip(psip), m_psipZ(psipZ), m_pred(predicate)
    { }
    double do_compute(double R, double Z) const
    {
        double psip = m_psip(R,Z);
        double psipZ = m_psipZ(R,Z);
        if( m_pred( R,Z))
            return psipZ*m_poly( psip);
        else
            return psipZ;
    }
    private:
    dg::PolynomialHeaviside m_poly;
    std::function<double(double,double)> m_psip, m_psipZ;
    std::function<bool(double,double)> m_pred;
};

struct PsipZZ: public aCylindricalFunctor<PsipZZ>
{
    PsipZZ( std::function<bool(double,double)> predicate, std::function<double(double,double)> psip, std::function<double(double,double)> psipZ, std::function<double(double,double)> psipZZ, double psi0, double alpha, double sign = -1) :
        m_poly( psi0, alpha, sign), m_dpoly( psi0, alpha, sign), m_psip(psip), m_psipZ(psipZ), m_psipZZ(psipZZ), m_pred(predicate)
    { }
    double do_compute(double R, double Z) const
    {
        double psip = m_psip(R,Z);
        double psipZ = m_psipZ(R,Z);
        double psipZZ = m_psipZZ(R,Z);
        if( m_pred( R,Z))
            return psipZZ*m_poly( psip) + psipZ*psipZ*m_dpoly(psip);
        else
            return psipZZ;
    }
    private:
    dg::PolynomialHeaviside m_poly;
    dg::DPolynomialHeaviside m_dpoly;
    std::function<double(double,double)> m_psip, m_psipZ, m_psipZZ;
    std::function<bool(double,double)> m_pred;
};

struct PsipRR: public aCylindricalFunctor<PsipRR>
{
    PsipRR( std::function<bool(double,double)> predicate, std::function<double(double,double)> psip, std::function<double(double,double)> psipR, std::function<double(double,double)> psipRR, double psi0, double alpha, double sign = -1) :
        m_poly( psi0, alpha, sign), m_dpoly( psi0, alpha, sign), m_psip(psip), m_psipR(psipR), m_psipRR(psipRR), m_pred(predicate)
    { }
    double do_compute(double R, double Z) const
    {
        double psip = m_psip(R,Z);
        double psipR = m_psipR(R,Z);
        double psipRR = m_psipRR(R,Z);
        if( m_pred( R,Z))
            return psipRR*m_poly( psip) + psipR*psipR*m_dpoly(psip);
        else
            return psipRR;
    }
    private:
    dg::PolynomialHeaviside m_poly;
    dg::DPolynomialHeaviside m_dpoly;
    std::function<double(double,double)> m_psip, m_psipR, m_psipRR;
    std::function<bool(double,double)> m_pred;
};
struct PsipRZ: public aCylindricalFunctor<PsipRZ>
{
    PsipRZ( std::function<bool(double,double)> predicate, std::function<double(double,double)> psip, std::function<double(double,double)> psipR, std::function<double(double,double)> psipZ, std::function<double(double,double)> psipRZ, double psi0, double alpha, double sign = -1) :
        m_poly( psi0, alpha, sign), m_dpoly( psi0, alpha, sign), m_psip(psip), m_psipR(psipR), m_psipZ(psipZ), m_psipRZ(psipRZ), m_pred(predicate)
    { }
    double do_compute(double R, double Z) const
    {
        double psip = m_psip(R,Z);
        double psipR = m_psipR(R,Z);
        double psipZ = m_psipZ(R,Z);
        double psipRZ = m_psipRZ(R,Z);
        if( m_pred( R,Z))
            return psipRZ*m_poly( psip) + psipR*psipZ*m_dpoly(psip);
        else
            return psipRZ;
    }
    private:
    dg::PolynomialHeaviside m_poly;
    dg::DPolynomialHeaviside m_dpoly;
    std::function<double(double,double)> m_psip, m_psipR, m_psipZ, m_psipRZ;
    std::function<bool(double,double)> m_pred;
};

static inline dg::geo::CylindricalFunctorsLvl2 createPsip(
        const std::function<bool(double,double)> predicate,
        const CylindricalFunctorsLvl2& psip,
    double psi0, double alpha, double sign = -1)
{
    return CylindricalFunctorsLvl2(
            mod::Psip(predicate,psip.f(), psi0, alpha, sign),
            mod::PsipR(predicate,psip.f(), psip.dfx(), psi0, alpha, sign),
            mod::PsipZ(predicate,psip.f(), psip.dfy(), psi0, alpha, sign),
            mod::PsipRR(predicate,psip.f(), psip.dfx(), psip.dfxx(), psi0, alpha, sign),
            mod::PsipRZ(predicate,psip.f(), psip.dfx(), psip.dfy(), psip.dfxy(), psi0, alpha, sign),
            mod::PsipZZ(predicate,psip.f(), psip.dfy(), psip.dfyy(), psi0, alpha, sign));
}

//some possible predicates

static bool everywhere( double R, double Z){return true;}
struct HeavisideZ{
    HeavisideZ( double Z_X, int side): m_ZX( Z_X), m_side(side) {}
    bool operator()(double R, double Z){
        if( Z < m_ZX && m_side <= 0) return true;
        if( Z >= m_ZX && m_side > 0) return true;
        return false;
    }
    private:
    double m_ZX;
    int m_side;
};

} //namespace mod

} //namespace geo
} //namespace dg
