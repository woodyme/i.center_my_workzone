
#ifndef DLGNCMONDEMO_H
#define DLGNCMONDEMO_H

#include <QDialog>

class QTimer;
class QTextCodec;
class QLabel;
class QLineEdit;
class QPushButton;

#include "NcMonInterface.h"

class DlgNcMonDemo : public QDialog
{
	Q_OBJECT
	
public:
	DlgNcMonDemo(QWidget *parent = 0);
	~DlgNcMonDemo();
	
private:
	JDMACHMON *pMachMon;

	QTimer *timer;

	QTextCodec *codec;
	
	QLabel *serverNameLabel;
	QLineEdit *serverNameLineEdit;
	
	QPushButton *connectPushButton;	
	QPushButton *disConnectPushButton;

	QLabel *machCoordLabel;
	QLineEdit *machCoordLineEdit;

	QLabel *absCoordLabel;
	QLineEdit *absCoordLineEdit;

	QLabel *relCoordLabel;
	QLineEdit *relCoordLineEdit;

	QLabel *almInfoLabel;
	QLineEdit *almInfoLineEdit;

	QLabel *progStateLabel;
	QLineEdit *proStateLineEdit;

	QPushButton *refreshFileListPushButton;
	
	QPushButton *closePushButton;
	
private slots:
	void connectPushButtonClicked();	
	void disConnectPushButtonClicked();
	void updateBasicInformation();
	void refreshFileListPushButtonClicked();

};
#endif