
#include <QtGui>

#include "DlgNcMonDemo.h"

DlgNcMonDemo::DlgNcMonDemo(QWidget *parent) : QDialog(parent)
{	
	pMachMon = CreateJDMachMon();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateBasicInformation()));

	codec = QTextCodec::codecForLocale();
	
	serverNameLabel = new QLabel(codec->toUnicode("机床IP地址"));	
	serverNameLineEdit = new QLineEdit;
	serverNameLabel->setBuddy(serverNameLineEdit);
	
	connectPushButton = new QPushButton(codec->toUnicode("连接"));
	connect(connectPushButton, SIGNAL(clicked()), this, SLOT(connectPushButtonClicked()));
	
	disConnectPushButton = new QPushButton(codec->toUnicode("断开连接"));
	connect(disConnectPushButton, SIGNAL(clicked()), this, SLOT(disConnectPushButtonClicked()));

	machCoordLabel = new QLabel(codec->toUnicode("机床坐标"));
	machCoordLineEdit = new QLineEdit;
	machCoordLabel->setBuddy(machCoordLineEdit);

	absCoordLabel = new QLabel(codec->toUnicode("绝对坐标"));
	absCoordLineEdit = new QLineEdit;
	absCoordLabel->setBuddy(absCoordLineEdit);

	relCoordLabel = new QLabel(codec->toUnicode("相对坐标"));
	relCoordLineEdit = new QLineEdit;
	relCoordLabel->setBuddy(relCoordLineEdit);
	
	closePushButton = new QPushButton(codec->toUnicode("退出"));		
	connect(closePushButton, SIGNAL(clicked()), this, SLOT(close()));
	
	QHBoxLayout *layout1 = new QHBoxLayout;
	layout1->addWidget(serverNameLabel);
	layout1->addWidget(serverNameLineEdit);
	layout1->addWidget(connectPushButton);
	layout1->addWidget(disConnectPushButton);
	layout1->addStretch();

	QHBoxLayout *layout2 = new QHBoxLayout;
	layout2->addWidget(machCoordLabel);
	layout2->addWidget(machCoordLineEdit);
	layout2->addWidget(absCoordLabel);
	layout2->addWidget(absCoordLineEdit);
	layout2->addWidget(relCoordLabel);
	layout2->addWidget(relCoordLineEdit);

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(closePushButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(layout1);
	mainLayout->addLayout(layout2);
	mainLayout->addLayout(bottomLayout);
	
	setLayout(mainLayout);

}

DlgNcMonDemo::~DlgNcMonDemo()
{
	DeleteJDMachMon(pMachMon);
}

void DlgNcMonDemo::connectPushButtonClicked()
{	
	disConnectPushButtonClicked();

	if(ConnectJDMach(pMachMon, serverNameLineEdit->text().toStdString().c_str()))
	{
		QMessageBox::warning(this, "NcMonDemo", codec->toUnicode("连接成功"));
		
		timer->start(1200);

		refreshFileListPushButtonClicked();
	}
	else
	{
		QMessageBox::warning(this, "NcMonDemo", codec->toUnicode("连接失败"));	
	}

}

void DlgNcMonDemo::disConnectPushButtonClicked()
{
	if (IsConncect(pMachMon))
	{
		timer->stop();
		
		DisConnectJDMach(pMachMon);
	}
}

void DlgNcMonDemo::updateBasicInformation()
{
	double dMachCoord[3], dAbsCoord[3], dRelCoord[3];

	if (GetMachPos(pMachMon, dMachCoord, dAbsCoord, dRelCoord))
	{
		machCoordLineEdit->setText(QString("%1 %2 %3").arg(dMachCoord[0]).arg(dMachCoord[1]).arg(dMachCoord[2]));

		absCoordLineEdit->setText(QString("%1 %2 %3").arg(dAbsCoord[0]).arg(dAbsCoord[1]).arg(dAbsCoord[2]));

		relCoordLineEdit->setText(QString("%1 %2 %3").arg(dRelCoord[0]).arg(dRelCoord[1]).arg(dRelCoord[2]));
	}

	int nAlmInfo = 0;
	
	if (GetMachAlmInfo(pMachMon, &nAlmInfo))
	{
		enum NcAlmInfo
		{
			NCALM_NO,
			NCALM_EMG,
			NCALM_ERR,
			NCALM_UPS,
			NCALM_PROMPT
		};

		if (nAlmInfo == NCALM_NO)
		{
			almInfoLineEdit->setText(codec->toUnicode("无报警"));
		}
		else if (nAlmInfo == NCALM_EMG)
		{
			almInfoLineEdit->setText(codec->toUnicode("急停"));
		}
		else if (nAlmInfo == NCALM_ERR)
		{
			almInfoLineEdit->setText(codec->toUnicode("报警"));
		}
		else if (nAlmInfo == NCALM_UPS)
		{
			almInfoLineEdit->setText(codec->toUnicode("外部电源已掉电"));
		}
		else if (nAlmInfo == NCALM_PROMPT)
		{
			almInfoLineEdit->setText(codec->toUnicode("提示"));
		}
	}


}

void DlgNcMonDemo::refreshFileListPushButtonClicked()
{

}