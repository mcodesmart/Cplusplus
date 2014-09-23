/******************************************************************
** Point3D.h
**
** Class defenition file for a 3D Point Class
**
**Based on sample code provided for homework 6
**
** April 26th, 2014
****************************************************************/

#ifndef POINT3D_H
#define POINT3D_H

class Point3D
{
	friend Point3D operator*( const hMatrix&, const Point3D& ); // hMatrix is homogeneous matrix
	friend Point3D operator*( const Point3D&, double );
	friend Point3D operator*( double, const Point3D& );
	friend Point3D operator/( const Point3D&, double );
public:
	Point3D() { for( int i = 0; i < 3; i ++ )	coord[i] = 0.0f; }
	Point3D( double x, double y, double z )	{ coord[0] = x; coord[1] = y; coord[2] = z; }
	Point3D& operator=( Point3D );
	Point3D operator+( const Point3D&);
	Point3D operator-( const Point3D&);
	void Normalize( );
private:
	double	coord[3];
	double	normal[3];
	bool	visible;
};

#endif //POINT3D_H
