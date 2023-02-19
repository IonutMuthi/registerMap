#include "registercontroller.hpp"
#include "registermapcontroller.hpp"
#include "registermaptemplate.hpp"
#include "registermapvalues.hpp"

#include <iio.h>
#include <qboxlayout.h>

RegisterMapController::RegisterMapController(iio_device *dev, QString path,  QWidget *parent)
	: QWidget{parent}
{	
	QVBoxLayout *layout = new QVBoxLayout();
	setLayout(layout);

	registerMapTemplate = new RegisterMapTemplate(dev, path);
	registerMapValues = new RegisterMapValues(dev);
	registerController = new RegisterController(registerMapTemplate->getRegisterList());
	registerController->registerChanged(registerMapTemplate->getRegisterList()->begin().value(),registerMapValues->getValueOfRegister(registerMapTemplate->getRegisterList()->begin().key()));

	QObject::connect(registerController, &RegisterController::registerAddressChanged, this , [=](uint32_t address){
		registerController->registerChanged(registerMapTemplate->getRegisterList()->value(address),
						    registerMapValues->getValueOfRegister(address));
	});

	QObject::connect(registerController, &RegisterController::requestRead, registerMapValues, &RegisterMapValues::requestRead);
	QObject::connect(registerController, &RegisterController::requestWrite, registerMapValues, &RegisterMapValues::requestWrite);
	QObject::connect(registerMapValues, &RegisterMapValues::registerValueChanged, registerController, &RegisterController::registerValueChanged);
	QObject::connect(registerController, &RegisterController::requestSearch, registerMapTemplate, &RegisterMapTemplate::searchForRegisters);
	QObject::connect(registerMapTemplate, &RegisterMapTemplate::searchDone, registerController, &RegisterController::searchFinished);

	layout->addWidget(registerController);
}

RegisterMapController::~RegisterMapController()
{
	delete registerMapTemplate;
	delete registerMapValues;
	delete registerController;
}

