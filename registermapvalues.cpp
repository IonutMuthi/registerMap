#include "registermapvalues.hpp"
#include "regreadwrite.hpp"
#include "readwrite/iregisterreadstrategy.hpp"
#include "readwrite/iregisterwritestrategy.hpp"

RegisterMapValues::RegisterMapValues(IRegisterReadStrategy *readStrategy, IRegisterWriteStrategy *writeStrategy, QObject *parent)
	: QObject{parent}
{

	this->readStrategy = readStrategy;
	QObject::connect(this, &RegisterMapValues::requestRead, readStrategy, &IRegisterReadStrategy::read);
	QObject::connect(readStrategy, &IRegisterReadStrategy::readDone, this, &RegisterMapValues::readDone);

	this->writeStrategy = writeStrategy;
	QObject::connect(this, &RegisterMapValues::requestWrite, writeStrategy, &IRegisterWriteStrategy::write);
	QObject::connect(writeStrategy, &IRegisterWriteStrategy::writeSuccess, readStrategy, &IRegisterReadStrategy::read);

	registerReadValues = new QMap<uint32_t, uint32_t>();
}

RegisterMapValues::~RegisterMapValues()
{
	delete registerReadValues;
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
