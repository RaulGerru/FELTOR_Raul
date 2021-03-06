//Mathematica generated file. Do not manually edit!
//Manufactures a solution for the feltor equations for circular flux-surfaces with R0=10, I0=20, a=1 and all Dirichlet boundary conditions
//Defines the functors: 
//    Ne, Ni, Ue, Ui, Phie, Phii, GammaPhie, GammaNi, A
//as well as
//    SNe, SNi, SUe, SUi, SPhie, SPhii, SGammaPhie, SGammaNi, SA
//Requires a definition for DG_DEVICE (define empty for host code and __host__ __device__ to generate CUDA code!)
//Requires a definition for FELTORPERP and FELTORPARALLEL (define 1/0 to activate/deactive respective terms in equations)
#include <cmath>
namespace feltor{ namespace manufactured{ 
DG_DEVICE double Power(double x, double y){ return pow(x,y);}
DG_DEVICE double Sqrt(double x){ return sqrt(x);}
DG_DEVICE double Sin(double x){ return sin(x);}
DG_DEVICE double Cos(double x){ return cos(x);}
static const double Pi = M_PI;
struct Ne{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return 1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)
; }};
struct Ni{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return 1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)
; }};
struct Ue{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/(3.*Sqrt(-mue))
; }};
struct Ui{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/3.
; }};
struct Phie{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (Sin(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.
; }};
struct Phii{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (Sin(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.
; }};
struct GammaPhie{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (Sin(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.
; }};
struct GammaNi{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return 1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)
; }};
struct A{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (beta*Sin(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*t)*Sin(4*Pi*Z))/4.
; }};
struct SNe{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return 1.5707963267948966*Cos(Pi*t)*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*Z) + 
  FELTORPARALLEL*(-((nuparallel*
          (0. + (1.*Z*((-1.5707963267948966*(-10 + R)*Cos(Pi*Z)*Sin(P)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (1.5707963267948966*Z*Cos(Pi*(-10 + R))*Sin(P)*
                    Sin(Pi*t)*Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (10.*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                  (R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
             Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
            (1.*(-10 + R)*R*((4.934802200544679*Z*Cos(Pi*(-10 + R))*
                    Cos(Pi*Z)*Sin(P)*Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (31.41592653589793*Cos(P)*Cos(Pi*Z)*Sin(Pi*(-10 + R))*
                    Sin(Pi*t))/
                  (R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
                 (1.5707963267948966*(-10 + R)*Z*Cos(Pi*Z)*Sin(P)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t))/
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
                 (1.5707963267948966*Power(Z,2)*Cos(Pi*(-10 + R))*
                    Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) + 
                 (1.5707963267948966*Cos(Pi*(-10 + R))*Sin(P)*
                    Sin(Pi*t)*Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
                 (10.*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                  (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),
                     1.5)) + (4.934802200544679*(-10 + R)*Sin(P)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/
             Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
            (20*((-1.5707963267948966*(-10 + R)*Cos(P)*Cos(Pi*Z)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (1.5707963267948966*Z*Cos(P)*Cos(Pi*(-10 + R))*
                    Sin(Pi*t)*Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
                 (10.*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                  (R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
             Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
            (1.*R*Z*((-4.934802200544679*(-10 + R)*Cos(Pi*(-10 + R))*
                    Cos(Pi*Z)*Sin(P)*Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (1.5707963267948966*Power(-10 + R,2)*Cos(Pi*Z)*Sin(P)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t))/
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
                 (1.5707963267948966*Cos(Pi*Z)*Sin(P)*Sin(Pi*(-10 + R))*
                    Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (31.41592653589793*Cos(P)*Cos(Pi*(-10 + R))*Sin(Pi*t)*
                    Sin(Pi*Z))/
                  (R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
                 (1.5707963267948966*(-10 + R)*Z*Cos(Pi*(-10 + R))*
                    Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
                 (10.*(-10 + R)*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                    Sin(Pi*Z))/
                  (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),
                     1.5)) - (10.*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                    Sin(Pi*Z))/
                  (Power(R,2)*
                    Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
                 (4.934802200544679*Z*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                    Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/
             Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/R) + 
     (0. - (2.0943951023931953*(-10 + R)*R*Cos(2*Pi*Z)*Sin(2*P)*
           Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
           (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)))/
         (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
        (0.5235987755982988*(-10 + R)*R*Cos(Pi*Z)*Sin(P)*Sin(2*P)*
           Sin(Pi*(-10 + R))*Sin(2*Pi*(-10 + R))*Sin(Pi*t)*Sin(2*Pi*t)*
           Sin(2*Pi*Z))/
         (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
        (0.5235987755982988*R*Z*Cos(Pi*(-10 + R))*Sin(P)*Sin(2*P)*
           Sin(2*Pi*(-10 + R))*Sin(Pi*t)*Sin(2*Pi*t)*Sin(Pi*Z)*Sin(2*Pi*Z)\
)/(Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
        (3.3333333333333335*Cos(P)*Sin(2*P)*Sin(Pi*(-10 + R))*
           Sin(2*Pi*(-10 + R))*Sin(Pi*t)*Sin(2*Pi*t)*Sin(Pi*Z)*Sin(2*Pi*Z)\
)/(Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
        (2.0943951023931953*R*Z*Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(2*Pi*t)*
           (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
           Sin(2*Pi*Z))/
         (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
        (40*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
           (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
           Sin(2*Pi*Z))/
         (3.*Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
        (0.3333333333333333*Z*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
           (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
           Sin(2*Pi*Z))/
         (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/R) + 
  FELTORPERP*(-((nuperp*((1.5707963267948966*(-10 + R)*Z*Cos(Pi*Z)*Sin(P)*
               Sin(Pi*(-10 + R))*Sin(Pi*t))/
             (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
            1.5707963267948966*
             (1 - (1.*Power(Z,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
             Cos(Pi*(-10 + R))*Sin(P)*Sin(Pi*t)*Sin(Pi*Z) - 
            (10.*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
             (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
            R*((4.934802200544679*(-10 + R)*Z*Cos(Pi*(-10 + R))*
                  Cos(Pi*Z)*Sin(P)*Sin(Pi*t))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
               (31.41592653589793*(-10 + R)*Cos(P)*Cos(Pi*Z)*
                  Sin(Pi*(-10 + R))*Sin(Pi*t))/
                (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
               (3.141592653589793*Power(-10 + R,2)*Z*Cos(Pi*Z)*Sin(P)*
                  Sin(Pi*(-10 + R))*Sin(Pi*t))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) - 
               (3.141592653589793*(-10 + R)*Power(Z,2)*Cos(Pi*(-10 + R))*
                  Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
               (1.5707963267948966*(-10 + R)*Cos(Pi*(-10 + R))*Sin(P)*
                  Sin(Pi*t)*Sin(Pi*Z))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
               (20.*(-10 + R)*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                  Sin(Pi*Z))/
                (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) - 
               4.934802200544679*
                (1 - (1.*Power(-10 + R,2))/
                   (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(P)*
                Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)) + 
            R*((31.41592653589793*(-10 + R)*Cos(P)*Cos(Pi*Z)*
                  Sin(Pi*(-10 + R))*Sin(Pi*t))/
                (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               (31.41592653589793*Z*Cos(P)*Cos(Pi*(-10 + R))*Sin(Pi*t)*
                  Sin(Pi*Z))/
                (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               0.5*(Power(R,-2) - 
                  400/
                   (Power(R,2)*
                     (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*Sin(P)*
                Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)) + 
            R*((4.934802200544679*(-10 + R)*Z*Cos(Pi*(-10 + R))*Cos(Pi*Z)*
                  Sin(P)*Sin(Pi*t))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
               (3.141592653589793*Power(-10 + R,2)*Z*Cos(Pi*Z)*Sin(P)*
                  Sin(Pi*(-10 + R))*Sin(Pi*t))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
               (1.5707963267948966*Z*Cos(Pi*Z)*Sin(P)*Sin(Pi*(-10 + R))*
                  Sin(Pi*t))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
               (31.41592653589793*Z*Cos(P)*Cos(Pi*(-10 + R))*Sin(Pi*t)*
                  Sin(Pi*Z))/
                (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
               (3.141592653589793*(-10 + R)*Power(Z,2)*Cos(Pi*(-10 + R))*
                  Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
               (20.*(-10 + R)*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                  Sin(Pi*Z))/
                (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) + 
               (10.*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               4.934802200544679*
                (1 - (1.*Power(Z,2))/
                   (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(P)*
                Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))))/R) + 
     (R*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
         ((-4.*taue*Z*(-1000. + 20.*R - 2.*Power(Z,2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
           (4.*taue*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (3*Pi*Cos(3*Pi*Z)*(3.7699111843077517*R*Cos(3*Pi*R)*
                 Sin(3*P) - 0.06*Z*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*t))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) - 
           (27.925268031909273*(-50. + 1.*R - 0.1*Power(Z,2))*Cos(2*Pi*Z)*
              Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
              Sin(2*Pi*Z))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (4*beta*Pi*Cos(4*Pi*Z)*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (R*(-3141.592653589793 + 125.66370614359172*R - 
                   6.283185307179586*Power(R,2) - 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
                (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                 Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2)) - 
           (80.*Z*(-50. + 1.*R - 0.1*Power(Z,2))*
              (1.*taue - 0.1111111111111111*Power(Sin(2*P),2)*
                 Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                 Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
           (4.*Z*(1.*taue - 0.1111111111111111*Power(Sin(2*P),2)*
                 Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                 Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
           (0.06*Cos(3*P)*Sin(3*Pi*R)*Sin(3*Pi*t)*Sin(3*Pi*Z))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) - 
           (2.*Z*(3.7699111843077517*R*Cos(3*Pi*R)*Sin(3*P) - 
                0.06*Z*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (2*beta*Pi*Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (R*(-3141.592653589793 + 125.66370614359172*R - 
                   6.283185307179586*Power(R,2) - 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
                (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                 Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(4*Pi*Z))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2)) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (-12.566370614359172*R*Z*Cos(4*Pi*R)*Sin(4*P) + 
                (0.2*Power(Z,2)*Cos(4*P) + 
                   (50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) - 1.*Z*Sin(4*P))*Sin(4*Pi*R))*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*Sin(4*Pi*Z))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2)) - 
           (1.3333333333333333*beta*Z*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (R*(-3141.592653589793 + 125.66370614359172*R - 
                   6.283185307179586*Power(R,2) - 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
                (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                 Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              Sin(4*Pi*Z))/
            (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),
               3))) + 1.5707963267948966*R*Cos(Pi*Z)*Sin(P)*
         Sin(Pi*(-10 + R))*Sin(Pi*t)*
         ((taue*(-1000. + 20.*R - 2.*Power(Z,2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (20.*(-50. + 1.*R - 0.1*Power(Z,2))*
              (1.*taue - 0.1111111111111111*Power(Sin(2*P),2)*
                 Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                 Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           ((3.7699111843077517*R*Cos(3*Pi*R)*Sin(3*P) - 
                0.06*Z*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (R*(-3141.592653589793 + 125.66370614359172*R - 
                   6.283185307179586*Power(R,2) - 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
                (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                 Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              Sin(4*Pi*Z))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2))) + 
        R*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
         ((4.*R*(-20. + 2.*R)*taue*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
           (2.*taue*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (2.792526803190927*R*Z*Cos(2*Pi*R)*Power(Sin(2*P),2)*
              Sin(2*Pi*R)*Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
           (2*R*(-20. + 2.*R)*Z*
              (-2.*taue + 0.2222222222222222*Power(Sin(2*P),2)*
                 Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                 Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) + 
           (Z*(-2.*taue + 0.2222222222222222*Power(Sin(2*P),2)*
                 Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                 Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (Sin(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*Cos(3*Pi*Z)*Sin(3*P) - 
                0.06*Cos(3*P)*Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (3*Pi*Cos(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
                (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) - 
           ((-20. + 2.*R)*Sin(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
                (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(-125.66370614359172 + 12.566370614359172*R)*
                 Cos(4*Pi*Z)*Sin(4*P) + 
                (3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((70. - 6.*R + 0.30000000000000004*Power(R,2) + 
                      0.1*Power(Z,2))*Cos(4*P) - 0.5*Z*Sin(4*P))*
                 Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2)) + 
           (4*beta*Pi*Cos(4*Pi*R)*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2)) + 
           (2*beta*Pi*Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(4*Pi*R)*
              Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2)) - 
           (2*beta*(-20. + 2.*R)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*
              Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),3))) + 
        1.5707963267948966*R*Cos(Pi*(-10 + R))*Sin(P)*Sin(Pi*t)*Sin(Pi*Z)*
         (0. - (2.*R*taue*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (R*Z*(-2.*taue + 0.2222222222222222*Power(Sin(2*P),2)*
                 Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                 Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (Sin(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
                (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2))) + 
        (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
         (0. - (2.*R*taue*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (R*Z*(-2.*taue + 0.2222222222222222*Power(Sin(2*P),2)*
                 Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                 Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (Sin(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
                (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2))) + 
        R*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
         ((0.044444444444444446*
              (900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*Cos(2*P)*
              Sin(2*P)*Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
              Power(Sin(2*Pi*Z),2))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (3*Cos(3*P)*Sin(3*Pi*t)*
              (0.1884955592153876*Z*Cos(3*Pi*Z)*Sin(3*Pi*R) + 
                (-1.884955592153876 + 0.1884955592153876*R)*Cos(3*Pi*R)*
                 Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (4*beta*Cos(4*P)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (Z*(-157.07963267948966 + 6.283185307179586*R - 
                   0.3141592653589793*Power(R,2) - 
                   0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) \
+ ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                      0.3141592653589793*Power(R,3) + 
                      3.141592653589793*Power(Z,2) + 
                      R*(-219.9114857512855 - 
                        0.3141592653589793*Power(Z,2)))*Cos(4*Pi*R) + 
                   (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                    Sin(4*Pi*R))*Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2)) + 
           (2*beta*Cos(2*P)*Sin(4*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (Z*(-157.07963267948966 + 6.283185307179586*R - 
                   0.3141592653589793*Power(R,2) - 
                   0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) \
+ ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                      0.3141592653589793*Power(R,3) + 
                      3.141592653589793*Power(Z,2) + 
                      R*(-219.9114857512855 - 
                         0.3141592653589793*Power(Z,2)))*Cos(4*Pi*R) + 
                   (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                    Sin(4*Pi*R))*Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2))) + 
        0.5*R*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)*
         ((taue*(250000.00000000006 - 80.*Power(R,3) + 1.*Power(R,4) + 
                1000.0000000000001*Power(Z,2) + 1.*Power(Z,4) + 
                R*(-40000. - 80.*Power(Z,2)) + 
                Power(R,2)*(2200. + 2.*Power(Z,2))))/
            (R*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3)) - 
           (0.1*(900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*
              (1.*taue - 0.1111111111111111*Power(Sin(2*P),2)*
                 Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                 Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (Sin(3*P)*Sin(3*Pi*t)*
              (0.1884955592153876*Z*Cos(3*Pi*Z)*Sin(3*Pi*R) + 
                (-1.884955592153876 + 0.1884955592153876*R)*Cos(3*Pi*R)*
                 Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (beta*Sin(2*P)*Sin(4*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (Z*(-157.07963267948966 + 6.283185307179586*R - 
                   0.3141592653589793*Power(R,2) - 
                   0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) + 
                ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                      0.3141592653589793*Power(R,3) + 
                      3.141592653589793*Power(Z,2) + 
                      R*(-219.9114857512855 - 
                         0.3141592653589793*Power(Z,2)))*Cos(4*Pi*R) + 
                   (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                    Sin(4*Pi*R))*Sin(4*Pi*Z)))/
            (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
                1.*Power(Z,2),2))))/R)
; }};
struct SNi{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return 1.5707963267948966*Cos(Pi*t)*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*Z) + 
  FELTORPARALLEL*(-((nuparallel*
          (0. + (1.*Z*((-1.5707963267948966*(-10 + R)*Cos(Pi*Z)*Sin(P)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (1.5707963267948966*Z*Cos(Pi*(-10 + R))*Sin(P)*
                    Sin(Pi*t)*Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (10.*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                  (R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
             Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
            (1.*(-10 + R)*R*((4.934802200544679*Z*Cos(Pi*(-10 + R))*
                    Cos(Pi*Z)*Sin(P)*Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (31.41592653589793*Cos(P)*Cos(Pi*Z)*Sin(Pi*(-10 + R))*
                    Sin(Pi*t))/
                  (R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
                 (1.5707963267948966*(-10 + R)*Z*Cos(Pi*Z)*Sin(P)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t))/
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
                 (1.5707963267948966*Power(Z,2)*Cos(Pi*(-10 + R))*
                    Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) + 
                 (1.5707963267948966*Cos(Pi*(-10 + R))*Sin(P)*
                    Sin(Pi*t)*Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
                 (10.*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                  (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),
                     1.5)) + (4.934802200544679*(-10 + R)*Sin(P)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/
             Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
            (20*((-1.5707963267948966*(-10 + R)*Cos(P)*Cos(Pi*Z)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (1.5707963267948966*Z*Cos(P)*Cos(Pi*(-10 + R))*
                    Sin(Pi*t)*Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
                 (10.*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                  (R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
             Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
            (1.*R*Z*((-4.934802200544679*(-10 + R)*Cos(Pi*(-10 + R))*
                    Cos(Pi*Z)*Sin(P)*Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (1.5707963267948966*Power(-10 + R,2)*Cos(Pi*Z)*Sin(P)*
                    Sin(Pi*(-10 + R))*Sin(Pi*t))/
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
                 (1.5707963267948966*Cos(Pi*Z)*Sin(P)*Sin(Pi*(-10 + R))*
                    Sin(Pi*t))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
                 (31.41592653589793*Cos(P)*Cos(Pi*(-10 + R))*Sin(Pi*t)*
                    Sin(Pi*Z))/
                  (R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
                 (1.5707963267948966*(-10 + R)*Z*Cos(Pi*(-10 + R))*
                    Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
                 (10.*(-10 + R)*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                    Sin(Pi*Z))/
                  (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),
                     1.5)) - (10.*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                    Sin(Pi*Z))/
                  (Power(R,2)*
                    Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
                 (4.934802200544679*Z*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                    Sin(Pi*Z))/
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/
             Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/R) + 
     (0. - (2.0943951023931953*(-10 + R)*R*Cos(2*Pi*Z)*Sin(2*P)*
           Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
           (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)))/
         Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
        (0.5235987755982988*(-10 + R)*R*Cos(Pi*Z)*Sin(P)*Sin(2*P)*
           Sin(Pi*(-10 + R))*Sin(2*Pi*(-10 + R))*Sin(Pi*t)*Sin(2*Pi*t)*
           Sin(2*Pi*Z))/Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
        (0.5235987755982988*R*Z*Cos(Pi*(-10 + R))*Sin(P)*Sin(2*P)*
           Sin(2*Pi*(-10 + R))*Sin(Pi*t)*Sin(2*Pi*t)*Sin(Pi*Z)*Sin(2*Pi*Z)\
)/Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
        (3.3333333333333335*Cos(P)*Sin(2*P)*Sin(Pi*(-10 + R))*
           Sin(2*Pi*(-10 + R))*Sin(Pi*t)*Sin(2*Pi*t)*Sin(Pi*Z)*Sin(2*Pi*Z)\
)/Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
        (2.0943951023931953*R*Z*Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(2*Pi*t)*
           (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
           Sin(2*Pi*Z))/Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
        (40*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
           (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
           Sin(2*Pi*Z))/
         (3.*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
        (0.3333333333333333*Z*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
           (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
           Sin(2*Pi*Z))/Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))/R) + 
  FELTORPERP*(-((nuperp*((1.5707963267948966*(-10 + R)*Z*Cos(Pi*Z)*Sin(P)*
               Sin(Pi*(-10 + R))*Sin(Pi*t))/
             (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
            1.5707963267948966*
             (1 - (1.*Power(Z,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
             Cos(Pi*(-10 + R))*Sin(P)*Sin(Pi*t)*Sin(Pi*Z) - 
            (10.*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
             (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
            R*((4.934802200544679*(-10 + R)*Z*Cos(Pi*(-10 + R))*
                  Cos(Pi*Z)*Sin(P)*Sin(Pi*t))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
               (31.41592653589793*(-10 + R)*Cos(P)*Cos(Pi*Z)*
                  Sin(Pi*(-10 + R))*Sin(Pi*t))/
                (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
               (3.141592653589793*Power(-10 + R,2)*Z*Cos(Pi*Z)*Sin(P)*
                  Sin(Pi*(-10 + R))*Sin(Pi*t))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) - 
               (3.141592653589793*(-10 + R)*Power(Z,2)*Cos(Pi*(-10 + R))*
                  Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
               (1.5707963267948966*(-10 + R)*Cos(Pi*(-10 + R))*Sin(P)*
                  Sin(Pi*t)*Sin(Pi*Z))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
               (20.*(-10 + R)*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                  Sin(Pi*Z))/
                (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) - 
               4.934802200544679*
                (1 - (1.*Power(-10 + R,2))/
                   (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(P)*
                Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)) + 
            R*((31.41592653589793*(-10 + R)*Cos(P)*Cos(Pi*Z)*
                  Sin(Pi*(-10 + R))*Sin(Pi*t))/
                (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               (31.41592653589793*Z*Cos(P)*Cos(Pi*(-10 + R))*Sin(Pi*t)*
                  Sin(Pi*Z))/
                (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               0.5*(Power(R,-2) - 
                  400/
                   (Power(R,2)*
                     (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*Sin(P)*
                Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)) + 
            R*((4.934802200544679*(-10 + R)*Z*Cos(Pi*(-10 + R))*Cos(Pi*Z)*
                  Sin(P)*Sin(Pi*t))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
               (3.141592653589793*Power(-10 + R,2)*Z*Cos(Pi*Z)*Sin(P)*
                  Sin(Pi*(-10 + R))*Sin(Pi*t))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
               (1.5707963267948966*Z*Cos(Pi*Z)*Sin(P)*Sin(Pi*(-10 + R))*
                  Sin(Pi*t))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
               (31.41592653589793*Z*Cos(P)*Cos(Pi*(-10 + R))*Sin(Pi*t)*
                  Sin(Pi*Z))/
                (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
               (3.141592653589793*(-10 + R)*Power(Z,2)*Cos(Pi*(-10 + R))*
                  Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
               (20.*(-10 + R)*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
                  Sin(Pi*Z))/
                (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) + 
               (10.*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
                (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               4.934802200544679*
                (1 - (1.*Power(Z,2))/
                   (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(P)*
                Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))))/R) + 
     (R*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
         ((-4.*taui*Z*(-1000. + 20.*R - 2.*Power(Z,2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
           (4.*taui*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (3*Pi*Cos(3*Pi*Z)*(3.7699111843077517*R*Cos(3*Pi*R)*
                 Sin(3*P) - 0.06*Z*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*t))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (27.925268031909273*mui*(-50. + 1.*R - 0.1*Power(Z,2))*
              Cos(2*Pi*Z)*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
              Power(Sin(2*Pi*t),2)*Sin(2*Pi*Z))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (4*beta*Pi*Cos(4*Pi*Z)*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (R*(-3141.592653589793 + 125.66370614359172*R - 
                   6.283185307179586*Power(R,2) - 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
                (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                 Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) - 
           (8.88888888888889*Z*(-50. + 1.*R - 0.1*Power(Z,2))*
              (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                 Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
           (0.4444444444444445*Z*
              (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                 Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
           (0.06*Cos(3*P)*Sin(3*Pi*R)*Sin(3*Pi*t)*Sin(3*Pi*Z))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) - 
           (2.*Z*(3.7699111843077517*R*Cos(3*Pi*R)*Sin(3*P) - 
                0.06*Z*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (2*beta*Pi*Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (R*(-3141.592653589793 + 125.66370614359172*R - 
                   6.283185307179586*Power(R,2) - 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
                (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                 Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(4*Pi*Z))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (-12.566370614359172*R*Z*Cos(4*Pi*R)*Sin(4*P) + 
                (0.2*Power(Z,2)*Cos(4*P) + 
                   (50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) - 1.*Z*Sin(4*P))*Sin(4*Pi*R))*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*Sin(4*Pi*Z))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) - 
           (1.3333333333333333*beta*Z*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (R*(-3141.592653589793 + 125.66370614359172*R - 
                   6.283185307179586*Power(R,2) - 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
                (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                 Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              Sin(4*Pi*Z))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3)) + 
        1.5707963267948966*R*Cos(Pi*Z)*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
         ((taui*(-1000. + 20.*R - 2.*Power(Z,2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (2.2222222222222223*(-50. + 1.*R - 0.1*Power(Z,2))*
              (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                 Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           ((3.7699111843077517*R*Cos(3*Pi*R)*Sin(3*P) - 
                0.06*Z*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              (R*(-3141.592653589793 + 125.66370614359172*R - 
                   6.283185307179586*Power(R,2) - 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
                (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                    Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                 Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              Sin(4*Pi*Z))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))) + 
        R*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
         ((4.*R*(-20. + 2.*R)*taui*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
           (2.*taui*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
           (2.792526803190927*mui*R*Z*Cos(2*Pi*R)*Power(Sin(2*P),2)*
              Sin(2*Pi*R)*Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (0.4444444444444444*R*(-20. + 2.*R)*Z*
              (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                 Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
           (0.2222222222222222*Z*
              (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                 Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (Sin(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*Cos(3*Pi*Z)*Sin(3*P) - 
                0.06*Cos(3*P)*Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (3*Pi*Cos(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
                (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) - 
           ((-20. + 2.*R)*Sin(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
                (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(-125.66370614359172 + 12.566370614359172*R)*
                 Cos(4*Pi*Z)*Sin(4*P) + 
                (3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((70. - 6.*R + 0.30000000000000004*Power(R,2) + 
                      0.1*Power(Z,2))*Cos(4*P) - 0.5*Z*Sin(4*P))*
                 Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) + 
           (4*beta*Pi*Cos(4*Pi*R)*Sin(2*P)*Sin(2*Pi*(-10 + R))*
              Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) + 
           (2*beta*Pi*Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(4*Pi*R)*
              Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) - 
           (2*beta*(-20. + 2.*R)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*
              Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3))) + 
        1.5707963267948966*R*Cos(Pi*(-10 + R))*Sin(P)*Sin(Pi*t)*Sin(Pi*Z)*
         (0. - (2.*R*taui*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
           (0.2222222222222222*R*Z*
              (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                 Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (Sin(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
                (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))) + 
        (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
         (0. - (2.*R*taui*Z)/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
           (0.2222222222222222*R*Z*
              (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                 Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (Sin(3*Pi*R)*Sin(3*Pi*t)*
              (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
                (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (R*(3141.592653589793 - 125.66370614359172*R + 
                   6.283185307179586*Power(R,2) + 
                   6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
                ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                      1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                   0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))) + 
        R*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
         ((-0.044444444444444446*mui*
              (900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*Cos(2*P)*
              Sin(2*P)*Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
              Power(Sin(2*Pi*Z),2))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (3*Cos(3*P)*Sin(3*Pi*t)*
              (0.1884955592153876*Z*Cos(3*Pi*Z)*Sin(3*Pi*R) + 
                (-1.884955592153876 + 0.1884955592153876*R)*Cos(3*Pi*R)*
                 Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (4*beta*Cos(4*P)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (Z*(-157.07963267948966 + 6.283185307179586*R - 
                   0.3141592653589793*Power(R,2) - 
                   0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) \
+ ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                      0.3141592653589793*Power(R,3) + 
                      3.141592653589793*Power(Z,2) + 
                      R*(-219.9114857512855 - 
                        0.3141592653589793*Power(Z,2)))*Cos(4*Pi*R) + 
                   (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                    Sin(4*Pi*R))*Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) + 
           (2*beta*Cos(2*P)*Sin(4*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (Z*(-157.07963267948966 + 6.283185307179586*R - 
                   0.3141592653589793*Power(R,2) - 
                   0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) \
+ ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                      0.3141592653589793*Power(R,3) + 
                      3.141592653589793*Power(Z,2) + 
                      R*(-219.9114857512855 - 
                         0.3141592653589793*Power(Z,2)))*Cos(4*Pi*R) + 
                   (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                    Sin(4*Pi*R))*Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))) + 
        0.5*R*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)*
         ((taui*(250000.00000000006 - 80.*Power(R,3) + 1.*Power(R,4) + 
                1000.0000000000001*Power(Z,2) + 1.*Power(Z,4) + 
                R*(-40000. - 80.*Power(Z,2)) + 
                Power(R,2)*(2200. + 2.*Power(Z,2))))/
            (R*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3)) - 
           (0.011111111111111112*
              (900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*
              (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                 Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
            Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
           (Sin(3*P)*Sin(3*Pi*t)*
              (0.1884955592153876*Z*Cos(3*Pi*Z)*Sin(3*Pi*R) + 
                (-1.884955592153876 + 0.1884955592153876*R)*Cos(3*Pi*R)*
                 Sin(3*Pi*Z)))/
            (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
           (beta*Sin(2*P)*Sin(4*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
              Sin(4*Pi*t)*Sin(2*Pi*Z)*
              (Z*(-157.07963267948966 + 6.283185307179586*R - 
                   0.3141592653589793*Power(R,2) - 
                   0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) + 
                ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                      0.3141592653589793*Power(R,3) + 
                      3.141592653589793*Power(Z,2) + 
                      R*(-219.9114857512855 - 
                         0.3141592653589793*Power(Z,2)))*Cos(4*Pi*R) + 
                   (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                    Sin(4*Pi*R))*Sin(4*Pi*Z)))/
            (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))))/R)
; }};
struct SUe{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (2*Pi*Cos(2*Pi*t)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*Z))/(3.*Sqrt(-mue)) + 
  FELTORPARALLEL*((taue*Sin(Pi*t)*
        ((15.707963267948966 - 1.5707963267948966*R)*R*Cos(Pi*Z)*Sin(P)*
           Sin(Pi*R) + (1.5707963267948966*R*Z*Cos(Pi*R)*Sin(P) + 
             10.*Cos(P)*Sin(Pi*R))*Sin(Pi*Z)))/
      (mue*R*Sqrt(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*
        (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))) + 
     (0.6981317007977318*(-10 + R)*Cos(2*Pi*Z)*Power(Sin(2*P),2)*
        Power(Sin(2*Pi*(-10 + R)),2)*Power(Sin(2*Pi*t),2)*Sin(2*Pi*Z))/
      (mue*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
     (0.6981317007977318*Z*Cos(2*Pi*(-10 + R))*Power(Sin(2*P),2)*
        Sin(2*Pi*(-10 + R))*Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2))/
      (mue*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
     (40*Cos(2*P)*Sin(2*P)*Power(Sin(2*Pi*(-10 + R)),2)*
        Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2))/
      (9.*mue*R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
     (nuparallel*(0. + (1.*Z*((-2.0943951023931953*(-10 + R)*
                  Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2))) + 
               (2.0943951023931953*Z*Cos(2*Pi*(-10 + R))*Sin(2*P)*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2))) + 
               (40*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (3.*Sqrt(-mue)*R*
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
           Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
          (1.*(-10 + R)*R*((13.15947253478581*Z*Cos(2*Pi*(-10 + R))*
                  Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*t))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2))) + 
               (80*Pi*Cos(2*P)*Cos(2*Pi*Z)*Sin(2*Pi*(-10 + R))*
                  Sin(2*Pi*t))/
                (3.*Sqrt(-mue)*R*
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
               (2.0943951023931953*(-10 + R)*Z*Cos(2*Pi*Z)*Sin(2*P)*
                  Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                (Sqrt(-mue)*Power(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2),1.5)) - 
               (2.0943951023931953*Power(Z,2)*Cos(2*Pi*(-10 + R))*
                  Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (Sqrt(-mue)*Power(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2),1.5)) + 
               (2.0943951023931953*Cos(2*Pi*(-10 + R))*Sin(2*P)*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2))) - 
               (13.333333333333334*Z*Cos(2*P)*Sin(2*Pi*(-10 + R))*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (Sqrt(-mue)*R*
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5)) \
+ (13.15947253478581*(-10 + R)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
                  Sin(2*Pi*Z))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2)))))/
           Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (20*((-4.1887902047863905*(-10 + R)*Cos(2*P)*Cos(2*Pi*Z)*
                  Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2))) + 
               (4.1887902047863905*Z*Cos(2*P)*Cos(2*Pi*(-10 + R))*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2))) - 
               (80*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (3.*Sqrt(-mue)*R*
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
           Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (1.*R*Z*((-13.15947253478581*(-10 + R)*Cos(2*Pi*(-10 + R))*
                  Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*t))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2))) + 
               (2.0943951023931953*Power(-10 + R,2)*Cos(2*Pi*Z)*
                  Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                (Sqrt(-mue)*Power(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2),1.5)) - 
               (2.0943951023931953*Cos(2*Pi*Z)*Sin(2*P)*
                  Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2))) + 
               (80*Pi*Cos(2*P)*Cos(2*Pi*(-10 + R))*Sin(2*Pi*t)*
                  Sin(2*Pi*Z))/
                (3.*Sqrt(-mue)*R*
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               (2.0943951023931953*(-10 + R)*Z*Cos(2*Pi*(-10 + R))*
                  Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (Sqrt(-mue)*Power(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2),1.5)) - 
               (13.333333333333334*(-10 + R)*Cos(2*P)*
                  Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (Sqrt(-mue)*R*
                  Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5)) - 
               (40*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (3.*Sqrt(-mue)*Power(R,2)*
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               (13.15947253478581*Z*Sin(2*P)*Sin(2*Pi*(-10 + R))*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (Sqrt(-mue)*Sqrt(400 + 1.*Power(-10 + R,2) + 
                    1.*Power(Z,2)))))/
           Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/R + 
     (Sin(3*Pi*t)*((18.84955592153876 - 1.8849555921538759*R)*R*
           Cos(3*Pi*Z)*Sin(3*P)*Sin(3*Pi*R) + 
          (1.8849555921538759*R*Z*Cos(3*Pi*R)*Sin(3*P) + 
             12.*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*Z)))/
      (mue*R*Sqrt(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)))) + 
  (beta*Pi*Cos(4*Pi*t)*Sin(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*Z))/mue + 
  FELTORPERP*(0. + (eta*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
           Sin(Pi*Z))*((Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
             Sin(2*Pi*Z))/3. - 
          (Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
           (3.*Sqrt(-mue))))/mue + 
     ((41.8879020478639*R*taue*(-50. + 1.*R - 0.1*Power(Z,2))*Cos(2*Pi*Z)*
           Sin(2*P)*Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z)))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) \
+ (20.94395102393195*R*taue*(-50. + 1.*R - 0.1*Power(Z,2))*Cos(Pi*Z)*
           Sin(P)*Sin(2*P)*Sin(Pi*R)*Sin(2*Pi*R)*Sin(Pi*t)*Sin(2*Pi*t)*
           Sin(2*Pi*Z))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) \
- (2.0943951023931953*Power(R,2)*taue*Z*Cos(Pi*R)*Sin(P)*Sin(2*P)*
           Sin(2*Pi*R)*Sin(Pi*t)*Sin(2*Pi*t)*Sin(Pi*Z)*Sin(2*Pi*Z))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) \
- (0.03333333333333333*R*taue*
           (900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*Cos(P)*Sin(2*P)*
           Sin(Pi*R)*Sin(2*Pi*R)*Sin(Pi*t)*Sin(2*Pi*t)*Sin(Pi*Z)*
           Sin(2*Pi*Z))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) \
- (4.1887902047863905*Power(R,2)*taue*Z*Cos(2*Pi*R)*Sin(2*P)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) \
- (0.06666666666666667*R*taue*
           (900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*Cos(2*P)*
           Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) \
+ (1.3333333333333333*Power(R,2)*(-20. + 2.*R)*taue*Z*Sin(2*P)*
           Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3)) \
- (26.666666666666664*R*taue*Z*(-50. + 1.*R - 0.1*Power(Z,2))*Sin(2*P)*
           Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3)) \
- (2.6666666666666665*R*taue*Z*Sin(2*P)*Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         (Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)))/
      (R*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))) - 
     (nuperp*((2.0943951023931953*(-10 + R)*Z*Cos(2*Pi*Z)*Sin(2*P)*
             Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
           (Sqrt(-mue)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
          (2*Pi*(1 - (1.*Power(Z,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
             Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
           (3.*Sqrt(-mue)) - (13.333333333333332*Z*Cos(2*P)*
             Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
           (Sqrt(-mue)*R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
          R*((13.15947253478581*(-10 + R)*Z*Cos(2*Pi*(-10 + R))*
                Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*t))/
              (Sqrt(-mue)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
             (83.7758040957278*(-10 + R)*Cos(2*P)*Cos(2*Pi*Z)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              (Sqrt(-mue)*R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
             (4.1887902047863905*Power(-10 + R,2)*Z*Cos(2*Pi*Z)*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              (Sqrt(-mue)*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),
                 2)) - (4.1887902047863905*(-10 + R)*Power(Z,2)*
                Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (Sqrt(-mue)*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),
                 2)) + (2.0943951023931953*(-10 + R)*Cos(2*Pi*(-10 + R))*
                Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (Sqrt(-mue)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (26.666666666666664*(-10 + R)*Z*Cos(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (Sqrt(-mue)*R*Power(400 + 1.*Power(-10 + R,2) + 
                  1.*Power(Z,2),2)) - 
             (4*Power(Pi,2)*(1 - 
                  (1.*Power(-10 + R,2))/
                   (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (3.*Sqrt(-mue))) + 
          R*((83.7758040957278*(-10 + R)*Cos(2*P)*Cos(2*Pi*Z)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              (Sqrt(-mue)*R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (83.7758040957278*Z*Cos(2*P)*Cos(2*Pi*(-10 + R))*
                Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (Sqrt(-mue)*R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (4*(Power(R,-2) - 
                  400/
                   (Power(R,2)*
                     (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*
                Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (3.*Sqrt(-mue))) + 
          R*((13.15947253478581*(-10 + R)*Z*Cos(2*Pi*(-10 + R))*
                Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*t))/
              (Sqrt(-mue)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (4.1887902047863905*Power(-10 + R,2)*Z*Cos(2*Pi*Z)*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              (Sqrt(-mue)*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),
                 2)) + (2.0943951023931953*Z*Cos(2*Pi*Z)*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              (Sqrt(-mue)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (83.7758040957278*Z*Cos(2*P)*Cos(2*Pi*(-10 + R))*Sin(2*Pi*t)*
                Sin(2*Pi*Z))/
              (Sqrt(-mue)*R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
             (4.1887902047863905*(-10 + R)*Power(Z,2)*Cos(2*Pi*(-10 + R))*
                Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (Sqrt(-mue)*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),
                 2)) + (26.666666666666664*(-10 + R)*Z*Cos(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (Sqrt(-mue)*R*Power(400 + 1.*Power(-10 + R,2) + 
                  1.*Power(Z,2),2)) + 
             (13.333333333333332*Z*Cos(2*P)*Sin(2*Pi*(-10 + R))*
                Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (Sqrt(-mue)*Power(R,2)*
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (4*Power(Pi,2)*(1 - 
                  (1.*Power(Z,2))/
                   (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/(3.*Sqrt(-mue))\
)))/R + (Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(3*Pi*t)*Sin(2*Pi*Z)*
        ((-1884.9555921538758 + 37.69911184307752*R - 
             3.7699111843077526*Power(Z,2))*Cos(3*Pi*Z)*Sin(3*P)*
           Sin(3*Pi*R) + (-3.7699111843077517*R*Z*Cos(3*Pi*R)*Sin(3*P) + 
             (-54. + 1.2000000000000002*R - 
                0.06000000000000001*Power(R,2) - 
                0.06000000000000001*Power(Z,2))*Cos(3*P)*Sin(3*Pi*R))*
           Sin(3*Pi*Z)))/
      (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) + 
     (2*Pi*Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
        ((taue*(-1000. + 20.*R - 2.*Power(Z,2)))/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          (20.*(-50. + 1.*R - 0.1*Power(Z,2))*
             (1.*taue - 0.1111111111111111*Power(Sin(2*P),2)*
                Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                Power(Sin(2*Pi*Z),2)))/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          ((3.7699111843077517*R*Cos(3*Pi*R)*Sin(3*P) - 
               0.06*Z*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
          (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*
             (R*(-3141.592653589793 + 125.66370614359172*R - 
                  6.283185307179586*Power(R,2) - 
                  6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
               (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                   Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
             Sin(4*Pi*Z))/
           (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
               1.*Power(Z,2),2))))/(3.*Sqrt(-mue)) + 
     (2*Pi*Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z)*
        (0. - (2.*R*taue*Z)/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          (R*Z*(-2.*taue + 0.2222222222222222*Power(Sin(2*P),2)*
                Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                Power(Sin(2*Pi*Z),2)))/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          (Sin(3*Pi*R)*Sin(3*Pi*t)*
             (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
               (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
           (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
          (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*Sin(2*Pi*t)*
             Sin(4*Pi*t)*Sin(2*Pi*Z)*
             (R*(3141.592653589793 - 125.66370614359172*R + 
                  6.283185307179586*Power(R,2) + 
                  6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
               ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                     1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                  0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
           (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
               1.*Power(Z,2),2))))/(3.*Sqrt(-mue)) + 
     (beta*taue*Sin(Pi*t)*Sin(4*Pi*t)*
        (1.5707963267948966*Cos(Pi*Z)*Sin(P)*Sin(Pi*R)*
           (R*(-3141.592653589793 + 125.66370614359172*R - 
                6.283185307179586*Power(R,2) - 
                6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
             (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                 Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
              Sin(4*Pi*R))*Sin(4*Pi*Z) + 
          1.5707963267948966*Cos(Pi*R)*Sin(P)*Sin(4*Pi*R)*Sin(Pi*Z)*
           (R*(3141.592653589793 - 125.66370614359172*R + 
                6.283185307179586*Power(R,2) + 
                6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
             ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                   1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)) + 
          0.5*Cos(P)*Sin(4*P)*Sin(Pi*R)*Sin(Pi*Z)*
           (Z*(-157.07963267948966 + 6.283185307179586*R - 
                0.3141592653589793*Power(R,2) - 
                0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) + 
             ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                   0.3141592653589793*Power(R,3) + 
                   3.141592653589793*Power(Z,2) + 
                   R*(-219.9114857512855 - 0.3141592653589793*Power(Z,2))\
)*Cos(4*Pi*R) + (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                 Sin(4*Pi*R))*Sin(4*Pi*Z))))/
      (mue*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)*
        (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))) + 
     (2*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z)*
        ((taue*(250000.00000000006 - 80.*Power(R,3) + 1.*Power(R,4) + 
               1000.0000000000001*Power(Z,2) + 1.*Power(Z,4) + 
               R*(-40000. - 80.*Power(Z,2)) + 
               Power(R,2)*(2200. + 2.*Power(Z,2))))/
           (R*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3)) - 
          (0.1*(900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*
             (1.*taue - 0.1111111111111111*Power(Sin(2*P),2)*
                Power(Sin(2*Pi*R),2)*Power(Sin(2*Pi*t),2)*
                Power(Sin(2*Pi*Z),2)))/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          (Sin(3*P)*Sin(3*Pi*t)*
             (0.1884955592153876*Z*Cos(3*Pi*Z)*Sin(3*Pi*R) + 
               (-1.884955592153876 + 0.1884955592153876*R)*Cos(3*Pi*R)*
                Sin(3*Pi*Z)))/
           (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
          (beta*Sin(2*P)*Sin(4*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
             Sin(4*Pi*t)*Sin(2*Pi*Z)*
             (Z*(-157.07963267948966 + 6.283185307179586*R - 
                  0.3141592653589793*Power(R,2) - 
                  0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) + 
               ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                     0.3141592653589793*Power(R,3) + 
                     3.141592653589793*Power(Z,2) + 
                     R*(-219.9114857512855 - 
                        0.3141592653589793*Power(Z,2)))*Cos(4*Pi*R) + 
                  (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                   Sin(4*Pi*R))*Sin(4*Pi*Z)))/
           (3.*Sqrt(-mue)*Power(500. - 20.*R + 1.*Power(R,2) + 
               1.*Power(Z,2),2))))/(3.*Sqrt(-mue)) + 
     (3*beta*Sin(3*Pi*t)*Sin(4*Pi*t)*
        (Pi*Cos(3*Pi*Z)*Sin(3*P)*Sin(3*Pi*R)*
           (R*(-3141.592653589793 + 125.66370614359172*R - 
                6.283185307179586*Power(R,2) - 
                6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
             (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*Cos(4*P) + 
                (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*Sin(4*Pi*R))*
           Sin(4*Pi*Z) + Pi*Cos(3*Pi*R)*Sin(3*P)*Sin(4*Pi*R)*Sin(3*Pi*Z)*
           (R*(3141.592653589793 - 125.66370614359172*R + 
                6.283185307179586*Power(R,2) + 
                6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
             ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                   1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)) + 
          Cos(3*P)*Sin(4*P)*Sin(3*Pi*R)*Sin(3*Pi*Z)*
           (Z*(-157.07963267948966 + 6.283185307179586*R - 
                0.3141592653589793*Power(R,2) - 
                0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) + 
             ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                   0.3141592653589793*Power(R,3) + 
                   3.141592653589793*Power(Z,2) + 
                   R*(-219.9114857512855 - 0.3141592653589793*Power(Z,2)))*
                 Cos(4*Pi*R) + 
                (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                 Sin(4*Pi*R))*Sin(4*Pi*Z))))/
      (5.*mue*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)))
; }};
struct SUi{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (2*Pi*Cos(2*Pi*t)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*Z))/3. + 
  FELTORPARALLEL*((taui*Sin(Pi*t)*
        ((15.707963267948966 - 1.5707963267948966*R)*R*Cos(Pi*Z)*Sin(P)*
           Sin(Pi*R) + (1.5707963267948966*R*Z*Cos(Pi*R)*Sin(P) + 
             10.*Cos(P)*Sin(Pi*R))*Sin(Pi*Z)))/
      (mui*R*Sqrt(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*
        (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))) - 
     (0.6981317007977318*(-10 + R)*Cos(2*Pi*Z)*Power(Sin(2*P),2)*
        Power(Sin(2*Pi*(-10 + R)),2)*Power(Sin(2*Pi*t),2)*Sin(2*Pi*Z))/
      Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
     (0.6981317007977318*Z*Cos(2*Pi*(-10 + R))*Power(Sin(2*P),2)*
        Sin(2*Pi*(-10 + R))*Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2))/
      Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
     (40*Cos(2*P)*Sin(2*P)*Power(Sin(2*Pi*(-10 + R)),2)*
        Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2))/
      (9.*R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
     (nuparallel*(0. + (1.*Z*((-2.0943951023931953*(-10 + R)*
                  Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
               (2.0943951023931953*Z*Cos(2*Pi*(-10 + R))*Sin(2*P)*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
               (40*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (3.*R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
           Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
          (1.*(-10 + R)*R*((13.15947253478581*Z*Cos(2*Pi*(-10 + R))*
                  Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*t))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
               (80*Pi*Cos(2*P)*Cos(2*Pi*Z)*Sin(2*Pi*(-10 + R))*
                  Sin(2*Pi*t))/
                (3.*R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
               (2.0943951023931953*(-10 + R)*Z*Cos(2*Pi*Z)*Sin(2*P)*
                  Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
               (2.0943951023931953*Power(Z,2)*Cos(2*Pi*(-10 + R))*
                  Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) + 
               (2.0943951023931953*Cos(2*Pi*(-10 + R))*Sin(2*P)*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
               (13.333333333333334*Z*Cos(2*P)*Sin(2*Pi*(-10 + R))*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5)) \
+ (13.15947253478581*(-10 + R)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
                  Sin(2*Pi*Z))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/
           Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (20*((-4.1887902047863905*(-10 + R)*Cos(2*P)*Cos(2*Pi*Z)*
                  Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
               (4.1887902047863905*Z*Cos(2*P)*Cos(2*Pi*(-10 + R))*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
               (80*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (3.*R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
           Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (1.*R*Z*((-13.15947253478581*(-10 + R)*Cos(2*Pi*(-10 + R))*
                  Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*t))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
               (2.0943951023931953*Power(-10 + R,2)*Cos(2*Pi*Z)*
                  Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
               (2.0943951023931953*Cos(2*Pi*Z)*Sin(2*P)*
                  Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
               (80*Pi*Cos(2*P)*Cos(2*Pi*(-10 + R))*Sin(2*Pi*t)*
                  Sin(2*Pi*Z))/
                (3.*R*Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               (2.0943951023931953*(-10 + R)*Z*Cos(2*Pi*(-10 + R))*
                  Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5) - 
               (13.333333333333334*(-10 + R)*Cos(2*P)*
                  Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),1.5)) \
- (40*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
                (3.*Power(R,2)*
                  Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
               (13.15947253478581*Z*Sin(2*P)*Sin(2*Pi*(-10 + R))*
                  Sin(2*Pi*t)*Sin(2*Pi*Z))/
                Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/
           Sqrt(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/R + 
     (Sin(3*Pi*t)*((18.84955592153876 - 1.8849555921538759*R)*R*
           Cos(3*Pi*Z)*Sin(3*P)*Sin(3*Pi*R) + 
          (1.8849555921538759*R*Z*Cos(3*Pi*R)*Sin(3*P) + 
             12.*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*Z)))/
      (mui*R*Sqrt(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)))) + 
  (beta*Pi*Cos(4*Pi*t)*Sin(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*Z))/mui + 
  FELTORPERP*(0. + (eta*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
           Sin(Pi*Z))*((Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
             Sin(2*Pi*Z))/3. - 
          (Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
           (3.*Sqrt(-mue))))/mui + 
     ((41.8879020478639*R*taui*(-50. + 1.*R - 0.1*Power(Z,2))*Cos(2*Pi*Z)*
           Sin(2*P)*Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z)))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
        (20.94395102393195*R*taui*(-50. + 1.*R - 0.1*Power(Z,2))*
           Cos(Pi*Z)*Sin(P)*Sin(2*P)*Sin(Pi*R)*Sin(2*Pi*R)*Sin(Pi*t)*
           Sin(2*Pi*t)*Sin(2*Pi*Z))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
        (2.0943951023931953*Power(R,2)*taui*Z*Cos(Pi*R)*Sin(P)*Sin(2*P)*
           Sin(2*Pi*R)*Sin(Pi*t)*Sin(2*Pi*t)*Sin(Pi*Z)*Sin(2*Pi*Z))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
        (0.03333333333333333*R*taui*
           (900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*Cos(P)*Sin(2*P)*
           Sin(Pi*R)*Sin(2*Pi*R)*Sin(Pi*t)*Sin(2*Pi*t)*Sin(Pi*Z)*
           Sin(2*Pi*Z))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
        (4.1887902047863905*Power(R,2)*taui*Z*Cos(2*Pi*R)*Sin(2*P)*
           Sin(2*Pi*t)*(2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*
           Sin(2*Pi*Z))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
        (0.06666666666666667*R*taui*
           (900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*Cos(2*P)*
           Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
        (1.3333333333333333*Power(R,2)*(-20. + 2.*R)*taui*Z*Sin(2*P)*
           Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
        (26.666666666666664*R*taui*Z*(-50. + 1.*R - 0.1*Power(Z,2))*
           Sin(2*P)*Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3) - 
        (2.6666666666666665*R*taui*Z*Sin(2*P)*Sin(2*Pi*R)*Sin(2*Pi*t)*
           (2. + 1.*Sin(P)*Sin(Pi*R)*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
         Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))/
      (R*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))) - 
     (nuperp*((2.0943951023931953*(-10 + R)*Z*Cos(2*Pi*Z)*Sin(2*P)*
             Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (2*Pi*(1 - (1.*Power(Z,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
             Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/3. - 
          (13.333333333333332*Z*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
             Sin(2*Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
          R*((13.15947253478581*(-10 + R)*Z*Cos(2*Pi*(-10 + R))*
                Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*t))/
              (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
             (83.7758040957278*(-10 + R)*Cos(2*P)*Cos(2*Pi*Z)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
             (4.1887902047863905*Power(-10 + R,2)*Z*Cos(2*Pi*Z)*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) - 
             (4.1887902047863905*(-10 + R)*Power(Z,2)*
                Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
             (2.0943951023931953*(-10 + R)*Cos(2*Pi*(-10 + R))*Sin(2*P)*
                Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
             (26.666666666666664*(-10 + R)*Z*Cos(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) - 
             (4*Power(Pi,2)*(1 - 
                  (1.*Power(-10 + R,2))/
                   (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/3.) + 
          R*((83.7758040957278*(-10 + R)*Cos(2*P)*Cos(2*Pi*Z)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (83.7758040957278*Z*Cos(2*P)*Cos(2*Pi*(-10 + R))*
                Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (4*(Power(R,-2) - 
                  400/
                   (Power(R,2)*
                     (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*
                Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/3.) + 
          R*((13.15947253478581*(-10 + R)*Z*Cos(2*Pi*(-10 + R))*
                Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*t))/
              (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
             (4.1887902047863905*Power(-10 + R,2)*Z*Cos(2*Pi*Z)*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
             (2.0943951023931953*Z*Cos(2*Pi*Z)*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t))/
              (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
             (83.7758040957278*Z*Cos(2*P)*Cos(2*Pi*(-10 + R))*Sin(2*Pi*t)*
                Sin(2*Pi*Z))/
              (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
             (4.1887902047863905*(-10 + R)*Power(Z,2)*Cos(2*Pi*(-10 + R))*
                Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z))/
              Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
             (26.666666666666664*(-10 + R)*Z*Cos(2*P)*Sin(2*Pi*(-10 + R))*
                Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) + 
             (13.333333333333332*Z*Cos(2*P)*Sin(2*Pi*(-10 + R))*
                Sin(2*Pi*t)*Sin(2*Pi*Z))/
              (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
             (4*Power(Pi,2)*(1 - 
                  (1.*Power(Z,2))/
                   (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(2*P)*
                Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z))/3.)))/R + 
     (Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(3*Pi*t)*Sin(2*Pi*Z)*
        ((-1884.9555921538758 + 37.69911184307752*R - 
             3.7699111843077526*Power(Z,2))*Cos(3*Pi*Z)*Sin(3*P)*
           Sin(3*Pi*R) + (-3.7699111843077517*R*Z*Cos(3*Pi*R)*Sin(3*P) + 
             (-54. + 1.2000000000000002*R - 
                0.06000000000000001*Power(R,2) - 
                0.06000000000000001*Power(Z,2))*Cos(3*P)*Sin(3*Pi*R))*
           Sin(3*Pi*Z)))/
      (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)) + 
     (2*Pi*Cos(2*Pi*Z)*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
        ((taui*(-1000. + 20.*R - 2.*Power(Z,2)))/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          (2.2222222222222223*(-50. + 1.*R - 0.1*Power(Z,2))*
             (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          ((3.7699111843077517*R*Cos(3*Pi*R)*Sin(3*P) - 
               0.06*Z*Cos(3*P)*Sin(3*Pi*R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
          (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*
             (R*(-3141.592653589793 + 125.66370614359172*R - 
                  6.283185307179586*Power(R,2) - 
                  6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
               (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                   Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
                Sin(4*Pi*R))*Sin(2*Pi*t)*Sin(4*Pi*t)*Sin(2*Pi*Z)*
             Sin(4*Pi*Z))/
           (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))))/3. + 
     (2*Pi*Cos(2*Pi*(-10 + R))*Sin(2*P)*Sin(2*Pi*t)*Sin(2*Pi*Z)*
        (0. - (2.*R*taui*Z)/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) - 
          (0.2222222222222222*R*Z*
             (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          (Sin(3*Pi*R)*Sin(3*Pi*t)*
             (-3.7699111843077517*R*Cos(3*Pi*Z)*Sin(3*P) + 
               (0.6 - 0.06*R)*Cos(3*P)*Sin(3*Pi*Z)))/
           (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
          (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(4*Pi*R)*Sin(2*Pi*t)*
             Sin(4*Pi*t)*Sin(2*Pi*Z)*
             (R*(3141.592653589793 - 125.66370614359172*R + 
                  6.283185307179586*Power(R,2) + 
                  6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
               ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                     1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                  0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)))/
           (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))))/3. + 
     (beta*taui*Sin(Pi*t)*Sin(4*Pi*t)*
        (1.5707963267948966*Cos(Pi*Z)*Sin(P)*Sin(Pi*R)*
           (R*(-3141.592653589793 + 125.66370614359172*R - 
                6.283185307179586*Power(R,2) - 
                6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
             (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*
                 Cos(4*P) + (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*
              Sin(4*Pi*R))*Sin(4*Pi*Z) + 
          1.5707963267948966*Cos(Pi*R)*Sin(P)*Sin(4*Pi*R)*Sin(Pi*Z)*
           (R*(3141.592653589793 - 125.66370614359172*R + 
                6.283185307179586*Power(R,2) + 
                6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
             ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                   1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)) + 
          0.5*Cos(P)*Sin(4*P)*Sin(Pi*R)*Sin(Pi*Z)*
           (Z*(-157.07963267948966 + 6.283185307179586*R - 
                0.3141592653589793*Power(R,2) - 
                0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) + 
             ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                   0.3141592653589793*Power(R,3) + 
                   3.141592653589793*Power(Z,2) + 
                   R*(-219.9114857512855 - 0.3141592653589793*Power(Z,2))\
)*Cos(4*Pi*R) + (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                 Sin(4*Pi*R))*Sin(4*Pi*Z))))/
      (mui*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)*
        (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))) + 
     (2*Cos(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*Sin(2*Pi*Z)*
        ((taui*(250000.00000000006 - 80.*Power(R,3) + 1.*Power(R,4) + 
               1000.0000000000001*Power(Z,2) + 1.*Power(Z,4) + 
               R*(-40000. - 80.*Power(Z,2)) + 
               Power(R,2)*(2200. + 2.*Power(Z,2))))/
           (R*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),3)) - 
          (0.011111111111111112*
             (900. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2))*
             (9.*taui + mui*Power(Sin(2*P),2)*Power(Sin(2*Pi*R),2)*
                Power(Sin(2*Pi*t),2)*Power(Sin(2*Pi*Z),2)))/
           Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2) + 
          (Sin(3*P)*Sin(3*Pi*t)*
             (0.1884955592153876*Z*Cos(3*Pi*Z)*Sin(3*Pi*R) + 
               (-1.884955592153876 + 0.1884955592153876*R)*Cos(3*Pi*R)*
                Sin(3*Pi*Z)))/
           (500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2)) + 
          (beta*Sin(2*P)*Sin(4*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
             Sin(4*Pi*t)*Sin(2*Pi*Z)*
             (Z*(-157.07963267948966 + 6.283185307179586*R - 
                  0.3141592653589793*Power(R,2) - 
                  0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) + 
               ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                     0.3141592653589793*Power(R,3) + 
                     3.141592653589793*Power(Z,2) + 
                     R*(-219.9114857512855 - 
                        0.3141592653589793*Power(Z,2)))*Cos(4*Pi*R) + 
                  (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                   Sin(4*Pi*R))*Sin(4*Pi*Z)))/
           (3.*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2))))/3. + 
     (3*beta*Sin(3*Pi*t)*Sin(4*Pi*t)*
        (Pi*Cos(3*Pi*Z)*Sin(3*P)*Sin(3*Pi*R)*
           (R*(-3141.592653589793 + 125.66370614359172*R - 
                6.283185307179586*Power(R,2) - 
                6.283185307179586*Power(Z,2))*Cos(4*Pi*R)*Sin(4*P) + 
             (Z*(50. - 2.*R + 0.1*Power(R,2) + 0.1*Power(Z,2))*Cos(4*P) + 
                (-250. + 5.*R - 0.5*Power(Z,2))*Sin(4*P))*Sin(4*Pi*R))*
           Sin(4*Pi*Z) + Pi*Cos(3*Pi*R)*Sin(3*P)*Sin(4*Pi*R)*Sin(3*Pi*Z)*
           (R*(3141.592653589793 - 125.66370614359172*R + 
                6.283185307179586*Power(R,2) + 
                6.283185307179586*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*P) + 
             ((-500. + 70.*R - 3.*Power(R,2) + 0.1*Power(R,3) - 
                   1.*Power(Z,2) + 0.1*R*Power(Z,2))*Cos(4*P) - 
                0.5*R*Z*Sin(4*P))*Sin(4*Pi*Z)) + 
          Cos(3*P)*Sin(4*P)*Sin(3*Pi*R)*Sin(3*Pi*Z)*
           (Z*(-157.07963267948966 + 6.283185307179586*R - 
                0.3141592653589793*Power(R,2) - 
                0.3141592653589793*Power(Z,2))*Cos(4*Pi*Z)*Sin(4*Pi*R) + 
             ((1570.7963267948965 + 9.42477796076938*Power(R,2) - 
                   0.3141592653589793*Power(R,3) + 
                   3.141592653589793*Power(Z,2) + 
                   R*(-219.9114857512855 - 0.3141592653589793*Power(Z,2)))*
                 Cos(4*Pi*R) + 
                (-22.5 + 0.5*R - 0.025*Power(R,2) - 0.025*Power(Z,2))*
                 Sin(4*Pi*R))*Sin(4*Pi*Z))))/
      (5.*mui*Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)))
; }};
struct SPhie{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return 0. - ((0.015707963267948967*Power(R,3)*Cos(Pi*Z)*Sin(P)*Sin(Pi*(-10 + R))*
        Sin(Pi*t)*((3*Pi*(1 - 
               (1.*Power(-10 + R,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Cos(3*Pi*Z)*
             Sin(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/5. + 
          (1.8849555921538759*(-10 + R)*Z*Cos(3*Pi*(-10 + R))*Sin(3*P)*
             Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (12.*(-10 + R)*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*
             Sin(3*Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
      (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
     (0.02*Power(R,3)*Z*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*
           Sin(Pi*Z))*((3*Pi*(1 - 
               (1.*Power(-10 + R,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Cos(3*Pi*Z)*
             Sin(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/5. + 
          (1.8849555921538759*(-10 + R)*Z*Cos(3*Pi*(-10 + R))*Sin(3*P)*
             Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (12.*(-10 + R)*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*
             Sin(3*Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
      Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
     (0.015707963267948967*Power(R,3)*Cos(Pi*(-10 + R))*Sin(P)*Sin(Pi*t)*
        Sin(Pi*Z)*((1.8849555921538759*(-10 + R)*Z*Cos(3*Pi*Z)*Sin(3*P)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (3*Pi*(1 - (1.*Power(Z,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
             Cos(3*Pi*(-10 + R))*Sin(3*P)*Sin(3*Pi*t)*Sin(3*Pi*Z))/5. - 
          (12.*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
      (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
     (0.02*(-10 + R)*Power(R,3)*
        (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
        ((1.8849555921538759*(-10 + R)*Z*Cos(3*Pi*Z)*Sin(3*P)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (3*Pi*(1 - (1.*Power(Z,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
             Cos(3*Pi*(-10 + R))*Sin(3*P)*Sin(3*Pi*t)*Sin(3*Pi*Z))/5. - 
          (12.*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
      Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
     (3*Power(R,2)*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
        ((1.8849555921538759*(-10 + R)*Z*Cos(3*Pi*Z)*Sin(3*P)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (3*Pi*(1 - (1.*Power(Z,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
             Cos(3*Pi*(-10 + R))*Sin(3*P)*Sin(3*Pi*t)*Sin(3*Pi*Z))/5. - 
          (12.*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))))/
      (100.*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
     (0.005*Power(R,3)*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)*
        ((37.69911184307752*(-10 + R)*Cos(3*Pi*Z)*Sin(3*P)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
           (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
          (37.69911184307752*Z*Cos(3*Pi*(-10 + R))*Sin(3*P)*Sin(3*Pi*t)*
             Sin(3*Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) \
+ (3*(Power(R,-2) - 400/
                (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*
             Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.))/
      (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
     (Power(R,3)*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
        ((17.765287921960844*(-10 + R)*Z*Cos(3*Pi*(-10 + R))*Cos(3*Pi*Z)*
             Sin(3*P)*Sin(3*Pi*t))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
          (113.09733552923255*(-10 + R)*Cos(3*P)*Cos(3*Pi*Z)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
           (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
          (3.7699111843077517*Power(-10 + R,2)*Z*Cos(3*Pi*Z)*Sin(3*P)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
           Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) - 
          (3.7699111843077517*(-10 + R)*Power(Z,2)*Cos(3*Pi*(-10 + R))*
             Sin(3*P)*Sin(3*Pi*t)*Sin(3*Pi*Z))/
           Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
          (1.8849555921538759*(-10 + R)*Cos(3*Pi*(-10 + R))*Sin(3*P)*
             Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
          (24.*(-10 + R)*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*
             Sin(3*Pi*Z))/
           (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) - 
          (9*Power(Pi,2)*(1 - 
               (1.*Power(-10 + R,2))/
                (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(3*P)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.))/
      (100.*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
     (Power(R,3)*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
        ((113.09733552923255*(-10 + R)*Cos(3*P)*Cos(3*Pi*Z)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
           (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
          (113.09733552923255*Z*Cos(3*P)*Cos(3*Pi*(-10 + R))*Sin(3*Pi*t)*
             Sin(3*Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) \
- (9*(Power(R,-2) - 400/
                (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*
             Sin(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.))/
      (100.*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
     (Power(R,3)*(1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*
        ((17.765287921960844*(-10 + R)*Z*Cos(3*Pi*(-10 + R))*Cos(3*Pi*Z)*
             Sin(3*P)*Sin(3*Pi*t))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
          (3.7699111843077517*Power(-10 + R,2)*Z*Cos(3*Pi*Z)*Sin(3*P)*
             Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
           Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
          (1.8849555921538759*Z*Cos(3*Pi*Z)*Sin(3*P)*Sin(3*Pi*(-10 + R))*
             Sin(3*Pi*t))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
          (113.09733552923255*Z*Cos(3*P)*Cos(3*Pi*(-10 + R))*Sin(3*Pi*t)*
             Sin(3*Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
          (3.7699111843077517*(-10 + R)*Power(Z,2)*Cos(3*Pi*(-10 + R))*
             Sin(3*P)*Sin(3*Pi*t)*Sin(3*Pi*Z))/
           Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
          (24.*(-10 + R)*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*
             Sin(3*Pi*Z))/
           (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) + 
          (12.*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
           (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
          (9*Power(Pi,2)*(1 - 
               (1.*Power(Z,2))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))\
)*Sin(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.))/
      (100.*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))/R
; }};
struct SPhii{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (0.017765287921960846*mui*Power(Sin(3*Pi*t),2)*
    (Power(R,2)*(400.00000000000006 + 1.0000000000000002*Power(Z,2))*
       Power(Cos(3*Pi*Z),2)*Power(Sin(3*P),2)*Power(Sin(3*Pi*R),2) + 
      Power(R,2)*(500. - 20.000000000000004*R + 1.*Power(R,2))*
       Power(Cos(3*Pi*R),2)*Power(Sin(3*P),2)*Power(Sin(3*Pi*Z),2) + 
      10.13211836423378*Power(Cos(3*P),2)*Power(Sin(3*Pi*R),2)*
       Power(Sin(3*Pi*Z),2) - 2.026423672846756*R*Power(Cos(3*P),2)*
       Power(Sin(3*Pi*R),2)*Power(Sin(3*Pi*Z),2) + 
      0.1013211836423378*Power(R,2)*Power(Cos(3*P),2)*Power(Sin(3*Pi*R),2)*
       Power(Sin(3*Pi*Z),2) + 0.1013211836423378*Power(Z,2)*
       Power(Cos(3*P),2)*Power(Sin(3*Pi*R),2)*Power(Sin(3*Pi*Z),2) - 
      3.1830988618379075*R*Z*Sin(6*P)*Sin(6*Pi*R)*Power(Sin(3*Pi*Z),2) - 
      31.830988618379074*R*Sin(6*P)*Power(Sin(3*Pi*R),2)*Sin(6*Pi*Z) + 
      3.1830988618379075*Power(R,2)*Sin(6*P)*Power(Sin(3*Pi*R),2)*
       Sin(6*Pi*Z) - 5.*Power(R,2)*Z*Power(Sin(3*P),2)*Sin(6*Pi*R)*
       Sin(6*Pi*Z) + 0.5000000000000001*Power(R,3)*Z*Power(Sin(3*P),2)*
       Sin(6*Pi*R)*Sin(6*Pi*Z)))/
  Power(500. - 20.*R + 1.*Power(R,2) + 1.*Power(Z,2),2)
; }};
struct SGammaPhie{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return (-0.5*mui*taui*((1.8849555921538759*(-10 + R)*Z*Cos(3*Pi*Z)*Sin(3*P)*
         Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
       (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
      (3*Pi*(1 - (1.*Power(Z,2))/
            (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
         Cos(3*Pi*(-10 + R))*Sin(3*P)*Sin(3*Pi*t)*Sin(3*Pi*Z))/5. - 
      (12.*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
       (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
      R*((17.765287921960844*(-10 + R)*Z*Cos(3*Pi*(-10 + R))*Cos(3*Pi*Z)*
            Sin(3*P)*Sin(3*Pi*t))/
          (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
         (113.09733552923255*(-10 + R)*Cos(3*P)*Cos(3*Pi*Z)*
            Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
          (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
         (3.7699111843077517*Power(-10 + R,2)*Z*Cos(3*Pi*Z)*Sin(3*P)*
            Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
          Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) - 
         (3.7699111843077517*(-10 + R)*Power(Z,2)*Cos(3*Pi*(-10 + R))*
            Sin(3*P)*Sin(3*Pi*t)*Sin(3*Pi*Z))/
          Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
         (1.8849555921538759*(-10 + R)*Cos(3*Pi*(-10 + R))*Sin(3*P)*
            Sin(3*Pi*t)*Sin(3*Pi*Z))/
          (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
         (24.*(-10 + R)*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*
            Sin(3*Pi*Z))/
          (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) - 
         (9*Power(Pi,2)*(1 - (1.*Power(-10 + R,2))/
               (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(3*P)*
            Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.) + 
      R*((113.09733552923255*(-10 + R)*Cos(3*P)*Cos(3*Pi*Z)*
            Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
          (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
         (113.09733552923255*Z*Cos(3*P)*Cos(3*Pi*(-10 + R))*Sin(3*Pi*t)*
            Sin(3*Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
         (9*(Power(R,-2) - 400/
               (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*
            Sin(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.) + 
      R*((17.765287921960844*(-10 + R)*Z*Cos(3*Pi*(-10 + R))*Cos(3*Pi*Z)*
            Sin(3*P)*Sin(3*Pi*t))/
          (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
         (3.7699111843077517*Power(-10 + R,2)*Z*Cos(3*Pi*Z)*Sin(3*P)*
            Sin(3*Pi*(-10 + R))*Sin(3*Pi*t))/
          Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
         (1.8849555921538759*Z*Cos(3*Pi*Z)*Sin(3*P)*Sin(3*Pi*(-10 + R))*
            Sin(3*Pi*t))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
         (113.09733552923255*Z*Cos(3*P)*Cos(3*Pi*(-10 + R))*Sin(3*Pi*t)*
            Sin(3*Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
         (3.7699111843077517*(-10 + R)*Power(Z,2)*Cos(3*Pi*(-10 + R))*
            Sin(3*P)*Sin(3*Pi*t)*Sin(3*Pi*Z))/
          Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
         (24.*(-10 + R)*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*
            Sin(3*Pi*Z))/
          (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) + 
         (12.*Z*Cos(3*P)*Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/
          (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
         (9*Power(Pi,2)*(1 - (1.*Power(Z,2))/
               (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(3*P)*
            Sin(3*Pi*(-10 + R))*Sin(3*Pi*t)*Sin(3*Pi*Z))/5.)))/R
; }};
struct SGammaNi{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return 0. - (0.5*mui*taui*((1.5707963267948966*(-10 + R)*Z*Cos(Pi*Z)*Sin(P)*
          Sin(Pi*(-10 + R))*Sin(Pi*t))/
        (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
       1.5707963267948966*(1 - 
          (1.*Power(Z,2))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
        Cos(Pi*(-10 + R))*Sin(P)*Sin(Pi*t)*Sin(Pi*Z) - 
       (10.*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
        (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
       R*((4.934802200544679*(-10 + R)*Z*Cos(Pi*(-10 + R))*Cos(Pi*Z)*
             Sin(P)*Sin(Pi*t))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) \
+ (31.41592653589793*(-10 + R)*Cos(P)*Cos(Pi*Z)*Sin(Pi*(-10 + R))*
             Sin(Pi*t))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
          (3.141592653589793*Power(-10 + R,2)*Z*Cos(Pi*Z)*Sin(P)*
             Sin(Pi*(-10 + R))*Sin(Pi*t))/
           Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) - 
          (3.141592653589793*(-10 + R)*Power(Z,2)*Cos(Pi*(-10 + R))*
             Sin(P)*Sin(Pi*t)*Sin(Pi*Z))/
           Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
          (1.5707963267948966*(-10 + R)*Cos(Pi*(-10 + R))*Sin(P)*
             Sin(Pi*t)*Sin(Pi*Z))/
           (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
          (20.*(-10 + R)*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
           (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) - 
          4.934802200544679*(1 - 
             (1.*Power(-10 + R,2))/
              (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(P)*
           Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)) + 
       R*((31.41592653589793*(-10 + R)*Cos(P)*Cos(Pi*Z)*Sin(Pi*(-10 + R))*
             Sin(Pi*t))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
          (31.41592653589793*Z*Cos(P)*Cos(Pi*(-10 + R))*Sin(Pi*t)*
             Sin(Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
          0.5*(Power(R,-2) - 400/
              (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*
           Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z)) + 
       R*((4.934802200544679*(-10 + R)*Z*Cos(Pi*(-10 + R))*Cos(Pi*Z)*
             Sin(P)*Sin(Pi*t))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
          (3.141592653589793*Power(-10 + R,2)*Z*Cos(Pi*Z)*Sin(P)*
             Sin(Pi*(-10 + R))*Sin(Pi*t))/
           Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
          (1.5707963267948966*Z*Cos(Pi*Z)*Sin(P)*Sin(Pi*(-10 + R))*
             Sin(Pi*t))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
          (31.41592653589793*Z*Cos(P)*Cos(Pi*(-10 + R))*Sin(Pi*t)*
             Sin(Pi*Z))/(R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
          (3.141592653589793*(-10 + R)*Power(Z,2)*Cos(Pi*(-10 + R))*Sin(P)*
             Sin(Pi*t)*Sin(Pi*Z))/
           Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
          (20.*(-10 + R)*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
           (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) + 
          (10.*Z*Cos(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))/
           (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
          4.934802200544679*(1 - 
             (1.*Power(Z,2))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
           Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))))/R
; }};
struct SA{
    double mue,mui,taue,taui,eta,beta,nuperp,nuparallel;
    DG_DEVICE double operator()(double R, double Z, double P, double t)const{
    return -(beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
      (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/3. \
+ (beta*Sin(2*P)*Sin(2*Pi*(-10 + R))*Sin(2*Pi*t)*
     (1 + 0.5*Sin(P)*Sin(Pi*(-10 + R))*Sin(Pi*t)*Sin(Pi*Z))*Sin(2*Pi*Z))/
   (3.*Sqrt(-mue)) - ((3.141592653589793*beta*(-10 + R)*Z*Cos(4*Pi*Z)*
        Sin(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*t))/
      (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
     beta*Pi*(1 - (1.*Power(Z,2))/
         (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Cos(4*Pi*(-10 + R))*
      Sin(4*P)*Sin(4*Pi*t)*Sin(4*Pi*Z) - 
     (20.*beta*Z*Cos(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*t)*Sin(4*Pi*Z))/
      (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
     R*((39.47841760435743*beta*(-10 + R)*Z*Cos(4*Pi*(-10 + R))*
           Cos(4*Pi*Z)*Sin(4*P)*Sin(4*Pi*t))/
         (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) + 
        (251.32741228718345*beta*(-10 + R)*Cos(4*P)*Cos(4*Pi*Z)*
           Sin(4*Pi*(-10 + R))*Sin(4*Pi*t))/
         (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
        (6.283185307179586*beta*Power(-10 + R,2)*Z*Cos(4*Pi*Z)*Sin(4*P)*
           Sin(4*Pi*(-10 + R))*Sin(4*Pi*t))/
         Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) - 
        (6.283185307179586*beta*(-10 + R)*Power(Z,2)*Cos(4*Pi*(-10 + R))*
           Sin(4*P)*Sin(4*Pi*t)*Sin(4*Pi*Z))/
         Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
        (3.141592653589793*beta*(-10 + R)*Cos(4*Pi*(-10 + R))*Sin(4*P)*
           Sin(4*Pi*t)*Sin(4*Pi*Z))/
         (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
        (40.*beta*(-10 + R)*Z*Cos(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*t)*
           Sin(4*Pi*Z))/
         (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) - 
        4*beta*Power(Pi,2)*(1 - 
           (1.*Power(-10 + R,2))/
            (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*Sin(4*P)*
         Sin(4*Pi*(-10 + R))*Sin(4*Pi*t)*Sin(4*Pi*Z)) + 
     R*((251.32741228718345*beta*(-10 + R)*Cos(4*P)*Cos(4*Pi*Z)*
           Sin(4*Pi*(-10 + R))*Sin(4*Pi*t))/
         (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
        (251.32741228718345*beta*Z*Cos(4*P)*Cos(4*Pi*(-10 + R))*
           Sin(4*Pi*t)*Sin(4*Pi*Z))/
         (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
        4*beta*(Power(R,-2) - 400/
            (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))))*
         Sin(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*t)*Sin(4*Pi*Z)) + 
     R*((39.47841760435743*beta*(-10 + R)*Z*Cos(4*Pi*(-10 + R))*
           Cos(4*Pi*Z)*Sin(4*P)*Sin(4*Pi*t))/
         (400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
        (6.283185307179586*beta*Power(-10 + R,2)*Z*Cos(4*Pi*Z)*Sin(4*P)*
           Sin(4*Pi*(-10 + R))*Sin(4*Pi*t))/
         Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
        (3.141592653589793*beta*Z*Cos(4*Pi*Z)*Sin(4*P)*Sin(4*Pi*(-10 + R))*
           Sin(4*Pi*t))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)) - 
        (251.32741228718345*beta*Z*Cos(4*P)*Cos(4*Pi*(-10 + R))*
           Sin(4*Pi*t)*Sin(4*Pi*Z))/
         (R*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) + 
        (6.283185307179586*beta*(-10 + R)*Power(Z,2)*Cos(4*Pi*(-10 + R))*
           Sin(4*P)*Sin(4*Pi*t)*Sin(4*Pi*Z))/
         Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2) + 
        (40.*beta*(-10 + R)*Z*Cos(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*t)*
           Sin(4*Pi*Z))/
         (R*Power(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2),2)) + 
        (20.*beta*Z*Cos(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*t)*Sin(4*Pi*Z))/
         (Power(R,2)*(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2))) - 
        4*beta*Power(Pi,2)*(1 - 
           (1.*Power(Z,2))/(400 + 1.*Power(-10 + R,2) + 1.*Power(Z,2)))*
         Sin(4*P)*Sin(4*Pi*(-10 + R))*Sin(4*Pi*t)*Sin(4*Pi*Z)))/R
; }};
}}//namespace feltor namespace manufactured
