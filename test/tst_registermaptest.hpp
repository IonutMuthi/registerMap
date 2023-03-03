#ifndef TST_REGISTERMAPTEST_HPP
#define TST_REGISTERMAPTEST_HPP

#include <QObject>

class IRegisterWriteStrategy;
class IRegisterReadStrategy;
class TST_RegisterMapTest : public QObject
{
	Q_OBJECT
public:
	explicit TST_RegisterMapTest(QObject *parent = nullptr);
	void readIIOStrategy();
	void readFileStrategy();
	void read(IRegisterReadStrategy *strategy, uint32_t address, uint32_t expectedValue);

	void writeIIOStrategy();
	void writeFileStrategy();
	struct iio_device* getIioDevice(const char *dev_name);

};

#endif // TST_REGISTERMAPTEST_HPP
