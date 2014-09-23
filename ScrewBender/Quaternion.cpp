#include <cmath>
#include <iostream>
#include <fstream>

#include "Quaternion.h"

using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;

const double PI = 3.1415926535897;

Quaternion::Quaternion()

{
	q[0]=q[1]=q[2]=q[3] = 0.0f;
}

Quaternion::Quaternion(const double re[4])
{
	for (int i=0; i<4; i++)
		q[i] = re[i];
}

Quaternion::Quaternion(vector<double> re)
{
	for (int i=0; i<4; i++)
		q[i] = re[i];
}

Quaternion::Quaternion(double re1, double re2, double re3, double re4)
{
	q[0] = re1;
	q[1] = re2;
	q[2] = re3;
	q[3] = re4;
}


 Quaternion Quaternion::operator+ (const Quaternion& Q) const
{
   Quaternion sum;
  for (int i=0; i<4; i++)
	  sum.q[i] = (this->q[i] + Q.q[i]);
   return sum;
}

  Quaternion Quaternion::operator- (const Quaternion& Q) const
{
   Quaternion diff;
  for (int i=0; i<4; i++)
	  diff.q[i] = (this->q[i] - Q.q[i]);
   return diff;
}

double Quaternion::Modulus()
{
double sum = 0.0;

	for (int i=0; i<4; i++)
		sum += q[i]*q[i];
	

	return sum;
}
	

Quaternion Quaternion::Conjugate()
{

	Quaternion conju(-q[0], -q[1], -q[2], q[3]);

return conju;
}


Quaternion Quaternion::Inverse()
{

	return Conjugate()/Modulus();
}

Quaternion operator/(Quaternion& arg1, double arg2)
{
Quaternion division;
	
	for (int i=0; i<4; i++)
	division.q[i] = arg1.q[i] / arg2;

return division;

}

vector<double> Quaternion::getQuaternionElement() const 
{
	vector<double> result;
	result.push_back(q[0]);
	result.push_back(q[1]);
	result.push_back(q[2]);
	result.push_back(q[3]);
	return result;
}



Quaternion operator*( Quaternion& arg1, Quaternion& arg2)
{
Quaternion product;

product.q[0] = arg1.q[3]*arg2.q[0] + arg2.q[3]*arg1.q[0] +
			   arg1.q[1]*arg2.q[2] - arg1.q[2]*arg2.q[1];

product.q[1] = arg1.q[3]*arg2.q[1] + arg2.q[3]*arg1.q[1] +
			   arg1.q[2]*arg2.q[0] - arg1.q[0]*arg2.q[2];

product.q[2] = arg1.q[3]*arg2.q[2] + arg2.q[3]*arg1.q[2] +
			   arg1.q[0]*arg2.q[1] - arg1.q[1]*arg2.q[0];

product.q[3] = arg1.q[3]*arg2.q[3] - 
				(arg1.q[0]*arg2.q[0] + arg1.q[1]*arg2.q[1] + arg1.q[2]*arg2.q[2]);

return product;
}

Quaternion operator*( double arg1, Quaternion& arg2)
{
Quaternion product;
	
	for (int i=0; i<4; i++)
	product.q[i] = arg1 * arg2.q[i];

return product;

}

Quaternion operator*(Quaternion& arg1, double arg2)
{
Quaternion product;
	
	for (int i=0; i<4; i++)
	product.q[i] = arg2 * arg1.q[i];

return product;

}

Quaternion& Quaternion::operator=(Quaternion arg1)
{
	for (int i=0; i<4; i++)
		q[i] = arg1.q[i];

return *this;
}

ifstream &operator>>(ifstream &input, Quaternion & arg)
{
	for (int i=0; i<4; i++)
		input>>arg.q[i];

	return input;

}
ofstream &operator<<(ofstream &output, const Quaternion & arg)		   
{
	output << "(" << arg.q[0] << ", " << arg.q[1] << ", " << arg.q[2] << ", " << arg.q[3] << ")" << endl; 
	return output;
}
			
istream &operator>>(istream &input, Quaternion & arg)
{
	for (int i=0; i<4; i++)
		input>>arg.q[i];

	return input;

}
ostream &operator<<(ostream &output, const Quaternion & arg)		   
{
	output << "(" << arg.q[0] << ", " << arg.q[1] << ", " << arg.q[2] << ", " << arg.q[3] << ")"; 
	return output;
}

Matrix Quaternion::quaternionToRotationMatrix()
{
    Matrix R(3,3);
	double k;
	k = q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
    R.setMatrixElement(0,0,((q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3])/k)) ;
	R.setMatrixElement(0,1,(2*(q[0]*q[1] - q[2]*q[3])/k));
	R.setMatrixElement(0,2,(2*(q[0]*q[2] + q[1]*q[3])/k));
	R.setMatrixElement(1,0,(2*(q[0]*q[1] + q[2]*q[3])/k));
	R.setMatrixElement(1,1,((- q[0]*q[0] + q[1]*q[1] - q[2]*q[2] + q[3]*q[3])/k));
	R.setMatrixElement(1,2,(2*(q[1]*q[2] - q[0]*q[3])/k));
	R.setMatrixElement(2,0,(2*(q[0]*q[2] - q[1]*q[3])/k));
	R.setMatrixElement(2,1,(2*(q[1]*q[2] + q[0]*q[3])/k));
	R.setMatrixElement(2,2,((- q[0]*q[0] - q[1]*q[1] + q[2]*q[2] + q[3]*q[3])/k));
	return (R);
}


Quaternion Quaternion::eulerToQuaternion(const hPoint& euler)
	{
	vector<double> angles = euler.getCoordPoint();
	double c1 = cos(angles[2] * PI / 180.0 * 0.5);
	double c2 = cos(angles[1]* PI / 180.0 * 0.5);
	double c3 = cos(angles[0]* PI / 180.0 * 0.5);
	double s1 = sin(angles[2]* PI / 180.0 * 0.5);
	double s2 = sin(angles[1]* PI / 180.0 * 0.5);
	double s3 = sin(angles[0]* PI / 180.0 * 0.5);

	Quaternion result;
	result.q[0] = c1*c2*s3 - s1*s2*c3;
	result.q[1] = c1*s2*c3 + s1*c2*s3;
	result.q[2] = s1*c2*c3 - c1*s2*s3;
	result.q[3] = c1*c2*c3 + s1*s2*s3;

	return result;
	};

hPoint Quaternion::getEuler()
	{
	  
      double roll	= (180 / PI)*(atan2(2.0*(q[1]*q[2] + q[3]*q[4]),1 - 2.0*(q[2]*q[2] + q[3]*q[3])));
	  double pitch	= (180 / PI)*(asin(2.0*(q[1]*q[3] - q[4]*q[2])));
	  double yaw	= (180 / PI)*(atan2(2.0*(q[1]*q[4] + q[2]*q[3]),1 - 2.0*(q[3]*q[3] + q[4]*q[4])));
	  return hPoint(roll,pitch,yaw);
    
}