#include <QApplication>
#include "DlgNcMonDemo.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	DlgNcMonDemo *dlgNcMonDemo = new DlgNcMonDemo;
	dlgNcMonDemo->show();
	
	return app.exec();
}