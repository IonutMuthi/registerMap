#include "registermapvalues.hpp"
#include "regreadwrite.hpp"

RegisterMapValues::RegisterMapValues(struct iio_device *dev, QObject *parent)
	: QObject{parent}
{
	registerReadValues = new QMap<uint32_t, uint32_t>();
	regReadWrite = new RegReadWrite(dev);

	QObject::connect(this, &RegisterMapValues::requestWrite, regReadWrite, &RegReadWrite::write);
	QObject::connect(this, &RegisterMapValues::requestRead, regReadWrite, &RegReadWrite::read);
	QObject::connect(regReadWrite, &RegReadWrite::readDone, this, &RegisterMapValues::readDone);
	QObject::connect(regReadWrite, &RegReadWrite::writeSuccess, regReadWrite, &RegReadWrite::read);

	// ? USE DEBUG TO HANDLE CONSOLE LOGS
	//TODO TREAT SUCCESS MESSAGES
//	QObject::connect(regReadWrite, &RegReadWrite::writeSuccess, this, [=](uint32_t address){
//		readWriteFeedback->setText(readWriteFeedback->text() + "\n "
//					   + "Write value to register " + QString::number( address,16) + " sucessfully" );
//		Q_EMIT requestRead("0x" + QString::number( address,16));
//	});

//	QObject::connect(regReadWrite, &RegReadWrite::writeError, this, [=](const char *err){
//		readWriteFeedback->setText(readWriteFeedback->text() + "\n "
//					   + "Write value to register " + err);
//	});

//	QObject::connect(regReadWrite, &RegReadWrite::readError, this, [=](const char *err){
//		readWriteFeedback->setText(readWriteFeedback->text() + "\n "
//					   + "Read reg value is : " + err);
//	});

}

RegisterMapValues::~RegisterMapValues()
{
	delete registerReadValues;
	delete regReadWrite;
}

void RegisterMapValues::readDone(uint32_t address, uint32_t value)
{
	registerReadValues->insert(address,value);
	Q_EMIT registerValueChanged(address, value);
}

uint32_t RegisterMapValues::getValueOfRegister(uint32_t address)
{
	return registerReadValues->value(address);
}
