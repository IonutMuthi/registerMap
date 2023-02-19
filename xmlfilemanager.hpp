#ifndef XMLFILEMANAGER_HPP
#define XMLFILEMANAGER_HPP

#include <QObject>

class QDomElement;
class RegisterModel;
class BitFieldModel;
class QString;

class XmlFileManager: public QObject
{
	Q_OBJECT

public:
	XmlFileManager( struct iio_device *dev, QString filePath);

	QList<QString>* getAllAddresses();
	QMap<uint32_t, RegisterModel*> *getAllRegisters();
	RegisterModel* getRegAtAddress(QString addr);
	RegisterModel* getRegister(QDomElement reg);
	void getRegMapData(QString addr);
	QVector<BitFieldModel*> *getBitFields(QString regAddr);
	QVector<BitFieldModel*> *getBitFieldsOfRegister(QDomElement reg);
	BitFieldModel *getBitField(QDomElement bitField);

private:
	QString filePath;
	struct iio_device *dev;
};

#endif // XMLFILEMANAGER_HPP
