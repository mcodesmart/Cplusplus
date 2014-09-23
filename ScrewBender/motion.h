/******************************************************************
**motion.h 
**
**Class definition file for all operations for a motion class
**
**April 26th, 2014
****************************************************************/
#ifndef MOTION_H
#define MOTION_H

#include "DualQuaternion.h"

class Motion
{
	friend class Mainwindow;
public:
	~Motion();
	void readCtrlPositions(QString);
	void writeCtrlPositions(QString);
	void drawControlPoses(void);
	void deleteLastControlPose(void);
	void clear();
	DualQuaternion split(DualQuaternion&,DualQuaternion&); 

	//accessor and getters
	int getNumberOfPoses(void) const {return numberOfPoses;}
	void setNumberOfPoses(int value){numberOfPoses = value;}
	int getNumIterations(void) const {return numIterations;}
	void setNumIterations(int value){numIterations = value;}

public:
	vector<DualQuaternion> ctrlPos;
	int numberOfPoses;
	int numIterations;
};

#endif
