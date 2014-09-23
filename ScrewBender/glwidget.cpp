/****************************************************************************
 ** Written for MEC 510 - Object Oriented Programming for Engineers
 ** 
 ** Term Project 
 **
 ** Implememtation file for QGLWidget for displaying motion
 ** 
 ** April 26th, 2014
 ****************************************************************************/
#include <QDebug>
#include <QtGui>
#include <QtOpenGL>
#include <QMouseEvent>
#include <QImage>


#include "glwidget.h"
#include "tweakmotion.h"
#include "mainwindow.h"
#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
	{
		
		 xRot = 0.0f;
		 yRot = 0.0f;
		 zRot = 0.0f;
		 xTrans = 0.0f;
		 yTrans = 0.0f;
		 scale = 1.0f;
		 draw = 0;
		/*input.numberOfPoses = 2;
		inputTweakMotion.numberOfPoses = 2;
		 Quaternion q1 = Quaternion(0.68269,0.34134,0.40961,0.49964);
		 Quaternion q2 = Quaternion(0.076441,1.22328,-0.938694,0.830112);
		 Quaternion q3 = Quaternion(-0.14779, 0.08867, -0.29557, 0.93964);
		 Quaternion q4 = Quaternion(-0.743224, 0.208546, 0.579116, 0.577701);
		 Quaternion q5 = Quaternion(0, -0.34215, 0, 0.93964);
		 Quaternion q6 = Quaternion(0.875805, 0.533655, 0.213207, 0.726433);
		 DualQuaternion dqq = DualQuaternion(q1,q2);
		 DualQuaternion dqq2 = DualQuaternion(q3,q4);
		 DualQuaternion dqq3 = DualQuaternion(q5,q6);
		 input.ctrlPos.push_back(dqq);
		 inputTweakMotion.ctrlPos.push_back(dqq);
		 input.ctrlPos.push_back(dqq2);
		 inputTweakMotion.ctrlPos.push_back(dqq2);
		 inputTweakMotion.ctrlPos.push_back(dqq3);*/
	}

 static void qNormalizeAngle(float &angle)
 {
     while (angle < 0)
         angle += 360 * 16;
     while (angle > 360 * 16)
         angle -= 360 * 16;
 }

 void GLWidget::setXRotation(float angle)
 {
     qNormalizeAngle(angle);
     if (angle != xRot) {
         xRot = angle;
         updateGL();
     }
 }

  void GLWidget::setYRotation(float angle)
 {
     qNormalizeAngle(angle);
     if (angle != yRot) {
         yRot = angle;
         updateGL();
     }
 }

 void GLWidget::setZRotation(float angle)
 {
     qNormalizeAngle(angle);
     if (angle != zRot) {
         zRot = angle;
         updateGL();
     }
 }

 void GLWidget::initializeGL()
	 {
    glClearColor(1.0,1.0,1.0,1.0);
	GLUquadricObj *qobj = gluNewQuadric();	
	gluQuadricDrawStyle(qobj,GLU_FILL);
	gluQuadricNormals(qobj,GLU_SMOOTH);	
	glClearDepth( 1.0f );
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	double eqn[] = {0.01f,0.0f,0.01f,-1.0f};// enable clip plane	
	glClipPlane(GL_CLIP_PLANE0,eqn);
	setupLight();
	}



void GLWidget::paintGL()
	{

	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glMatrixMode(GL_MODELVIEW);
	 glPushMatrix();
	 glLoadIdentity();
	 glTranslatef(0.0, 0.0, -5.0f);
     glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
     glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
     glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
	 glTranslatef(xTrans/10.0, yTrans/10.0, 0.0f );
	 glScalef(scale, scale, scale);
	 input.drawControlPoses();			//always draw the control points

	 if (draw == 1)
		 {
		 inputTweakMotion.drawbSpline();
		 qDebug()<<"bSpline";
		 }
	 else if (draw == 2)
		 {
		inputTweakMotion.drawFourPoint();
		qDebug()<<"fourPoint";
		 }
	 else if (draw == 3){
		inputTweakMotion.drawJarek();
		qDebug()<<"Jarek";
		 }
	 glPopMatrix();
	

	 }

//ok for now
void GLWidget::resizeGL(int w, int h)
	{
	 double ratio = (double)w/(double)h;
     //glViewport((w - side) / 2, (h - side) / 2, side, side);
	 glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	 glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
	 gluPerspective(70.0f, ratio, 0.1f, 10000.0f);
   //  glOrtho(-15.0, +15.0, -10.0, +15.0, 1.0, 15.0);
	// glOrtho(-2.5, +2.5, -2.5, +2.5, 4.0, 15.0);
     glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity ();
     glTranslatef(0.0f, 0.0f, -10.0f);
}

 void GLWidget::mousePressEvent(QMouseEvent *event)
 {
     lastPos = event->pos();
 }

 void GLWidget::mouseMoveEvent(QMouseEvent *event)
 {
	QPointF mousePosition = event->pos(); 
	QString str;
	QTextStream(&str) <<  mousePosition.x() << ", " << mousePosition.y() ;
	emit mousePositionChanged(str);

     float dx = event->x() - lastPos.x();
     float dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 8.0 * dy);
         setYRotation(yRot + 8.0 * dx);
		 
     } else if (event->buttons() & Qt::RightButton) {
		// setZRotation(zRot + 8.0 * dx);
		//setXRotation(xRot + 8.0 * dy);
         xTrans += dx/100;
		 yTrans -= dy/100;	
		 qDebug()<< xTrans<<yTrans;
		
     }    
     lastPos = event->pos();
 }

 void GLWidget::wheelEvent(QWheelEvent *e)
 {
      e->delta() > 0 ? scale += scale*0.1f : scale -= scale*0.1f;
      updateGL();
 }

   void GLWidget::saveGLState()
 {
     glPushAttrib(GL_ALL_ATTRIB_BITS);
     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
 }

   void GLWidget::restoreGLState()
 {
     glMatrixMode(GL_PROJECTION);
     glPopMatrix();
     glMatrixMode(GL_MODELVIEW);
     glPopMatrix();
     glPopAttrib();
 }

    void GLWidget::setupLight(void)
{
	
	float LightAmbient[]	= { 1.0f, 1.0f, 1.0f, 1.0};
	float LightDiffuse[]	= { 0.7f, 0.7f, 0.7f, 1.0f};
	float LightSpecular[]	= { 1.0f, 1.0f, 1.0f, 1.0f };
	float LightPosition[]	= { 3.0f, 3.0f, 3.0f, 1.0f };

	float RedSurface[]   = { 1.0f, 0.0f, 0.0f, 1.0f};
	float GreenSurface[] = { 0.0f, 1.0f, 0.0f, 1.0f};
	float BlueSurface[]  = { 0.0f, 0.0f, 1.0f, 1.0f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	float no_mat[]={0.0f,0.0f,0.0f,1.0f};
    float mat_ambient[]={0.7f,0.7f,0.7f,1.0f};
    float mat_ambient_color[]={0.8f,0.3f,0.7f,1.0f};
    float mat_diffuse[]={0.7f,0.7f,0.7f,1.0f};
    
    float mat_specular[]={0.7f,0.7f,0.7f,1.0f};

    float no_shininess[]={0.0};
    float low_shininess[]={5.0};
    float high_shininess[]={100.0};
    float mat_emission[]={0.2f,0.1f,0.1f,0.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
    glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission); 
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);

}

	 void GLWidget::drawMotionTypeOnScreen(int typeOfMotion, int numberOfIterations)
		 {
		 qDebug()<<"Im working";
		 draw = typeOfMotion;
		 inputTweakMotion.setNumIterations(numberOfIterations);
		 if (typeOfMotion == 0)  inputTweakMotion.clear();
		 updateGL();
		 }
   
    void GLWidget::recieveMotion(Motion motionType)
		{
		qDebug()<<"Motion Recieved";
		input= motionType;
		if (motionType.numberOfPoses == 0) 
			{
			inputTweakMotion.numberOfPoses =0;
			inputTweakMotion.clear();
			}
		inputTweakMotion.numberOfPoses = motionType.numberOfPoses;
		inputTweakMotion.ctrlPos = motionType.ctrlPos;
		 updateGL();
		
		}