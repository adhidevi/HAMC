#ifndef __MSDIST_H
#define __MSDIST_H

/*
   -------------------------------------------------
   hamcMultScatt

   Multiple scattering distribution calculation
   class.

   Seamus Riordan
   sriordan@physics.umass.edu

   August 24, 2011
   -------------------------------------------------

   The general use of this class is to load up some
   materials and generate multiple scattering events
   or to calculate what the (non-normalized) theta 
   distribution is for a given material.

   All of this is based on Hans Bethe's paper over
   Molière scattering

   H. A. Bethe, Phys. Rev. 89, 1256 (1953)

   Units we use:

   momentum [GeV], thickness [g/cm2], angle [rad]

   For the former, one can set the particle and 
   materials in a few ways.  These take the following 
   arguments:

   p - electron momentum, [GeV]
   t - Thickness [g/cm2]
   A - Mass number
   Z - Atomic number

   1)  No materials at instantiation, later call
       Init for single or multiple materials
   2)  Single or multiple materials at instantiation

   Once these are set, one can call GenerateMS()
   to start getting a distribution equal to one given
   by all the combined materials.

   One can also call GenerateMS with the same
   arguments fed to Init.  This is slower  since it has 
   to calculate a bunch of parameters requiring
   integrals over the distribution.  Sometimes you can't
   avoid this necessity, such as if you are doing MS
   through parts of a long target.

   To access the numeric theta distributions, you can 
   call CalcMSDist with the angle and optionally the 
   material parameters as you would call GenerateMS.

   -------------------------------------------------
*/

#include "time.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#define MAT_MAX 50

class hamcMultScatt {

    public:
	hamcMultScatt();
	hamcMultScatt( double p, double t, double A, double Z );
	hamcMultScatt( double p, int nmat, double t[], double A[], double Z[] );

	void   Init( double p, double t, double A, double Z );
	void   Init( double p, int nmat, double t[], double A[], double Z[] );

	virtual ~hamcMultScatt() {;}

	double GetP(){ return fp; }

	double J0(double x);
	double CalcMSDistPlane( double theta);
	double CalcMSDistPlane( double theta, double p, int,  double t[], double A[], double Z[] );
	double CalcMSDistPlane( double theta, double p, double t, double A, double Z );

	double CalcMSDist( double theta);
	double CalcMSDist( double theta, double p, int,  double t[], double A[], double Z[] );
	double CalcMSDist( double theta, double p, double t, double A, double Z );

	double GenerateMS();
	double GenerateMS( double p, double t, double A, double Z );
	double GenerateMS( double p, int nmat, double t[], double A[], double Z[] );
	double GenerateMSPlane();
	double GenerateMSPlane( double p, double t, double A, double Z );
	double GenerateMSPlane( double p, int nmat, double t[], double A[], double Z[] );

	bool   IsInit(){ return fInit; }

    private:

	bool   fInit;
	double fErf2sig;

	int    fNmat;
	double fp;
	double ft[MAT_MAX];
	double fA[MAT_MAX];
	double fZ[MAT_MAX];

	double fth;
	double fthpdg;
	double fB;
	double fchi2;

	// exponential parameters
	double fl;
	double fC;
	double fDt;
	double ftailprob;

	double solvelogeq(double b);
	double fn_integrand( double u, double th, int n );
	double intsimpson_fn( double th, int n );

	void   InitInternal();
};

#endif//__MSDIST_H
