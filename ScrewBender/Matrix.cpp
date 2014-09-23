/******************************************************************
** Matrix.cpp
**
** Class implementation file for a matrix representation 
**
** April 26th, 2014
****************************************************************/

#include "Matrix.h"
#include <cmath>

//default constructor
Matrix::Matrix()
{
	row = 0;
	column = 0;
	m = 0;
}

Matrix::Matrix( int a, int b )
{
	row = a;
	column = b;
	m = new double*[a];
	for( int i = 0; i < a; i ++ )	m[i] = new double[b];
}

Matrix::Matrix( const Matrix& mm )
{
	row = mm.row;
	column = mm.column;

	m = new double*[row];
	for( int i = 0; i < row; i ++ )	m[i] = new double[column];

	for(int i = 0; i < row; i ++ )
		for( int j = 0; j < column; j ++ )
			m[i][j] = mm.m[i][j];
}

Matrix::~Matrix( )
{
	if( m != 0 )
	{
		for( int i = 0; i < row; i ++ )
			delete[] m[i];

		delete[] m;
	}
}

Matrix Matrix::operator+( const Matrix& arg )
{
	Matrix sum(this->row, this->column);

	if( this->row != arg.row || this->column != arg.column )	return sum;

	for( int i = 0; i < this->row; i ++ )
		for( int j = 0; j < this->column; j ++ )
			sum.m[i][j] = this->m[i][j] + arg.m[i][j];

	return sum;
}

Matrix Matrix::operator-( const Matrix& arg )
{
	Matrix sum(this->row, this->column);

	if( this->row != arg.row || this->column != arg.column )	return sum;

	for( int i = 0; i < this->row; i ++ )
		for( int j = 0; j < this->column; j ++ )
			sum.m[i][j] = this->m[i][j] - arg.m[i][j];

	return sum;
}



void Matrix::operator=( const Matrix& arg1 )
{
	DeleteSpace( );
	row = arg1.row;
	column = arg1.column;
	MallocSpace( );

	for( int i = 0; i < row; i ++ )
		for( int j = 0; j < column; j ++ )
			m[i][j] = arg1.m[i][j];

	return;
}

Matrix Matrix::Inverse( )
{
	Matrix inv(row, column);

	if( row != column )	return inv;

	int *is, *js, i, j, k, l, u, v, n;
	double d, p, *a;

	n = row;

	a = new double[n*n];

	for( i = 0; i < n ; i ++ )
		for( j = 0; j < n; j ++ )
			a[i*n+j] = m[i][j];

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
			delete[] is;
			delete[] js;

			return inv;
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

	for( i = 0; i < n; i ++ )
		for( j = 0; j < n; j ++ )
			inv.m[i][j] = a[i*n+j];
		
	delete[] is;
	delete[] js;
	delete[] a;

	return inv;
}

Matrix Matrix::Transpose(  )
{	
	Matrix arg1(column, row);

	for( int i = 0; i < row; i ++ )
		for( int j = 0; j < column; j ++ )
			arg1.m[j][i] = m[i][j];

	return arg1;
}

void Matrix::Clear( )
{
	for( int i = 0; i < row; i ++ )
		for( int j = 0; j < column; j ++ )
			m[i][j] = 0.0;

	return;
}

bool Matrix::MallocSpace( )
{
	if( row <=0 || column <= 0 )
		return false;

	m = new double*[row];
	for( int i = 0; i < row; i ++ )
		m[i] = new double[column];

	return true;
}

void Matrix::DeleteSpace( )
{
	if( m!= 0 )
	{
		for( int i = 0; i < row; i ++ )
			delete[] m[i];
		delete[] m;

		row = 0;
		column = 0;

		m = 0;
	}

	return;
}

double Matrix::getMatrixElement(int i,int j) const
	{
		return m[i][j];
	}


void Matrix::setMatrixElement( int i, int j, double value)
	{
		m[i][j] = value;
	}


//Non-Member Functions
Matrix Matrix::operator*( const Matrix& arg )
{
	Matrix mul(this->row, this->column);

	if( this->column != arg.row )	return mul;

	mul.Clear();

	for( int i = 0; i < this->row; i ++ )
		for( int j = 0; j < arg.column; j ++ )
			for( int k = 0; k < this->column; k ++ )		
				mul.m[i][j] += this->m[i][k] * arg.m[k][j];

	return mul;
}

Matrix operator*( const Matrix& arg1, const double arg2 )
{
	Matrix sum(arg1.row, arg1.column);

	for( int i = 0; i < arg1.row; i ++ )
		for( int j = 0; j < arg1.column; j ++ )
			sum.m[i][j] = arg1.m[i][j] * arg2;

	return sum;
}

Matrix operator*( const double arg1, const Matrix& arg2 )
{
	Matrix sum( arg2.row, arg2.column );

	for( int i = 0; i < arg2.row; i ++ )
		for( int j = 0; j < arg2.column; j ++ )
			sum.m[i][j] = arg1 * arg2.m[i][j];

	return sum;
}

Matrix operator/( const Matrix& arg1, const double arg2 )
{
	Matrix sum(arg1.row, arg1.column);

	for( int i = 0; i < arg1.row; i ++ )
		for( int j = 0; j < arg1.column; j ++ )
			sum.m[i][j] = arg1.m[i][j] / arg2;

	return sum;
}
