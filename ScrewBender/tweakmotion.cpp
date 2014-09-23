/******************************************************************
** tweak motion.cpp
**
** Class implementation file for tweak motion class using subdivision
**
** April 26th, 2014
****************************************************************/
#include <iostream>
#include <vector>
#include <QDebug>

#include "motion.h"
#include "tweakmotion.h"
#include "Quaternion.h"
#include "hMatrix.h"
#include "hPoint.h"
#include <GL\glut.h>

using namespace std;

TweakMotion::TweakMotion()
{
};

void TweakMotion::readPts()	{
for (int k = 0; k < ctrlPos.size(); k++){
	ctrldQ[k] = ctrlPos[k];
	}
	numVertices = ctrlPos.size();
	};

void TweakMotion::createMidPoints(){
	for (int k = 1; k < numVertices; k++ ){
	mdQ[k-1] = split(ctrldQ[k],ctrldQ[k-1]);
		}
	mdQ[numVertices-1] = split(ctrldQ[numVertices-1],ctrldQ[0]);
	}; 


void  TweakMotion:: createbSplinePrimes(){
	for (int k = 0; k < numVertices-1; k++ ){
		pdQ[k]=  split(ctrldQ[k+1], split(mdQ[k],mdQ[k+1]));}
		pdQ[numVertices-1]=  split(ctrldQ[0], split(mdQ[0],mdQ[numVertices-1]));
	};


void  TweakMotion::createFourPointPrimes(){
		pdQ[0] = mdQ[0] + ((mdQ[0]- split(mdQ[1],mdQ[numVertices-1]))/4);
		for (int k = 1; k < numVertices-1; k++)	{
		pdQ[k] = mdQ[k] + ((mdQ[k]- split(mdQ[k-1],mdQ[k+1]))/4);}
		pdQ[numVertices-1] = mdQ[numVertices-1] + ((mdQ[numVertices-1]- split(mdQ[0],mdQ[numVertices-2]))/4);	
	}; 

void  TweakMotion::createJarekPrimes(){
	//control points
		ctrldQ[0] = ctrldQ[0] - (ctrldQ[0]- split(mdQ[0],mdQ[numVertices-1]))/4;
		for (int k = 1; k < numVertices-1; k++ ){
		ctrldQ[k] = ctrldQ[k] - (ctrldQ[k]- split(mdQ[k-1],mdQ[k]))/4;}
		ctrldQ[numVertices-1] = ctrldQ[numVertices-1] - (ctrldQ[numVertices-1]- split(mdQ[numVertices-2],mdQ[numVertices-1]))/4;	
	//control primes
		pdQ[0] = mdQ[0] + (mdQ[0]- split(mdQ[1],mdQ[numVertices-1]))/8;
		for (int k = 1; k < numVertices-1; k++ ){
		pdQ[k] = mdQ[k] + (mdQ[k]- split(mdQ[k-1],mdQ[k+1]))/8;}
		pdQ[numVertices-1] = mdQ[numVertices-1] + (mdQ[numVertices-1]- split(mdQ[0],mdQ[numVertices-2]))/8;	
	};

void TweakMotion::updateBSplineTweaks(){
	DualQuaternion Q;
	bSplineTweaks.clear();
	for (int k = 0; k < numVertices; k++ ){
		Q = mdQ[k];	bSplineTweaks.push_back(Q);
		Q = pdQ[k];	bSplineTweaks.push_back(Q);}
	numVertices = bSplineTweaks.size();
	for (int i = 0; i < numVertices; i++)	ctrldQ[i] = bSplineTweaks[i];
		};

void TweakMotion::updateFourPointTweaks(){
	DualQuaternion Q;
	fourPointTweaks.clear();
	for (int k = 0; k < numVertices; k++ ) {
		Q = ctrldQ[k];	fourPointTweaks.push_back(Q);
		Q = pdQ[k];	fourPointTweaks.push_back(Q);}
	numVertices= fourPointTweaks.size();
	for (int i = 0; i < numVertices; i++) ctrldQ[i] = fourPointTweaks[i];
	};

void TweakMotion::updateJareksTweaks(){
	DualQuaternion Q;
	jareksTweaks.clear();
	for (int k = 0; k < numVertices; k++ ){
		Q = ctrldQ[k];	jareksTweaks.push_back(Q);
		Q = pdQ[k];	jareksTweaks.push_back(Q);}
	numVertices= jareksTweaks.size();
	for (int i = 0; i < numVertices; i++ )	ctrldQ[i] = jareksTweaks[i] ;
	};


	void TweakMotion::iterateSteps(int ItrNum, MotionType mType) {
		switch(mType)
			{
			case BSPLINE:
			for (int i = 0; i < ItrNum; i++ )
				{
				createMidPoints();
				createbSplinePrimes();
				updateBSplineTweaks();
				}
			break;
			case FOURPOINT:
			for (int i = 0; i < ItrNum; i++ )
				{
				createMidPoints();
				createFourPointPrimes();
				updateFourPointTweaks();
				}
			break;
			case JAREKS:
			for (int i = 0; i < ItrNum; i++ )
				{
				createMidPoints();
				createJarekPrimes();
				updateJareksTweaks();
				}
			break;
			default:
			break;
			}
		};


//create Bspline Polygon
	void TweakMotion::drawbSpline(void) {
		 qDebug()<<"called drawbspline"<<numVertices;
		 TweakMotion::readPts(); 								//draw splines by iteration
		 TweakMotion::iterateSteps(numIterations, BSPLINE);
		vector <hMatrix> homogeneousMatricesForCtrlPositions;
	for (int i=0; i<bSplineTweaks.size(); i++)
	{
		homogeneousMatricesForCtrlPositions.push_back(bSplineTweaks[i].dualQuaternionToHomogeneousMatrix().transpose());
		double MatrixforOpenGLStack[16];

		for (int i1=0; i1<4; i1++)
			for (int i2=0; i2<4; i2++)
				MatrixforOpenGLStack[4*i1+i2] =  homogeneousMatricesForCtrlPositions.at(i).m[i1][i2];
		const float BROWN[3] = {0.7f, 0.5f, 0.2f };
		glMaterialfv(GL_FRONT,GL_DIFFUSE, BROWN);	
		glPushMatrix();
		glMultMatrixd(MatrixforOpenGLStack);
		glutSolidTeapot(0.15);
		glPopMatrix();
	}
}	

//create Four Point Polygon
	void TweakMotion::drawFourPoint(void) {
		TweakMotion::readPts();						//draw splines by iteration
		TweakMotion::iterateSteps(numIterations, FOURPOINT);
		vector <hMatrix> homogeneousMatricesForCtrlPositions;
	for (int i=0; i<fourPointTweaks.size(); i++)
	{
		homogeneousMatricesForCtrlPositions.push_back(fourPointTweaks[i].dualQuaternionToHomogeneousMatrix().transpose());
		double MatrixforOpenGLStack[16];

		for (int i1=0; i1<4; i1++)
			for (int i2=0; i2<4; i2++)
				MatrixforOpenGLStack[4*i1+i2] =  homogeneousMatricesForCtrlPositions.at(i).getMatrixElement(i1,i2);
		float GREEN[3] = { 0.0f, 1.0f, 0.0f };
		glMaterialfv(GL_FRONT,GL_DIFFUSE, GREEN);	
		glPushMatrix();
		glMultMatrixd(MatrixforOpenGLStack);
		glutSolidTeapot(0.15);
		glPopMatrix();
	}
	
		}	

//create Jareks Polygon
	void TweakMotion::drawJarek(void) {
		TweakMotion::readPts();
		TweakMotion::iterateSteps(numIterations, JAREKS);
		vector <hMatrix> homogeneousMatricesForCtrlPositions;
	for (int i=0; i<jareksTweaks.size(); i++)
	{
		homogeneousMatricesForCtrlPositions.push_back(jareksTweaks[i].dualQuaternionToHomogeneousMatrix().transpose());
		double MatrixforOpenGLStack[16];

		for (int i1=0; i1<4; i1++)
			for (int i2=0; i2<4; i2++)
					MatrixforOpenGLStack[4*i1+i2] =  homogeneousMatricesForCtrlPositions.at(i).m[i1][i2];
		float CYAN[3] = { 0.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT,GL_DIFFUSE,CYAN);
		glPushMatrix();
		glMultMatrixd(MatrixforOpenGLStack);
		glutSolidTeapot(0.15);
		glPopMatrix();
	}
	
		}	

	

TweakMotion::~TweakMotion(){
	}
