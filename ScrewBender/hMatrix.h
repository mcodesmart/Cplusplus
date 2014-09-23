/******************************************************************
** hMatrix.h
**
** Class definition file for a homogeneous matrix representation
**
**Based on sample code provided for homework 6
**
** April 26th, 2014
****************************************************************/

#ifndef HMATRIX_H
#define HMATRIX_H

#include <iostream>
#include "Matrix.h"

using namespace std;

class hPoint;
class Point;

// 4*4 homogeneous matrix
class hMatrix : public Matrix
{
	friend ostream &operator<<(ostream&, hMatrix&);
	friend hPoint operator*( const hMatrix&, const hPoint& ); 
	friend Point  operator*( const hMatrix&, const Point& );
public:
	hMatrix();
	hMatrix& operator=( hMatrix ); 
	void Clear();
	hMatrix Inverse( );		// return the inverse of a 4*4 matrix
	hMatrix transpose();
};

#endif //_HMARTRIX