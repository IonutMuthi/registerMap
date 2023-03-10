#ifndef REGISTERMAPVALUES_HPP
#define REGISTERMAPVALUES_HPP

#include <QObject>
#include <QMap>

class IRegisterWriteStrategy;
class IRegisterReadStrategy;
class RegReadWrite;
class RegisterMapValues : public QObject
{
	Q_OBJECT
public:
	explicit RegisterMapValues(QObject *parent = nullptr);
	~RegisterMapValues();


	QMap<uint32_t, uint32_t> *registerReadValues;

	void readDone(uint32_t address, uint32_t value);
	uint32_t getValueOfRegister(uint32_t address);
	void setReadStrategy(IRegisterReadStrategy *readStrategy);
	void setWriteStrategy(IRegisterWriteStrategy *writeStrategy);

	IRegisterReadStrategy *getReadStrategy() const;

	IRegisterWriteStrategy *getWriteStrategy() const;

	QMap<uint32_t, uint32_t> *getRegisterReadValues() const;
	bool hasValue(uint32_t address);

Q_SIGNALS:
	void registerValueChanged(uint32_t address, uint32_t value);
	void requestRead(uint32_t address);
	void requestWrite(uint32_t address, uint32_t value);

private:
	IRegisterReadStrategy *readStrategy = nullptr;
	IRegisterWriteStrategy *writeStrategy = nullptr;
	QMetaObject::Connection m_readConnection;
	QMetaObject::Connection writeConnection;
};

#endif // REGISTERMAPVALUES_HPP
