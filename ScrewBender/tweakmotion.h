/******************************************************************
** tweak motion.h
**
** Class definition file for tweak motion class using subdivision
**

**
** April 26th, 2014
****************************************************************/

#ifndef TWEAK_MOTION_H
#define TWEAK_MOTION_H

#include <vector>
#include "DualQuaternion.h"
#include "Motion.h"

using namespace std;

class TweakMotion : public Motion //extends motion class which has read and write functionality
	{
public:
	enum MotionType {BSPLINE, FOURPOINT, JAREKS};
	TweakMotion();
	void readPts();
	void createMidPoints();
	void createbSplinePrimes(); 
	void createFourPointPrimes(); 
	void createJarekPrimes(); 
	void updateBSplineTweaks();
	void updateFourPointTweaks();
	void updateJareksTweaks(); 
	void iterateSteps(int, MotionType);
	void drawbSpline(void); 
	void drawFourPoint(void); 
	void drawJarek(void); 
	~ TweakMotion();

	private:
	DualQuaternion ctrldQ[400];	
	DualQuaternion mdQ[400];		
	DualQuaternion pdQ[400];
	vector<DualQuaternion> bSplineTweaks;
	vector<DualQuaternion> fourPointTweaks;
	vector<DualQuaternion> jareksTweaks;
	int numVertices;
};

#endif //TWEAK_MOTION_H