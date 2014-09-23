/******************************************************************
**Quaternion.h
**
**Class defenition file for a quaternion class
**
**Based on sample code provided for homework 6
**
**April 26th, 2014
****************************************************************/
#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.h"
#include "hMatrix.h"
#include "hPoint.h"

class Quaternion
{
	friend ifstream &operator>>(ifstream &, Quaternion &);
	friend istream &operator>>(istream &, Quaternion &);
	friend ofstream &operator<<(ofstream &, const Quaternion &);
	friend ostream &operator<<(ostream &, const Quaternion &);
	friend Quaternion operator*(Quaternion&, Quaternion&);
	friend Quaternion operator*(Quaternion&, double);
	friend Quaternion operator*(double, Quaternion&);
	friend Quaternion operator/(Quaternion&, double);
	
public:
	Quaternion(const double re[4]);
	Quaternion(vector<double>);
	Quaternion(double,double,double,double);
	Quaternion();
	Quaternion operator+ (const Quaternion&) const;
	Quaternion operator- (const Quaternion&) const;	
	Quaternion& operator=(Quaternion);
	Matrix quaternionToRotationMatrix();
	double Modulus();
	Quaternion Conjugate();
	Quaternion Inverse();
	vector<double> getQuaternionElement() const;
	Quaternion eulerToQuaternion(const hPoint&);
	hPoint getEuler();

private:
	double q[4];

};

#endif //QUATERNION_H