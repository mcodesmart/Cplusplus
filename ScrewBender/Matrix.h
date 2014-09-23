/******************************************************************
** Matrix.h
**
** Class defenition file for an arbitrary matrix representation 
**
**Based on sample code provided for homework 6
**
** April 26th, 2014
****************************************************************/
#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	friend Matrix operator*( const Matrix&, const double );
	friend Matrix operator*( const double, const Matrix& );
	friend Matrix operator/( const Matrix&, const double );
public:
	Matrix();
	Matrix( int, int );
	Matrix( const Matrix& );
	~Matrix( );
	Matrix operator+( const Matrix& );
	Matrix operator-( const Matrix& );
	Matrix operator*( const Matrix& );
	void operator=( const Matrix& );
	void Clear(void);
	Matrix Inverse(void);
	Matrix Transpose(void);
	bool   MallocSpace(void);
	void   DeleteSpace(void);
	double getMatrixElement(int,int) const;
	virtual void   setMatrixElement(int,int,double);
public:
	int row;
	int column;
	double **m;
};


#endif //MATRIX_H