#include <cmath>
#include <iomanip>


#include "hMatrix.h"
#include "hPoint.h"

hMatrix::hMatrix() : Matrix(4,4)
{
	for( int i = 0; i < row; i ++ )
		for( int j = 0; j < column; j ++ )
			m[i][j] = 0.0f;
}

ostream& operator<<(ostream& os, hMatrix& arg)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
			os<<fixed<<setprecision(4)<<arg.m[i][j]<<" ";
		os<<endl;
	}
	return os;
}

hMatrix& hMatrix::operator=( hMatrix arg1 )
{
	for( int i = 0; i < 4; i ++ )
		for( int j = 0; j < 4; j ++ )
			m[i][j] = arg1.m[i][j];

	return *this;
}

void hMatrix::Clear()
{
	for( int i = 0; i < 4; i ++ )
		for( int j = 0; j < 4; j ++ )
			m[i][j] = 0.0f;

	return;
}

hMatrix hMatrix::transpose( )
{
	int i, j;
	hMatrix temp;

	for (i=0; i<4; i++)
		for (j=0; j<4; j++)
			temp.m[i][j] = m[j][i];

	return temp;
		
}


hMatrix hMatrix::Inverse( )
{
	hMatrix arg1;
	int *is, *js, i, j, k, l, u, v;

	double d, p, a[16];

	for( i = 0; i < 4 ; i ++ )
		for( j = 0; j < 4; j ++ )
			a[i*4+j] = m[i][j];

	int n = 4;

	is = new int[n];
	js = new int[n];

	for( k = 0; k <= n-1; k ++ )
	{
		d = 0.0f;
		for( i = k; i <= n-1; i ++ )
			for( j = k; j <= n-1; j ++ )
			{
				l = i * n + j;
				p = fabs( a[l] );
				if( p > d )
				{
					d = p; 
					is[k] = i;
					js[k] = j;
				}
			}

		if( d + 1.0f == 1.0f )
		{
			delete is;
			delete js;
			arg1.Clear();
			return arg1;
		}

		if( is[k] != k )
			for( j = 0; j <= n -1; j ++ )
			{
				u = k * n + j;
				v = is[k] * n + j;
				p = a[u];
				a[u] = a[v];
				a[v] = p;
			}

		if( js[k] != k )
			for( i = 0; i <= n-1; i ++ )
			{
				u = i * n + k;
				v = i * n + js[k];
				p = a[u];
				a[u] = a[v];
				a[v] = p;
			}

		l = k * n + k;
		a[l] = 1.0f / a[l];

		for( j = 0; j <= n-1; j ++ )
			if( j != k )
			{
				u = k * n + j;
				a[u] = a[u] * a[l];
			}

		for( i = 0; i <= n-1; i ++ )
			if( i !=k )
				for( j = 0; j <= n-1; j ++ )
					if( j != k )
					{
						u = i * n + j;
						a[u] = a[u] - a[i*n+k] * a[k*n+j];
					}

		for( i = 0; i <= n-1; i ++ )
			if( i != k )
			{
				u = i * n + k;
				a[u] = -a[u] * a[l];
			}
	}

	for( k = n-1; k >= 0; k -- )
	{
		if( js[k] != k )
			for( j = 0; j <= n-1; j ++ )
			{
				u = k * n + j;
				v = js[k] * n + j;
				p = a[u];
				a[u] = a[v];
				a[v] = p;
			}

		if( is[k] != k )
			for( i = 0; i <= n-1; i ++ )
			{
				u = i * n + k;
				v = i * n + is[k];
				p = a[u];
				a[u] = a[v];
				a[v] = p;
			}
	}

	for( i = 0; i < 4; i ++ )
		for( j = 0; j < 4; j ++ )
			arg1.m[i][j] = a[i*4+j];
		
	delete is;
	delete js;

	return arg1;
}
