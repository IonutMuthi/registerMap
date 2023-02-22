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
	explicit RegisterMapValues(IRegisterReadStrategy *readStrategy, IRegisterWriteStrategy *writeStrategy, QObject *parent = nullptr);
	~RegisterMapValues();


	QMap<uint32_t, uint32_t> *registerReadValues;

	void readDone(uint32_t address, uint32_t value);
	uint32_t getValueOfRegister(uint32_t address);

signals:
	void registerValueChanged(uint32_t address, uint32_t value);
	void requestRead(uint32_t address);
	void requestWrite(uint32_t address, uint32_t value);

private:
	IRegisterReadStrategy *readStrategy;
	IRegisterWriteStrategy *writeStrategy;
};

#endif // REGISTERMAPVALUES_HPP
