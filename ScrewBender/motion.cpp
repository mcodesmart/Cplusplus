/******************************************************************
**motion.cpp 
**
**Class Implementation file for all operations for a motion class
**
** Motion is a virtual class abstract motion
**
**April 26th, 2014
****************************************************************/

#include <QFile>
#include <QDebug>
#include <vector>
#include <GL/glut.h>
#include <gl/glu.h>

#include "motion.h"
#include "Quaternion.h"
#include "hMatrix.h"
#include "hPoint.h"


using namespace std;

void Motion::readCtrlPositions(QString fileNameArg)
{
QFile inFile(fileNameArg);
if (fileNameArg != "") {
		if (!inFile.open(QIODevice::ReadOnly|QIODevice::Text))
		{
		exit(1);
		return;
		}
	}
	qDebug() << "File Opened";
	QString line;
	QTextStream  stream(&inFile);
	stream>>numberOfPoses;
	qDebug() << numberOfPoses;
	int i;
	Quaternion *RotationQuaternion =  new Quaternion[numberOfPoses];
	Vector *TranslationVector = new Vector[numberOfPoses];
	double d[4];
	for(i=0; i<numberOfPoses; i++)
		{
		stream >>d[0]>>d[1]>>d[2]>>d[3];
		qDebug() << d[0]<<d[1]<<d[2]<<d[3];
		RotationQuaternion[i] = Quaternion(d);
		}
    	
  for(i=0; i<numberOfPoses; i++)
	  	{
		stream >>d[0]>>d[1]>>d[2]>>d[3];
		qDebug() << d[0]<<d[1]<<d[2]<<d[3];
		TranslationVector[i] = Vector(d);
		 }
  vector<double> t;
 for(i=0; i<numberOfPoses; i++)
		{
	     DualQuaternion dQ(RotationQuaternion[i], TranslationVector[i]);
		 ctrlPos.push_back(dQ);
		 t = ctrlPos[i].getDualQuaternionElements();
	 	 qDebug()<<t[0]<<t[1]<<t[2]<<t[3]<<t[4]<<t[5]<<t[6]<<t[7]<<endl;
		 }
    delete[] RotationQuaternion;
    delete[] TranslationVector;
	inFile.close();
    }


//work on this last
void Motion::writeCtrlPositions(QString fileNameArg)
{
	QFile outFile(fileNameArg);
	  if( !fileNameArg.isNull() )
    {
	//	exit(1);
       qDebug(fileNameArg.toAscii() );
    }
	outFile.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream  stream(&outFile);
	stream << numberOfPoses << endl;
	
	for(int i=0; i<numberOfPoses; i++)
		{
		vector<double> dd= ctrlPos[i].getDualQuaternionElements();
		stream <<dd[0]<<","<<dd[1]<<","<<dd[2]<<","<<dd[3]<<endl;
		stream <<dd[4]<<","<<dd[5]<<","<<dd[6]<<","<<dd[7]<<endl;
		}
	outFile.close();
}

void Motion::clear()
	{
	numberOfPoses = 0;
	ctrlPos.clear();
	}

void Motion::deleteLastControlPose(void)
	{
	numberOfPoses = numberOfPoses - 1;
	ctrlPos.pop_back();
	};

void Motion::drawControlPoses(void)
{
	//qDebug()<<"called"<<numberOfPoses;
	vector <hMatrix> homogeneousMatricesForCtrlPositions;
		for (int i=0; i<numberOfPoses; i++)
	{
		homogeneousMatricesForCtrlPositions.push_back(ctrlPos[i].dualQuaternionToHomogeneousMatrix().transpose());
		double MatrixforOpenGLStack[16];

		for (int i1=0; i1<4; i1++)
			for (int i2=0; i2<4; i2++)
				MatrixforOpenGLStack[4*i1+i2] =  homogeneousMatricesForCtrlPositions.at(i).m[i1][i2];
		float RED[3] = { 1.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT,GL_DIFFUSE, RED);
		glPushMatrix();
		glMultMatrixd(MatrixforOpenGLStack);
		glutSolidTeapot(0.15);
		glPopMatrix();

	}

		//debugger 
     /*double MOpenGLStack[16] = {0.4314, 0.875, 0.2181, 0.000,0.0567, -0.267, 0.961, 0.000,
								0.900, -0.402, -0.165, 0.000,-2.700, 2.0000, 0.000, 1.000};
	 glPushMatrix();
	 glMultMatrixd(MOpenGLStack);
	 glutSolidTeapot(0.15);
	 glPopMatrix();*/


}


DualQuaternion Motion::split(DualQuaternion& dQ1,DualQuaternion& dQ2)
	{
		return (dQ1 + dQ2)/2;
	}; 


Motion::~Motion()
{
	
}