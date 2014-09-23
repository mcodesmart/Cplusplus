/******************************************************************
**MainWindow.cpp 
**
**Implementation file for Main Window class
**
**April 29th, 2014
****************************************************************/
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QFiledialog>
#include <QtGui>
#include <QDoubleSpinBox>
#include <QTextStream>
#include <QMessagebox>

#include "mainwindow.h"
#include "glwidget.h"
#include "tweakmotion.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
//ui initializtions here
	ui.setupUi(this);
	ui.label_9->hide();
	ui.label_11->hide();
	ui.label_12->hide();
	ui.label_14->hide();
	printStatusBar("Ready");

	//initialize variables here
	poseCounter = 1;
	readFromFile = false;
	readFromUser= false;
	pointsSet = false;

	//connections here
	connect(ui.widget, SIGNAL(mousePositionChanged(QString)), this, SLOT(printStatusBar(QString)));
	connect(ui.xAxisPosition, SIGNAL(valueChanged(double)),this, SLOT(button_enable()));
	connect(ui.yAxisPosition, SIGNAL(valueChanged(double)),this, SLOT(button_enable()));
	connect(ui.zAxisPosition, SIGNAL(valueChanged(double)),this, SLOT(button_enable()));
	connect(ui.xAxisRotation, SIGNAL(valueChanged(double)),this, SLOT(button_enable()));
	connect(ui.yAxisRotation, SIGNAL(valueChanged(double)),this, SLOT(button_enable()));
	connect(ui.zAxisRotation, SIGNAL(valueChanged(double)),this, SLOT(button_enable()));
	connect(ui.bSplineButton, SIGNAL(toggled(bool)),ui.bSplineIterations, SLOT(setEnabled(bool)));
	connect(ui.fouPointButton, SIGNAL(toggled(bool)),ui.fourPointIterations, SLOT(setEnabled(bool)));
	connect(ui.jareksButton, SIGNAL(toggled(bool)),ui.jareksIterations, SLOT(setEnabled(bool)));
	connect(ui.bSplineButton, SIGNAL(toggled(bool)),ui.drawButton, SLOT(setAutoFillBackground (bool))); 
	connect(this, SIGNAL(drawMotion(int,int)), ui.widget, SLOT(drawMotionTypeOnScreen(int,int)),Qt::QueuedConnection);
	connect(this, SIGNAL(sendMotion(Motion)), ui.widget, SLOT(recieveMotion(Motion)));

}

/******************************************************************************************
** ACTIONS OR SLOTS
*******************************************************************************************/

void MainWindow::on_actionExit_Program_activated()
	{
	reset();
	motionHandler.~Motion();
	this->close();
	};

void MainWindow::on_actionRead_From_File_activated()
	{
	readFile();
	ui.label_2->setText("Control Poses Inserted from File");
	readFromFile = true;
	readFromUser = false;
	}


void MainWindow::on_actionSave_Motion_activated()
	{
	saveFile();
	ui.textEdit->moveCursor (QTextCursor::End);
	ui.textEdit->insertPlainText("File Saved");
	}

void MainWindow::on_insertFromFileButton_clicked()
	{
	readFile();
	ui.label_2->setText("Control Poses Inserted from File");
	readFromFile = true;
	readFromUser = false;
	}

void MainWindow::on_addPosesButton_clicked()
	{
	ui.label_2->setText("Enter the number of control poses");
	ui.insertFromFileButton->setDisabled(1);
	ui.numCntrlPosesEdit->setEnabled(1);
	ui.setButton->setEnabled(1);
	readFromUser = true;
	readFromFile = false;
	}


void  MainWindow::button_enable()
	{
	if(readFromUser==true)
		{
		enterPositions();
		}
	}


void MainWindow::on_previousButton_clicked()
{
	prev();
}


void MainWindow::on_nextButton_clicked()
{
	next();
}

void MainWindow::on_finishButton_clicked()
{	
	pointsSet = true;
	ui.drawButton->setEnabled(1);
	ui.modifyPosesButton->setEnabled(1);
	ui.deletePosesButton->setEnabled(1);
	ui.clearButton->setDisabled(1);
	ui.finishButton->setDisabled(1);
	ui.nextButton->setDisabled(1);
	ui.previousButton->setDisabled(1);
	ui.xAxisPosition->setDisabled(1);
	ui.yAxisPosition->setDisabled(1);
	ui.zAxisPosition->setDisabled(1);
	ui.xAxisRotation->setDisabled(1);
	ui.yAxisRotation->setDisabled(1);
	ui.zAxisRotation->setDisabled(1);
}

void MainWindow::on_modifyPosesButton_clicked()
{
	ui.clearButton->setEnabled(1);
	ui.finishButton->setEnabled(1);
	
	ui.xAxisPosition->setEnabled(1);
	ui.yAxisPosition->setEnabled(1);
	ui.zAxisPosition->setEnabled(1);
	ui.xAxisRotation->setEnabled(1);
	ui.yAxisRotation->setEnabled(1);
	ui.zAxisRotation->setEnabled(1);
	if(readFromFile)
	{
		ui.nextButton->setEnabled(1);

	}

	if(readFromUser)
	{
		ui.previousButton->setEnabled(1);

	}
}

void MainWindow::on_deletePosesButton_clicked()
	{
		deleteLast();
	}

 void MainWindow::on_clearButton_clicked()
	 {
	 if(readFromUser)
		 {
		if (poseCounter>1){
		ui.xAxisPosition->setValue(xP[poseCounter -1]);
		ui.yAxisPosition->setValue(yP[poseCounter -1]);
		ui.zAxisPosition->setValue(zP[poseCounter -1]);
		ui.xAxisRotation->setValue(xR[poseCounter -1]);
		ui.yAxisRotation->setValue(yR[poseCounter -1]);
		ui.zAxisRotation->setValue(zR[poseCounter -1]);}
	}
 };

void MainWindow::on_setButton_clicked()
{
	motionHandler.numberOfPoses = ui.numCntrlPosesEdit->value();
	ui.numCntrlPosesEdit->setDisabled(1);
	ui.setButton->setDisabled(1);
	ui.resetButton->setEnabled(1);
	ui.label_2->setText("Enter Positions and Click Finish");
	ui.label_9->show();
	ui.label_11->show();
	ui.label_12->show();
	ui.label_14->show();
	ui.label_9->setText(QString::number(poseCounter));
	ui.label_12->setText(QString::number(motionHandler.numberOfPoses));
	ui.textEdit->setPlainText("Number of Control Poses: "
		+ QString::number(motionHandler.numberOfPoses)+"\n\n");
	ui.xAxisPosition->setEnabled(1);
	ui.yAxisPosition->setEnabled(1);
	ui.zAxisPosition->setEnabled(1);
	ui.xAxisRotation->setEnabled(1);
	ui.yAxisRotation->setEnabled(1);
	ui.zAxisRotation->setEnabled(1);
	ui.clearButton->setEnabled(1);
	ui.nextButton->setEnabled(1);
	

	for(int i=0; i<motionHandler.numberOfPoses; i++)
		{
	DualQuaternion zerodQ = DualQuaternion(Quaternion(0,0,0,0), Quaternion(0,0,0,0));
	motionHandler.ctrlPos.push_back(zerodQ);
		}
}

void MainWindow::on_resetButton_clicked()
{
	
	reset();
	emit drawMotion(0,0);		//clear
	emit sendMotion(motionHandler);	//send cleared motion to clear screen
	
}

void  MainWindow::on_drawButton_clicked()
	{
	if (ui.jareksButton->isChecked() )
		{
		if(readFromUser) {emit sendMotion(motionHandler);}				
		numberOfIterations = ui.jareksIterations->value();
		emit drawMotion(3,numberOfIterations); //3 draws a four point
		//fix for strange bug in program
		ui.resetButton->setDisabled(1);
		}
	if (ui.bSplineButton->isChecked() ) 
		{
		if(readFromUser) {emit sendMotion(motionHandler);}		
		numberOfIterations = ui.bSplineIterations->value();
		emit drawMotion(1,numberOfIterations); //1 draws a bspline
		ui.resetButton->setEnabled(1);
		}
	if (ui.fouPointButton->isChecked() )
		{
		if(readFromUser) {emit sendMotion(motionHandler);}			
		numberOfIterations = ui.fourPointIterations->value();
		emit drawMotion(2,numberOfIterations); //2 draws a four point
		ui.resetButton->setEnabled(1);
		}

	}

void  MainWindow::on_clearTweakMotionButton_clicked()
	{
	emit drawMotion(0,1); //3 draws a four point
		}

/******************************************************************************************
** CLASS METHODS
*******************************************************************************************/

void MainWindow::next()
{	

	poseCounter = poseCounter + 1;
	ui.label_9->setText( QString::number(poseCounter) );
	if (poseCounter>=1)
		ui.previousButton->setEnabled(1);
	if (poseCounter == motionHandler.numberOfPoses)
		{
		if(readFromUser) ui.finishButton->setEnabled(1);
		ui.nextButton->setDisabled(1);
		}

		xP.push_back(ui.xAxisPosition->value());
		yP.push_back(ui.yAxisPosition->value());
		zP.push_back(ui.zAxisPosition->value());
		xR.push_back(ui.xAxisRotation->value());
		yR.push_back(ui.yAxisRotation->value());
		zR.push_back(ui.zAxisRotation->value());

	if(readFromFile)
		{
			DualQuaternion QR = motionHandler.ctrlPos[poseCounter-1];
			Quaternion Q = QR.GetReal();	//rotation part
			Quaternion R = QR.GetDual();    //tranlation part
			Quaternion T = (R*Q.Conjugate() - Q*R.Conjugate())/Q.Modulus(); // recover translation component
			vector<double> angles = R.getEuler().getCoordPoint();
			vector<double> positions = T.getQuaternionElement();
			double xPosDisp = positions[0];
			double yPosDisp = positions[1];
			double zPosDisp = positions[2];
			double xRotDisp = angles[0];
			double yRotDisp = angles[1];
			double zRotDisp = angles[2];
			ui.xAxisPosition->setValue(xPosDisp);
			ui.yAxisPosition->setValue(yPosDisp);
			ui.zAxisPosition->setValue(zPosDisp);
			ui.xAxisRotation->setValue(xRotDisp);
			ui.yAxisRotation->setValue(yRotDisp);
			ui.zAxisRotation->setValue(zRotDisp);
	}

	if(readFromUser)
		{
		updateTextBox();
		}
}

void MainWindow::prev()
{
	poseCounter = poseCounter - 1;
	ui.label_9->setText( QString::number(poseCounter) );
	if (poseCounter==1)
		ui.previousButton->setDisabled(1);
	if (poseCounter<=motionHandler.numberOfPoses)
		ui.nextButton->setEnabled(1);

	if(readFromFile)
		{
	DualQuaternion QR = motionHandler.ctrlPos[poseCounter-1];
	Quaternion Q = QR.GetReal();	//rotation part
	Quaternion R = QR.GetDual();    //tranlation part
	Quaternion T = (R*Q.Conjugate() - Q*R.Conjugate())/Q.Modulus(); // recover translation component
	vector<double> angles = R.getEuler().getCoordPoint();
	vector<double> positions = T.getQuaternionElement();
	double xPosDisp = positions[0];
	double yPosDisp = positions[1];
	double zPosDisp = positions[2];
	double xRotDisp = angles[0];
	double yRotDisp = angles[1];
	double zRotDisp = angles[2];
	ui.xAxisPosition->setValue(xPosDisp);
	ui.yAxisPosition->setValue(yPosDisp);
	ui.zAxisPosition->setValue(zPosDisp);
	ui.xAxisRotation->setValue(xRotDisp);
	ui.yAxisRotation->setValue(yRotDisp);
	ui.zAxisRotation->setValue(zRotDisp);
		}

	if(readFromUser)
		{
		updateTextBox();
		}
}

void MainWindow::reset()
	{
	ui.insertFromFileButton->setEnabled(1);
	readFromFile = false;
	readFromUser = false;
	pointsSet = false;
	poseCounter = 1;
	xP.clear(); yP.clear(); zP.clear();
	xR.clear(), yR.clear(), zR.clear();
	motionHandler.clear();
	ui.numCntrlPosesEdit->setValue(1);
	ui.numCntrlPosesEdit->setDisabled(1);
	ui.setButton->setDisabled(1);
	ui.resetButton->setDisabled(1);
	ui.label_2->show();
	ui.label_2->setText("Insert Points or Read from File");
	ui.label_9->hide();
	ui.label_11->hide();
	ui.label_12->hide();
	ui.label_14->hide();
	ui.textEdit->clear();
	ui.xAxisPosition->setValue(0.0);
	ui.yAxisPosition->setValue(0.0);
	ui.zAxisPosition->setValue(0.0);
	ui.xAxisRotation->setValue(0.0);
	ui.yAxisRotation->setValue(0.0);
	ui.zAxisRotation->setValue(0.0);
	ui.xAxisPosition->setDisabled(1);
	ui.yAxisPosition->setDisabled(1);
	ui.zAxisPosition->setDisabled(1);
	ui.xAxisRotation->setDisabled(1);
	ui.yAxisRotation->setDisabled(1);
	ui.zAxisRotation->setDisabled(1);
	ui.deletePosesButton->setDisabled(1);
	ui.modifyPosesButton->setDisabled(1);
	ui.drawButton->setDisabled(1);
	ui.clearButton->setDisabled(1);
	ui.nextButton->setDisabled(1);
	ui.previousButton->setDisabled(1);
	}

void MainWindow::readFile()
	{
	QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath(), "Text File(*.txt)");
	motionHandler.readCtrlPositions(filename);		//read control positions here
	emit sendMotion(motionHandler);					//draw poistions immediately to screen
	updateTextBox();					//show the dual Quaternions on the text box
	ui.numCntrlPosesEdit->setValue(motionHandler.numberOfPoses);
	ui.nextButton->setEnabled(1);
	ui.drawButton->setEnabled(1);
	ui.modifyPosesButton->setEnabled(1);
	ui.deletePosesButton->setEnabled(1);
	ui.finishButton->setDisabled(1);
	ui.resetButton->setEnabled(1);
	ui.label_9->show();
	ui.label_11->show();
	ui.label_12->show();
	ui.label_14->show();
	ui.label_9->setText(QString::number(poseCounter));
	ui.label_12->setText(QString::number(motionHandler.numberOfPoses));

	DualQuaternion QR = motionHandler.ctrlPos[poseCounter-1];
	Quaternion Q = QR.GetReal();	//rotation part
	Quaternion R = QR.GetDual();    //tranlation part
	Quaternion T = (R*Q.Conjugate() - Q*R.Conjugate())/Q.Modulus(); // recover translation component
	vector<double> angles = R.getEuler().getCoordPoint();
	vector<double> positions = T.getQuaternionElement();
	double xPosDisp = positions[0];
	double yPosDisp = positions[1];
	double zPosDisp = positions[2];
	double xRotDisp = angles[0];
	double yRotDisp = angles[1];
	double zRotDisp = angles[2];
	ui.xAxisPosition->setValue(xPosDisp);
	ui.yAxisPosition->setValue(yPosDisp);
	ui.zAxisPosition->setValue(zPosDisp);
	ui.xAxisRotation->setValue(xRotDisp);
	ui.yAxisRotation->setValue(yRotDisp);
	ui.zAxisRotation->setValue(zRotDisp);
	}

void MainWindow::saveFile()
	{
	 QString filename = QFileDialog::getSaveFileName(this,tr("Save Document"),
						QDir::currentPath(),tr("Text File(*.txt)"));
	 motionHandler.writeCtrlPositions(filename);	
    }
	

void MainWindow::deleteLast()
{
	if (poseCounter ==  motionHandler.numberOfPoses)
		poseCounter = poseCounter-1;
		motionHandler.deleteLastControlPose();
		ui.label_12->setText(QString::number(motionHandler.numberOfPoses));
		ui.label_9->setText(QString::number(poseCounter));
		emit sendMotion(motionHandler);						//draw poistions immediately to screen
}

void MainWindow::enterPositions()
{
	double xPos = ui.xAxisPosition->value();
	double yPos = ui.yAxisPosition->value();
	double zPos = ui.zAxisPosition->value();
	double xRot = ui.xAxisRotation->value();
	double yRot = ui.yAxisRotation->value();
	double zRot = ui.zAxisRotation->value();
	Quaternion  RotationQuaternion = RotationQuaternion.eulerToQuaternion(Vector(xRot,yRot,zRot));
	Vector TranslationVector = Vector(xPos,yPos,zPos,0.0);
	DualQuaternion dQ = DualQuaternion(RotationQuaternion, TranslationVector);
	motionHandler.ctrlPos[poseCounter-1] = dQ;
	emit sendMotion(motionHandler);						//draw poistions immediately to screen
	vector<double> printTrans = TranslationVector.getCoordPoint();
	vector<double> printRot = RotationQuaternion.getQuaternionElement();
	displayCurrentVectors(printTrans,printRot);
	ui.label_2->setText("Input All Points");
		}

void MainWindow::printStatusBar(QString msg)
	{
	ui.statusBar->showMessage(msg);
	}

void MainWindow::showMessageBox(QString msg)
	{
	QMessageBox msgBox;
	msgBox.setText(msg);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int ret = msgBox.exec();
    }

void MainWindow::displayCurrentVectors(vector<double> V1,vector<double> V2) 
	{
	ui.textEdit->setText("Number of Control Poses = "+QString::number(motionHandler.numberOfPoses)+"\n\n");
	ui.textEdit->moveCursor (QTextCursor::End);
	ui.textEdit->insertPlainText("Translation Vector "+ QString::number(poseCounter)+ " = " + 
		QString::number( V1[0],'f',3)+", "+QString::number( V1[1],'f',3)+", "+
		QString::number( V1[2],'f',3)+", "+QString::number( V1[3],'f',3)+"\n");
	ui.textEdit->insertPlainText("Rotation Vector "+ QString::number(poseCounter)+ " = " + 
		QString::number( V2[0],'f',3)+", "+QString::number( V2[1],'f',3)+", "+
		QString::number( V2[2],'f',3)+", "+QString::number( V2[3],'f',3)+"\n");
	 vector<double> DQ = motionHandler.ctrlPos[poseCounter-1].getDualQuaternionElements();
	ui.textEdit->insertPlainText("Dual Quaternion "+ QString::number(poseCounter)+ " = " + 
		QString::number(DQ[0],'f',3)+", "+QString::number(DQ[1],'f',3)+", "+ 
		QString::number(DQ[2],'f',3)+", "+QString::number(DQ[3],'f',3)+", "+
		QString::number(DQ[4],'f',3)+", "+QString::number(DQ[5],'f',3)+", "+
		QString::number(DQ[6],'f',3)+", "+QString::number(DQ[7],'f',3)+"\n\n");
	};


void MainWindow::updateTextBox(void)
	{
	vector<double> print;
	ui.textEdit->moveCursor (QTextCursor::End);
	ui.textEdit->insertPlainText("Number of Control Poses = "+ QString::number(motionHandler.numberOfPoses)+"\n\n");
	for(int i=0; i<motionHandler.numberOfPoses; i++)
		{
	     print= motionHandler.ctrlPos[i].getDualQuaternionElements();
		 ui.textEdit->insertPlainText(QString::number(print[0])+", "+QString::number(print[1])+", "+
		 QString::number(print[2])+", "+QString::number(print[3])+", "+QString::number(print[4])+", "+
		 QString::number(print[5])+", "+QString::number(print[6])+", "+ QString::number(print[7])+"\n\n");
	 	}
	}

//do not use, need to pause appliaction when called...(use new window)
void MainWindow::help()
{
   QTextEdit* help=new QTextEdit();
   help->setWindowFlags(Qt::Dialog); //or Qt::Tool, Qt::Dialog if you like
   setWindowTitle(tr("Simple Text Viewer"));
   resize(750, 400);
   help->setReadOnly(true);
   QFile file("ReadMe.txt");
   QTextStream stream ( &file );
   QString line;
   if(file.exists()){
   if (!file.open (QIODevice::ReadOnly))
    {
          QMessageBox::warning(this,"Alert", "Missing File",QMessageBox::Ok);
              return;
    }
			help->setHtml(stream.readAll());
	   }
	file.close();
    help->show();
}


MainWindow::~MainWindow()
{
	
}
