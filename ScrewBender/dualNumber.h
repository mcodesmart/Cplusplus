/******************************************************************
**dualnumber.h 
**
**Class defenition file for a dual number class and operations
**
**Based on sample code provided for homework 6
**
**April 26th, 2014
****************************************************************/

#ifndef DUALNUMBER_H
#define DUALNUMBER_H

class Dual
{
public:
	Dual() { real = 1.0f; dual = 0.0f; } //changed default value to 1.0 for real part and 0.0 for dual
	Dual( double re ) { real = re; dual = 0.0; };
	Dual( double re, double du ) { real = re; dual = du; }

	void   SetupDual( double, double );
	void   SetupDual( Dual& );
	void   SetReal( double r ) { real = r; }
	void   SetDual( double d ) { dual = d; }
	double GetReal() const { return real; }
	double GetDual() const { return dual; }

	friend Dual operator+( const Dual&, const Dual& );
	friend Dual operator+( const Dual&, double );
	friend Dual operator+( double, const Dual& );
	friend Dual operator-( const Dual&, const Dual& );
	friend Dual operator-( const Dual&, double );
	friend Dual operator-( double, const Dual& );
	friend Dual operator*( const Dual&, const Dual& );
	friend Dual operator*( double, const Dual& );
	friend Dual operator*( const Dual&, double );
	friend Dual operator/( const Dual&, const Dual& );
	friend Dual operator/( const Dual&, double );
	friend Dual operator/( double, const Dual& );
	Dual& operator=( Dual );
private:
	double real;
	double dual;

};

#endif
