#include "mainwindow.h"
#include <QtGui/QApplication>
#include <GL/glut.h>
#include <QDebug>
#include "motion.h"


int main(int argc, char *argv[])
{
	//This initates glut
	glutInit(&argc,argv);
	QApplication app(argc, argv);
	MainWindow mw;
	mw.show();
	return app.exec();
}
