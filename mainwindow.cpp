#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "xmlfilemanager.hpp"
#include "deviceregistermap.hpp"
#include "registermapvalues.hpp"
#include "registermaptemplate.hpp"
#include <qdebug.h>
#include <iio.h>
#include <qboxlayout.h>
#include "readwrite/iioregisterreadstrategy.hpp"
#include "readwrite/iioregisterwritestrategy.hpp"
#include "readwrite/fileregisterwritestrategy.hpp"
#include "readwrite/fileregisterreadstrategy.hpp"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ctx = iio_create_context_from_uri("ip:192.168.2.1");//("ip:127.0.0.1");

	if (!ctx) {
	    qDebug() << "Connection Error: No device available/connected to your PC.";
	}

	struct iio_device *dev = getIioDevice("ad9361-phy");


	IIORegisterReadStrategy *iioReadStrategy = new IIORegisterReadStrategy(dev);
	IIORegisterWriteStrategy *iioWriteStrategy = new IIORegisterWriteStrategy(dev);
	RegisterMapValues *registerMapValues = new RegisterMapValues();
	registerMapValues->setReadStrategy(iioReadStrategy);
	registerMapValues->setWriteStrategy(iioWriteStrategy);

//	FileRegisterReadStrategy *fileRegisterReadStrategy = new FileRegisterReadStrategy("/home/ubuntu/Documents/test.csv");
//	FileRegisterWriteStrategy *fileRegisterWriteStrategy = new FileRegisterWriteStrategy("/home/ubuntu/Documents/test.csv");
//	RegisterMapValues *registerMapValues = new RegisterMapValues(fileRegisterReadStrategy,fileRegisterWriteStrategy);


	RegisterMapTemplate *registerMapTemplate = new RegisterMapTemplate();

	XmlFileManager xmlFileManager(dev, "/home/ubuntu/Documents/RegmapUiDemo/ad9361-phy.xml");
	registerMapTemplate->setRegisterList(xmlFileManager.getAllRegisters());

	// each device register map will represent a tab
	DeviceRegisterMap *devRegMap = new DeviceRegisterMap(registerMapTemplate,registerMapValues);
	DeviceRegisterMap *regMap = new DeviceRegisterMap(nullptr,registerMapValues);

	QTabWidget *tabWidget = new QTabWidget;
	tabWidget->addTab(devRegMap, "ad9361");
	tabWidget->addTab(regMap, "test");


	QVBoxLayout *layout  = new QVBoxLayout();
	layout->addWidget(tabWidget);

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

