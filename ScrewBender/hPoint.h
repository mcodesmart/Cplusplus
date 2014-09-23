/******************************************************************
** hpoint.h
**
** Class defenition file for a homogeneous point representation of a 
** point or a plane
**
**Based on sample code provided for homework 6
**
** April 26th, 2014
****************************************************************/
#ifndef HPOINT_H
#define HPOINT_H

#include <iostream>
#include <fstream>
#include <vector>
class hMatrix;
class DualQuaternion;

using std::vector;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;

class hPoint
{
	friend ifstream &operator>>(ifstream &, hPoint &);
	friend istream &operator>>(istream &, hPoint &);
	friend ofstream &operator<<(ofstream &, const hPoint &);
	friend ostream &operator<<(ostream &, const hPoint &);
	friend hPoint operator*( const hMatrix&, const hPoint& );
	friend hPoint operator*( const hPoint&, double );
	friend hPoint operator*( double, const hPoint& );
	friend hPoint operator/( const hPoint&, double );
	friend double operator^( const hPoint&, const hPoint& );
public:
	hPoint();
	hPoint( double, double, double );
	hPoint( double, double, double, double );
	hPoint( double arg1[3]);
	hPoint& operator=( hPoint );
	hPoint operator+( const hPoint& );
	hPoint operator-( const hPoint& );
	hPoint operator*( const hPoint& );	//cross product
	void Clear();
	void PointNormalize();
	void PlaneNormalize();
	hPoint PointTransform( DualQuaternion Q );
	hPoint PlaneTransform( DualQuaternion Q );
	vector<double> getCoordPoint(void) const;

private: 
	vector<double> coord;
};

#define Vector hPoint
#define Plane  hPoint

#endif
