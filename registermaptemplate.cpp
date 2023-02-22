#include "registermaptemplate.hpp"
#include "xmlfilemanager.hpp"
#include <QMap>
#include "registermodel.hpp"
#include "bitfieldmodel.hpp"

RegisterMapTemplate::RegisterMapTemplate(struct iio_device *dev, QString filePath, QObject *parent)
	: QObject{parent}
{
	XmlFileManager xmlFileManager(dev, filePath);
	registerList = xmlFileManager.getAllRegisters();

}

RegisterMapTemplate::~RegisterMapTemplate()
{
	delete registerList;
}

QMap<uint32_t, RegisterModel *> *RegisterMapTemplate::getRegisterList() const
{
	return registerList;
}

RegisterModel *RegisterMapTemplate::getRegisterTemplate(uint32_t address)
{
	return registerList->value(address);
}

void RegisterMapTemplate::setRegisterList(QMap<uint32_t, RegisterModel *> *newRegisterList)
{
	registerList = newRegisterList;
}

void RegisterMapTemplate::searchForRegisters(QString searchParam)
{
	if (searchParam.isEmpty()) {
		Q_EMIT searchDone(registerList->keys());
	} else {

		QList<uint32_t> result;

		QMap<uint32_t, RegisterModel*>::iterator mapIterator;
		for (mapIterator = registerList->begin(); mapIterator != registerList->end(); ++mapIterator) {
			QString address = QString::number(mapIterator.key(),16);
			if (address.contains(searchParam) || mapIterator.value()->getName().contains(searchParam) ){
				result.push_back(mapIterator.key());
			} else {
				for (int i = 0 ; i < mapIterator.value()->getBitFields()->size(); ++i){
					if (mapIterator.value()->getBitFields()->at(i)->getName().toLower().contains(searchParam) ||
					    mapIterator.value()->getBitFields()->at(i)->getDescription().toLower().contains(searchParam) ) {

						result.push_back(mapIterator.key());
						break;
					}
				}
			}
		}

		Q_EMIT searchDone(result);
	}
}
