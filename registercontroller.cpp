#include "bitfieldsimplewidget.hpp"
#include "bitfielddetailedwidget.hpp"
#include "registercontroller.hpp"
#include "registermodel.hpp"
#include "bitfieldmodel.hpp"
#include "registersimplewidget.hpp"
#include "qtextspinbox.hpp"
#include "registermaptable.hpp"

#include <QVBoxLayout>
#include <bitfielddetailedwidgetfactory.hpp>
#include <bitfieldsdetailedwidget.hpp>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qdebug.h>
#include <QPushButton>

RegisterController::RegisterController(QMap<uint32_t, RegisterModel *> *registerModelList, QWidget *parent)
	: QWidget{parent}
{
	layout= new QVBoxLayout();
	setLayout(layout);

	registerMapTableWidget = new RegisterMapTable(registerModelList);
	layout->addWidget(registerMapTableWidget);

	QObject::connect(registerMapTableWidget, &RegisterMapTable::registerSelected, this, &RegisterController::registerAddressChanged);
	QObject::connect(registerMapTableWidget, &RegisterMapTable::requestSearch, this, &RegisterController::requestSearch);
	QObject::connect(this, &RegisterController::searchFinished, registerMapTableWidget, &RegisterMapTable::showSearchResults);


	regValue = new QLineEdit(this);
	regValue->setText("Not Read");


	// make address a spinbox with custom value for custom hexa values ?
	QHBoxLayout *addressLayout = new QHBoxLayout();
	addressLayout->addWidget(new QLabel("Address: "));
	addressPicker = new QTextSpinBox();

	QList<QString> *values = new QList<QString>();
	foreach (uint32_t addr , registerModelList->keys()) {
		values->push_back(QString::number(addr,16));
	}

	addressPicker->setValues(values);

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
	delete registerMapTableWidget;
}

void RegisterController::registerChanged(RegisterModel *regModel, uint32_t value)
{
	if (!addressChanged) {
		//TODO CHECK WHY IT DOES NOT LIKE 0 AS PARAMETER
		qDebug() << "TEST ADDRESS TRY TO SELECT " << regModel->getAddress();
		qDebug() << "TEST ADDRESS " << addressPicker->value();
		addressPicker->setValue(regModel->getAddress());
		qDebug() << "TEST ADDRESS " << addressPicker->value();

	} else {
		addressChanged = false;
	}

	if (bitFieldsDetailedWidget) delete bitFieldsDetailedWidget;

	bitFieldsDetailedWidget = new BitFieldsDetailedWidget(regModel->getBitFields());
	layout->addWidget(bitFieldsDetailedWidget);

	if (value) {
		regValue->setText(QString::number(value,16));
		bitFieldsDetailedWidget->updateBitFieldsValue(value);
	}

	QObject::connect(bitFieldsDetailedWidget, &BitFieldsDetailedWidget::bitFieldValueChanged, this, [=](QString val) {
		regValue->setText(val);
	});

	QObject::connect(regValue, &QLineEdit::textChanged, this, [=](QString val){
		bool ok;
		bitFieldsDetailedWidget->updateBitFieldsValue(val.toUInt(&ok,16));
	});


}

void RegisterController::registerValueChanged(uint32_t address, uint32_t value)
{
	registerMapTableWidget->valueUpdated(address, value);
	regValue->setText(QString::number(value,16));
	bitFieldsDetailedWidget->updateBitFieldsValue(value);
}

