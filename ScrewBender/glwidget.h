#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "motion.h"
#include "tweakmotion.h"

class GLWidget : public QGLWidget
{
	Q_OBJECT
friend class MainWindow;
public:
	explicit GLWidget(QWidget *parent =0);
	void saveGLState();
    void restoreGLState();
	

public slots:
	void setXRotation(float angle);
	void setYRotation(float angle);
	void setZRotation(float angle);
	void drawMotionTypeOnScreen(int, int);
	void recieveMotion(Motion);
	//QGLWidget* getGLWidget() { return _glwidget; }

signals:
	void mousePositionChanged(QString);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
	void setupLight(void);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *e);

private:
    float xRot;
    float yRot;
    float zRot;
	float xTrans;
	float yTrans;
	float scale;
	int draw;
    QPoint lastPos;
	Motion input;
	TweakMotion inputTweakMotion;
	QGLWidget* _glwidget;

};
#endif //GLWIDGET_H