========================================================================
TERM PROJECT
========================================================================
MEC 510.01: Object-Oriented Programming for Scientists and Engineers
Professor: A. Purwar
Author: Mahder Tewolde & Smiti Bhattacharya
MAY 20, 2014


**************************************************************************************
Problem:
**************************************************************************************
Smooth piecewise helical motions (polyscrew) are difficult to animate due to discontinuities 
between adjacent screws [1].


**************************************************************************************
Goals:
**************************************************************************************
The goal for this project was to implement a polyscrew subdivision routine using dual 
quaternions as the control points to smooth polyscrew motions. The subdivision schemes
to be implemented are the b-spline tweak, 4-point tweak and Jarek’s tweak.
These motions are to be developed in C++ using object oriented programming(OOP) principles.
A user interface is also required to be developed using Qt which can 
(a)Allow the user to input control points
(b)Select a subdivision scheme and the number of iterations of that scheme
(c)Render or draw the control points and the susequent motion


**************************************************************************************
What we did:
**************************************************************************************
We implemented a polyscrew subdivision routine for motion animation using the polynomial 
subdivision scheme described by Powell and Rossignac [1].This subdivision (split and tweak) 
scheme will include b-spline tweak, 4-point tweak and Jarek’s tweak. 
The translation and rotation was implemented in a dual quaternion space. The necessary 
classes for implementing these motion were developed in C++ using an OOP methodology. 
The motion visualization was implemented in Qt. A user interface application was 
developed to define control poses (position and orientation) for plotting motion and 
navigation of the motion in 3D space. The motion was modified by adding or removing 
control points and the user is allowed to choose one of the three schemes (B-spilne, 4-point & Jarek) 
described in the paper as well as the the number of iterations of each scheme.


**************************************************************************************
What worked:
**************************************************************************************
We have succeeded in our goal of implementing a polyscrew subdivision routine with dual
quaternions as control points by implementing the aforementioned three subdivision algorithms.
In addition, we have developed a software using Qt that:
(a)Allows the user to manually enter control points or input the data from a text file
(b)Allows the user to select a subdivision scheme and plot the resultant smooth motion
   on screen.
(c)Additional features of our sofware include:
	-Deleting Control Points
	-Modifying a Control Point
	-Saving the motion to a ".txt" file
   

*************************************************************************************
CLASS DESCRIPTIONS
__________________

The following base classes are used
1. Dual Number
	This class is used to represent a dual number that has a real part and a dual part which
	also act as the private data members. The operations on dual numbers are also implemented 
	as member functions.
2. Quaternion
	A quaternion is used to represent a rotation in three dimensional space. This class is 
	used to represent a quaternion class and has four private data members which represent
	each coefficient of the quaternions. The class is implemented as a vector of four doubles
	with the required constructors. Mathematical operators on quaternions are overloaded using 
	member functions stream input and output operators are implemented as memeber functions.
	Because a UI is impelemeted in Qt, these stream extraction operators are used for debug
	ging purposes only. 
3. Point3D
	A point class is used to represent points in 3D space.

4. Matrix Class
	A self contained class for an arbitrary matrix represenation.
5. hPoint CLass
	A class used for a homogeneous point representation of a point or a plane.
6. hMatrix Class
        The hMatrix class is used for the homogeneous matrix representation of
	a Dual Quaternion and inherits from the Matrix class. The class is implemented as a 4X4
	matrix with the required constructor. In addition, Mathematical and stream input output
	operators are implemented as member functions.
7. Dual Quaternion Class
	A Dual Quaternion is an ordered pair of Quaternions.This class is used to represent a dual 
	Quarternion as a Quaternion unit and a dual Unit. The class is implemented either as a type 	
	Quaternion or a vector of doubles with the required constructors.The mathematical operators 	
	on Dual Quaternions are overloaded using member functions in addition, stream input and 	       
	output operators are implemented as memeber functions.

8. Motion Class (Base Class for other motion classes)
	Motion class is a base class for any kind of motion. It is responsible for reading 
	control points from file and saving motion parameters to file. It can be used to 
	create additional types of motion, for example, bezier motions. 

9. TweakMotion Class
	This class inherits from the motion class. It uses the control poses saved in motion
	class to generate the motions using a subdivion scheme. 
10. Main Window
        This class inherits from the QMainWindow class.It handles the sequence of events that 
	occur in the main UI window when buttons are clicked through a signal-slot mechanism.
11. glwidget
	This is a class for rendering OpenGL graphics and inherits from the QGLWidget class.It
	is used to control the operation of the widgets on the UI through the signal slot 
	mechanism.

**********************************************************************************************
Methods for each class
**********************************************************************************************

The following services are provided for the Dual Number Class

	1. Allows the user to create a Dual object using a constructor which sets the real and
	   dual parts based on user input or initializes dual to be 0.0, if not given.
	2. Allows the user to modify the real and dual part via Set functions (2 functions).
	3. Allows the user to “get” the real and dual part of each Dual number (2 functions).
	4. Allows the user to perform a series of binary operations(namely: +;-;*;/;=) through 
	   operator overloading(13 functions).
	5. Allows stream input and output operators to be implemented as member functions (4functions).

The following services are provided for the Dual Quaternion Class
	1. Allows the user to create a Dual Quaternion object using constructors that set the
	   Quaternion unit and dual unit's based on user input or initializes the values as 0.0 if 
	   not given.
	2. Allows the user to perform a series of binary operations operations(namely: +;-;*;/;=;^) 	  
	   through operator overloading(19 functions).
	3. Allows the user to make the member dual part zero using the Clear() method.
	4. Allows the user to "get" the Real and Dual parts of the Dual Quaternion (2 functions)
	5. Allows the user to obtain the Length, Inverse and Conjugate of the DualQuaternion object.
	6. Allows the user to convert the Dual Quaternion to a Homogeneous Matrix form.
	7. Allows the user to save the data from the object into a file using the Print() method.


The following services are provided for the glwidget Class
	1. A GLWidget constructor is used to set the initial values of x,y and z rotations and 
	   x and y translation to 0.0. The constructor is also used to set the scale to 1.
	2. Allows the user to save and restore the state of the OpenGL scene.
	3. Allows the user to draw a motion on the screen by selecting the motion type(in this 	   	           
	   case either BSpline, Jarek or fourpoint Tweak algorithm) and the number of iterations 	   	   
	   by using the drawMotionTypeOnScreen() and recieveMotion() methods.
	4. Allows the user to normalize an angle so that it falls between 0 and 360 using method
	   qNormalizeAngle() and set the x,y and z rotation angles using the setXRotation(),
	   setYRotation() and setZRotation() methods respectively.
	5. Allows the user to draw the selected motion using the paintGL() method.
	6. Allows the user to set the UI with methods resizeGL() and initializeGL(). In addition 
	   the methods mousePressEvent(),mouseMoveEvent() and wheelEvent() allow the user to 
	   interface mouse events with the interface. The method setupLight() allows the user to 
	   to set the appearence of the UI.

The following services are provided for the hMatrix Class
	1. A hMatrix() constructor is used to generate a 4x4 matrix and initialize the elements to
           0.0.
	2. Allows the user to perform binary operations(namely:*;=) through operator overloading
	   (3 functions).In addition, stream a output operator is implemented as member functions 
	   (1 function).
	3. The inverse() and transpose() functions calculate the inverse and transpose of the 	   	           
	   Matrix respectively and the method Clear() resets the components of the hMatrix to 0.0.


The following services are provided for the hPoint Class
	1. An hPoint() constructor is used to populate the coordinate vector depending on the 
	   input type.
	2. Allows the user to perform binary operations(namely:*;/;^;+;-;=) through operator 	   	   	   
	   overloading (9 functions). In addition, stream input and output operators are 	   	   	   
	   implemented as memberfunctions (4 functions)
	3. The coordinates in the "coordinate vector" are normalized with the PointNormalize() 	   	   	   
	   method, the PlaneNormalize() method is used to normalize the plane.The PointTransform() 
	   and PlaneTransform() methods serve to transform the points and planes.
	4. Clear() allows the user to set the values of the coordinate vector to 0.0 and the 	   	   	   
	   getCoordPoint() method is used to "get" the coordinate values.
	   The following services are provided for the mainwindow Class
	1. The mainwindow() constructor initializes the widgets on the UI screen while inheriting
	   from the QMainWindow.
	2. Through a series of private slots, methods such as on_insertFromFileButton_clicked(),
	   on_finishButton_clicked();on_addPosesButton_clicked();on_modifyPosesButton_clicked();
	   on_deletePosesButton_clicked();on_clearButton_clicked();on_nextButton_clicked();
	   to name a few dictate the course of action once a user clicks on a specific button.
	3. The next() and prev() methods allows dictate the sequence of events upon pushing the
	   "next" and "previous" buttons on the UI. The help() method dictates the occurance of 
	   events upon selecting "Help" in the menu bar on the UI.
	4. The enterPositions() method allows the values input for x,y and z translation and 
	   rotation to be converted to Dual Quarternions and the readfile() method allows for data
	   from a ".txt" file to be input to the main window. The method displayCurrentVector()
	   displays the values entered by the user upon hitting the "next" button on the screen in
	   the message box.
	5. The printStatusBar() and showMessageBox() methods dictate the appearence of the data 
	   entered on the UI.

The following services are provided for the Matrix Class
	1. Allows the user to create a Matrix object using a constructor which sets the rows and 
	   colums to zero if not given.
	2. The getMatrixElement() and setMatrixElement() methods allow the user to access and set
	   the elements in the matrix object.
	3. A series of binary operators (namely: +;-;*;=) are allowed to be performed by the user
	   through operator overloading (4 functions)
	4. The Inverse() and Transpose() methods allow for the user to compute the inverse and 
	   transpose of the Matrix respectively and Clear() resets the values of the Matrix to 0.0.
	   DeleteSpace(), deletes the elements in the matrix whereas MallocSpace() allocates
	   memory for the matrix.

The following services are provided for the motion Class
	1. The method readCtrlPositions() allows the program to read control positions from a file.
	   The method clear() deletes all the entered poses.
	2. deleteLastControlPose() begins by deleting the last pose entered by the user. The method
	   drawControlPoses() draws the location of each point on the screen and the split() method
	   returns the midpoint of two DualQuarternions.

The following services are provided for the Point3D Class
	1. The constructor Point3D allows the user to implement an object of type Point3D 	   	           
	   initializing its elements to 0.0 if no value has been input.	
	2. A series of binary operators (namely: +;-;*;/;=) are allowed to be performed through
	   operator overloading (7 functions). The Normalize() method normalizes the elements of
	   the Point3D object.

The following services are provided for the Quaternion Class
	1. The class is implemented as a vector of four doubles with the required constructors.
	2. Mathematical operators on quaternions are overloaded using  member functions as 	   	   	   
	   are the stream input and output operators.
	3. The getQuaternionElement() allows the user to access the Quaternion elements. The
	   functions Modulus(), Conjugate() and Inverse() allow the user to perform the same
	   mathematical operations on the Qaternion.
	4. The method qaternionToRotationMatrix() allows the user to convert the Quaternion to
	   a 3X3 Matrix.
	5. The method getEuler() allows the user to convert the Quaternion to Euler angles while 	   	   
	   the method eulerToQuaternion() converts the Euler angles back to Quaternions.
	   The following services are provided for the tweakmotion Class
	1. The methods readPts() allows the user to read the control points and create mid points
	   using the method createMidPoints().
	2. For each of the three tweak algorithms, the methods createbSplinePrimes();
	   createFourPointPrimes(); createJarekPrimes(), creates the prime vertices. 	   	   	   	   
	   Likewise, updateBSplineTweaks();updateFourPointTweaks();updateJareksTweaks() updates the 
	   tweak points of all of the algorithms. Method iterateSteps() selects one of the three
	   algorithms and iterates through the points. Finally the drawbSpline(),drawFourPoint()
	   and drawJarek() methods draw the corresponding subdivision scheme.
		
	

**********************************************************************************************
Program instructions:
**********************************************************************************************

1. The Software allows the user to choose two means of selecting the control points
	(a) By manually entering the x,Y and Z Position and Rotation information on the screen
	(b) Directly reading Data From a ".txt" File

2. For option 1(a): Click on the "Add Control Pose" button. This enables the "Set" button and
   allows the user to enter the number of control points. Our program allows for a maximum of 
   six points.Upon entering the number of control points select "Set".
3. This activates the Spin Boxes where the user can input the X,Y and Z Position and Rotation.
   The position ranges in values from -5.0 to +5.0 and the angles are in degrees from -180 to
   +180. The entered values are accepted by pusing the "Next" button. This lets the user proceed
   to enter the next control point. A counter shows the current control point.
4. A "Clear" button clears all of the input data.
5. After all of the points have been entered, the user can click "Finish" to accept the values.
   An information screen in the lower right corner displays the inserted control pose information.
   Once, "Finish" is clicked, the "Draw", "Modify Control Pose" and "Delete Control Pose" buttons
   become active.
6. Upon entering the control point information, select the smoothing Algorithm desired and number
   of iterations. Currenly the upper limit for iterations is seven.
7. Click on "Draw" to smooth the curve.
8. "Modify Control Pose": Selecting this button allows the user to change either the position or
   rotation value for a specific control point indicated on the screen.
9. "Delete Control Pose": This button allows a specific control point to be deleted entirely.
10. For option 1(b): Click on button "Insert from File" and select from the dialog box the path
    of the ".txt" file that containts the data for the control points.
11. The Help function provides a dialog box with some information.
12. File -> SaveMotion saves the information input by the user.

*********************************************************************************************

References:

[1] Screw Bender: Smoothing Piecewise Helical Motions, Alexander Powell, Jarek Rossignac, IEEE 
    Computer Society 

*********************************************************************************************