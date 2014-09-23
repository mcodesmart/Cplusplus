/******************************************************************
**mainwindow.h 
**
**Class definition file for a Main Window class and operations
**
**April 29th, 2014
****************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"
#include "motion.h"
#include "glwidget.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();
	Motion motionHandler;
	void next();
	void prev();
	void deleteLast();
	void enterPositions();
	void reset();
	void updateTextBox();
	void displayCurrentVectors(vector<double>,vector<double>);
	void readFile();
	void saveFile();
	
private slots:
	void on_insertFromFileButton_clicked();
	void on_finishButton_clicked();
	void on_addPosesButton_clicked();
	void on_modifyPosesButton_clicked();
	void on_deletePosesButton_clicked();
	void on_clearTweakMotionButton_clicked();
	void on_clearButton_clicked();
	void on_nextButton_clicked();
	void on_previousButton_clicked();
	void on_setButton_clicked();
	void on_resetButton_clicked();
	void on_drawButton_clicked();
	void on_actionRead_From_File_activated();
	void on_actionSave_Motion_activated();
	void on_actionExit_Program_activated();
	void printStatusBar(QString);
	void showMessageBox(QString msg);
	void button_enable();
	void help();

signals:
	void drawMotion(int,int); // 1 = bspilne, 2 = fourpoint, 3 = jarek
	void sendMotion(Motion);

private:
	Ui::MainWindowClass ui;
	bool readFromFile;
	bool readFromUser;
	bool pointsSet;
	int poseCounter;
	int numberOfIterations;
	vector<double> xP, yP, zP;
	vector<double> xR, yR, zR;

};

#endif // MAINWINDOW_H
