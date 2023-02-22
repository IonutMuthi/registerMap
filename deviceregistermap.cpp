#include "registercontroller.hpp"
#include "deviceregistermap.hpp"

#include "registermapvalues.hpp"
#include "searchbarwidget.hpp"
#include "registermaptemplate.hpp"
#include "registermaptable.hpp"

#include <bitfieldsdetailedwidget.hpp>
#include <iio.h>
#include <qboxlayout.h>
#include "readwrite/iioregisterreadstrategy.hpp"
#include "readwrite/iioregisterwritestrategy.hpp"
#include "registermodel.hpp"

DeviceRegisterMap::DeviceRegisterMap(iio_device *dev, QString path,  QWidget *parent)
	: QWidget{parent}
{	
	layout = new QVBoxLayout();
	setLayout(layout);

	//TODO MOVE registerMapValues and registerMapTemplate as parameters
	IIORegisterReadStrategy *iioReadStrategy = new IIORegisterReadStrategy(dev);
	IIORegisterWriteStrategy *iioWriteStrategy = new IIORegisterWriteStrategy(dev);
	registerMapValues = new RegisterMapValues(iioReadStrategy,iioWriteStrategy);
	registerMapTemplate = new RegisterMapTemplate(dev, path);

	searchBarWidget = new SearchBarWidget();
	registerMapTableWidget = new RegisterMapTable(registerMapTemplate->getRegisterList());

	QObject::connect(searchBarWidget, &SearchBarWidget::requestSearch, registerMapTemplate, &RegisterMapTemplate::searchForRegisters);
	QObject::connect(registerMapTemplate, &RegisterMapTemplate::searchDone, registerMapTableWidget, &RegisterMapTable::setFilters);

	registerController = new RegisterController();
	registerController->setAddressRange(registerMapTemplate->getRegisterList()->keys());

	QObject::connect(registerMapTableWidget, &RegisterMapTable::registerSelected, this, [=](uint32_t address){
		registerController->registerChanged(registerMapTemplate->getRegisterList()->value(address),
						    registerMapValues->getValueOfRegister(address));
		registerChanged(registerMapTemplate->getRegisterList()->value(address),
				registerMapValues->getValueOfRegister(address));
	});


	layout->addWidget(searchBarWidget);
	layout->addWidget(registerMapTableWidget);


	QObject::connect(registerController, &RegisterController::registerAddressChanged, this , [=](uint32_t address){
		registerChanged(registerMapTemplate->getRegisterList()->value(address),
				registerMapValues->getValueOfRegister(address));
	});

	QObject::connect(registerController, &RegisterController::requestRead, registerMapValues, &RegisterMapValues::requestRead);
	QObject::connect(registerController, &RegisterController::requestWrite, registerMapValues, &RegisterMapValues::requestWrite);
	QObject::connect(registerMapValues, &RegisterMapValues::registerValueChanged, this, [=](uint32_t address, uint32_t value){
		registerMapTableWidget->valueUpdated(address, value);
		registerController->registerValueChanged(QString::number(value,16));
		bitFieldsDetailedWidget->updateBitFieldsValue(value);
	});

	layout->addWidget(registerController);

	registerChanged(registerMapTemplate->getRegisterList()->begin().value(),registerMapValues->getValueOfRegister(registerMapTemplate->getRegisterList()->begin().key()));
}

DeviceRegisterMap::~DeviceRegisterMap()
{
	delete layout;
	delete registerMapTemplate;
	delete registerMapValues;
	delete registerController;
	delete registerMapTableWidget;
	delete searchBarWidget;
	if (bitFieldsDetailedWidget) delete bitFieldsDetailedWidget;
}

void DeviceRegisterMap::registerChanged(RegisterModel *regModel, uint32_t value)
{
	if (bitFieldsDetailedWidget) delete bitFieldsDetailedWidget;

	bitFieldsDetailedWidget = new BitFieldsDetailedWidget(regModel->getBitFields());
	layout->addWidget(bitFieldsDetailedWidget);

	if (value) {
		bitFieldsDetailedWidget->updateBitFieldsValue(value);
	}

	QObject::connect(bitFieldsDetailedWidget, &BitFieldsDetailedWidget::bitFieldValueChanged, registerController, &RegisterController::registerValueChanged);

	QObject::connect(registerController, &RegisterController::valueChanged, this, [=](QString val){
		bool ok;
		bitFieldsDetailedWidget->updateBitFieldsValue(val.toUInt(&ok,16));
	});
}

