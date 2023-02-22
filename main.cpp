#include "mainwindow.hpp"
#include "logging_categories.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	SetScopyQDebugMessagePattern();
	QLoggingCategory::setFilterRules(""
//					 "*.debug=true\n"
					 "default=false"
//					  "ScanContextCollector.debug=true"
					 );

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
