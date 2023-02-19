#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "xmlfilemanager.hpp"
#include "registermapcontroller.hpp"
#include <qdebug.h>
#include <iio.h>
#include <qboxlayout.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ctx = iio_create_context_from_uri("ip:192.168.2.1"); //("ip:127.0.0.1");

	if (!ctx) {
	    qDebug() << "Connection Error: No device available/connected to your PC.";
	}

	struct iio_device *dev = getIioDevice("ad9361-phy");

	RegisterMapController *regMap = new RegisterMapController(dev,"/home/ubuntu/Documents/RegmapUiDemo/ad9361-phy.xml");
	QVBoxLayout *layout  = new QVBoxLayout();
	layout->addWidget(regMap);

	this->ui->centralwidget->setLayout(layout);

}

struct iio_device* MainWindow::getIioDevice(const char *dev_name){
    auto deviceCount = iio_context_get_devices_count(ctx);

    for (int i = 0; i < deviceCount; i++) {
	iio_device *dev = iio_context_get_device(ctx, i);
	if (strcasecmp(iio_device_get_name(dev), dev_name) == 0) {
	    return dev;
	}
    }
    return nullptr;
}

MainWindow::~MainWindow()
{
	delete ui;
}

