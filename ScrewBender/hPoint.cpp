#include <cmath>
#include <iostream>
#include <fstream>

#include "hPoint.h"
#include "Point3D.h"
#include "hMatrix.h"
#include "dualQuaternion.h"


hPoint::hPoint() 		
	{
	for( int i=0; i < 3; i ++ )  coord.push_back(0.0f); 
	coord.push_back(1.0f);
	}

hPoint::hPoint(double arg1, double arg2, double arg3 ) 	
	{ 
	coord.push_back(arg1); 
	coord.push_back(arg2); 
	coord.push_back(arg3); 
	coord.push_back(1.0f); 
	}

hPoint::hPoint(double arg1, double arg2, double arg3, double arg4 )	
	{ 
	coord.push_back(arg1); 
	coord.push_back(arg2); 
	coord.push_back(arg3); 
	coord.push_back(arg4); 
	}

hPoint::hPoint(double arg1[3] )	
	{
	coord.push_back(arg1[0]); 
	coord.push_back(arg1[1]); 
	coord.push_back(arg1[2]); 
	coord.push_back(1.0f); 
	}

hPoint& hPoint::operator=( hPoint arg1 )
	{
	for( int i = 0; i < 4; i ++ )
		coord[i] = arg1.coord[i];

	return *this;
	}

hPoint hPoint::operator*( const hPoint& h )
	{
	hPoint product;
	product.coord[0] = this->coord[1]*h.coord[2] - this->coord[2]*h.coord[1];
	product.coord[1] = this->coord[2]*h.coord[0] - this->coord[0]*h.coord[2];
	product.coord[2] = this->coord[0]*h.coord[1] - this->coord[1]*h.coord[0];
	product.coord[3] = 0.0f;
	return product;
	}

hPoint hPoint::operator+( const hPoint& arg)
	{
	hPoint sum;
	for( int i = 0; i < 4; i ++ )
		sum.coord[i] = this->coord[i] + arg.coord[i];	
	return sum;
	}

hPoint hPoint::operator-( const hPoint& arg )
	{
	hPoint diff;
	for( int i = 0; i < 4; i ++ )
		diff.coord[i] = this->coord[i] - arg.coord[i];
	return diff;
	}

vector<double> hPoint::getCoordPoint(void) const 
	{
	return coord;
	}

void hPoint::Clear()
	{
	for( int i = 0; i < 4; i ++ )	coord[i] = 0.0;

	return;
	}

void hPoint::PointNormalize()
	{
	for( int i = 0; i < 4; i ++ )	coord[i] = coord[i]/coord[3];

	return;
	}



hPoint hPoint::PointTransform( DualQuaternion Q )
	{
	DualQuaternion QQ, QR;
	hPoint hp = *this;

	for( int i = 0; i < 4; i ++ )
		{
		QQ.dual[i].SetupDual( Q.dual[i].GetReal(), 0 );
		QR.dual[i].SetupDual( Q.dual[i].GetDual(), 0 );
		}

	DualQuaternion qq = QQ*hp*QQ.Conjugate( )+QR*QQ.Conjugate()-QQ*QR.Conjugate();

	hPoint hpp(qq.dual[0].GetReal(), qq.dual[1].GetReal(), qq.dual[2].GetReal(), qq.dual[3].GetReal() );
	hpp.PointNormalize( );

	return hpp;
	}

Plane hPoint::PlaneTransform( DualQuaternion Q )
	{
	DualQuaternion QQ, QR;
	Plane hp = *this;

	for( int i = 0; i < 4; i ++ )
		{
		QQ.dual[i].SetupDual( Q.dual[i].GetReal(), 0 );
		QR.dual[i].SetupDual( Q.dual[i].GetDual(), 0 );
		}

	Vector M( hp.coord[0], hp.coord[1], hp.coord[2], 0 );

	DualQuaternion qq = QQ*hp*QQ.Conjugate( )+QR*M*QQ.Conjugate()-QQ*M*QR.Conjugate();

	hPoint hpp(qq.dual[0].GetReal(), qq.dual[1].GetReal(), qq.dual[2].GetReal(), qq.dual[3].GetReal() );
	hpp.PlaneNormalize( );

	return hpp;
	}

void hPoint::PlaneNormalize( )
	{
	double temp = 0;

	for( int i = 0; i < 3; i ++ )
		temp += coord[i]*coord[i];

	temp = sqrt( temp );

	for( int i = 0; i <= 3; i ++ )
		coord[i] /= temp;

	return;
	}
//Non Member Functions
hPoint operator*( const hMatrix& arg1, const hPoint& arg2 )
	{
	hPoint mul;

	mul.Clear();

	for( int i = 0; i < 4; i ++ )
		for( int j = 0; j < 4; j ++ )
			mul.coord[i] += arg1.m[i][j] * arg2.coord[j];

	return mul;
	}

hPoint operator*( const hPoint& arg1, double arg2 )
	{
	hPoint mul;

	for( int i = 0; i < 4; i ++ )
		mul.coord[i] = arg1.coord[i] * arg2;

	return mul;
	}

hPoint operator*( double arg1, const hPoint& arg2 )
	{
	hPoint mul;

	for( int i = 0; i < 4; i ++ )
		mul.coord[i] = arg2.coord[i] * arg1;

	return mul;
	}



hPoint operator/( const hPoint& arg1, double arg2 )
	{
	hPoint mul;

	for( int i = 0; i < 4; i ++ )
		mul.coord[i] = arg1.coord[i] / arg2;

	return mul;
	}


double operator^( const hPoint& arg1, const hPoint& arg2 )
	{
	double res = 0.0;

	for( int i = 0; i < 4; i ++ )
		res = res + arg1.coord[i] * arg2.coord[i];

	return res;
	}

ifstream &operator>>(ifstream &input, hPoint & arg)
	{
	for (int i=0; i<4; i++)
		input>>arg.coord[i];
	return input;

	}
ofstream &operator<<(ofstream &output, const hPoint & arg)		   
	{
	output << "(" << arg.coord[0] << ", " << arg.coord[1] << ", " << arg.coord[2] << ", " << arg.coord[3] << ")" << endl; 
	return output;
	}

istream &operator>>(istream &input, hPoint & arg)
	{
	for (int i=0; i<4; i++)
		input>>arg.coord[i];
	return input;

	}
ostream &operator<<(ostream &output, const hPoint & arg)		   
	{
	output << "(" << arg.coord[0] << ", " << arg.coord[1] << ", " << arg.coord[2] << ", " << arg.coord[3] << ")"; 
	return output;
	}