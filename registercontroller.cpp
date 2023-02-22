#include "bitfieldsimplewidget.hpp"
#include "bitfielddetailedwidget.hpp"
#include "registercontroller.hpp"
#include "registermodel.hpp"
#include "bitfieldmodel.hpp"
#include "registersimplewidget.hpp"
#include "qtextspinbox.hpp"

#include <QVBoxLayout>
#include <bitfielddetailedwidgetfactory.hpp>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qdebug.h>
#include <QPushButton>

RegisterController::RegisterController(QWidget *parent)
	: QWidget{parent}
{
	layout= new QVBoxLayout();
	setLayout(layout);

	regValue = new QLineEdit(this);
	regValue->setText("Not Read");
	QObject::connect(regValue, &QLineEdit::textChanged, this, &RegisterController::valueChanged);

	// make address a spinbox with custom value for custom hexa values ?
	QHBoxLayout *addressLayout = new QHBoxLayout();
	addressLayout->addWidget(new QLabel("Address: "));
	addressPicker = new QTextSpinBox();

	QObject::connect(addressPicker, &QTextSpinBox::textChanged, this, [=](QString address){
		addressChanged = true;
		bool ok;
		Q_EMIT	registerAddressChanged(address.toInt(&ok,16));
	});

	addressLayout->addWidget(addressPicker);

	QHBoxLayout *valueLayout = new QHBoxLayout();
	valueLayout->addWidget(new QLabel("Value: "));
	valueLayout->addWidget(regValue);


	QHBoxLayout *buttonsLayout = new QHBoxLayout();
	readButton = new QPushButton("Read");
	//request read
	QObject::connect( readButton, &QPushButton::clicked, this , [=](){
		bool ok;
		Q_EMIT requestRead(addressPicker->text().toInt(&ok,16));
	});


	writeButton = new QPushButton("Write");
	//request write on register
	QObject::connect( writeButton, &QPushButton::clicked, this, [=](){
		bool ok;
		Q_EMIT requestWrite(addressPicker->text().toInt(&ok,16), regValue->text().toInt(&ok,16));
	});

	description = new QLabel("Description : ");

	buttonsLayout->addWidget(readButton);
	buttonsLayout->addWidget(writeButton);

	layout->addLayout(addressLayout);
	layout->addLayout(valueLayout);
	layout->addLayout(buttonsLayout);

	layout->addWidget(description);
}

RegisterController::~RegisterController()
{
	delete layout;
	delete regValue;
	delete readButton;
	delete writeButton;
	delete description;
}

void RegisterController::registerChanged(RegisterModel *regModel, uint32_t value)
{
	if (!addressChanged) {
		addressPicker->setValue(regModel->getAddress());
	} else {
		addressChanged = false;
	}

	if (value) {
		regValue->setText(QString::number(value,16));
	}
}

void RegisterController::registerValueChanged(QString value)
{
	regValue->setText(value);
}

void RegisterController::setAddressRange(QList<uint32_t> val)
{
	QList<QString> *values = new QList<QString>();
	foreach (uint32_t addr , val) {
		values->push_back(QString::number(addr,16));
	}

	addressPicker->setValues(values);
	addressPicker->setMinimum(0);
}

