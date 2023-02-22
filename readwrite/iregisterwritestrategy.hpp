#ifndef IREGISTERWRITESTRATEGY_HPP
#define IREGISTERWRITESTRATEGY_HPP

#include <QObject>

class IRegisterWriteStrategy : public QObject
{
	Q_OBJECT
public:
	virtual void write(uint32_t address, uint32_t val) = 0;

signals:
	void writeError(const char *err);
	void writeSuccess(uint32_t address);
};

#endif // IREGISTERWRITESTRATEGY_HPP
