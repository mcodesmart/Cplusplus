/******************************************************************
**	Point3D.cpp
**
**	Implementation file for a 3D Point Class
**
**	April 26th, 2014
****************************************************************/
#include <cmath>
#include "hPoint.h"
#include "Point3D.h"
#include "hMatrix.h"


Point3D& Point3D::operator=( Point3D arg1 )
{
	for( int i=0; i < 3; i ++ )
		coord[i] = arg1.coord[i];

	for( int i = 0; i < 3; i ++ )
		normal[i] = arg1.normal[i];

	visible = arg1.visible;
		
	return *this;
}

Point3D Point3D::operator+(const Point3D& arg1)
{
	Point3D	result;

	for(int i = 0; i < 3; i ++ )
		result.coord[i] = this->coord[i] + arg1.coord[i];
	return result;
}

Point3D Point3D::operator-( const Point3D& arg1)
{
	Point3D result;
	for (int i = 0; i < 3; i ++)
		result.coord[i] = this->coord[i] - arg1.coord[i];
	return result;
}

Point3D operator*(const hMatrix& arg1, const Point3D& arg2)
{
	hPoint	mul, temp;
	Point3D	res;

	for( int i = 0; i < 3; i ++ )	temp.getCoordPoint()[i] = arg2.coord[i];
	temp.getCoordPoint()[3] = 1.0f;

	mul = arg1 * temp;

	for(int i = 0; i < 3; i ++ )	res.coord[i] = mul.getCoordPoint()[i] / mul.getCoordPoint()[3];

	return res;
}

Point3D operator*(const Point3D& arg1, double arg2)
{
	Point3D	res;

	for(int i = 0; i < 3; i ++ )	res.coord[i] = arg1.coord[i] * arg2;

	return res;
}

Point3D operator*( double arg1, const Point3D& arg2 )
{
	Point3D	res;

	for( int i = 0; i < 3; i ++ )	res.coord[i] = arg1 * arg2.coord[i];

	return res;
}

Point3D operator/(const Point3D& arg1, double arg2 )
{
	Point3D	res;

	for( int i = 0; i < 3; i ++ )	res.coord[i] = arg1.coord[i] / arg2;

	return res;
}


void Point3D::Normalize( )
{
	double sum = sqrt( normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2] );
	for( int i = 0; i < 3; i ++ )	normal[i] /= sum;
	return;
}

