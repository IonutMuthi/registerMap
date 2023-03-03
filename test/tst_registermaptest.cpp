#include "tst_registermaptest.hpp"
#include "../src/readwrite/iregisterreadstrategy.hpp"
#include "../src/readwrite/iioregisterreadstrategy.hpp"
#include "../src/readwrite/fileregisterreadstrategy.hpp"
#include "../src/readwrite/iregisterwritestrategy.hpp"
#include "../src/readwrite/iioregisterwritestrategy.hpp"
#include "../src/readwrite/fileregisterwritestrategy.hpp"
#include <iio.h>
#include <QtTest/QTest>

TST_RegisterMapTest::TST_RegisterMapTest(QObject *parent)
	: QObject{parent}
{
}

void TST_RegisterMapTest::readIIOStrategy()
{
	struct iio_device *dev = getIioDevice("ad9361-phy");
	IIORegisterReadStrategy iioReadStrategy(dev);
	read(&iioReadStrategy,0,0);
}

void TST_RegisterMapTest::readFileStrategy()
{
	FileRegisterReadStrategy fileRegisterReadStrategy("./readWriteTest.csv");
	read(&fileRegisterReadStrategy,0,1);
}

void TST_RegisterMapTest::read(IRegisterReadStrategy *strategy, uint32_t address, uint32_t expectedValue)
{
	QObject::connect(strategy, &IRegisterReadStrategy::readDone, this, [=](uint32_t returnedAddress, uint32_t returnedValue){
		QVERIFY(expectedValue == returnedValue);
		QVERIFY(address == returnedAddress);
	});

	strategy->read(address);
}

void TST_RegisterMapTest::writeIIOStrategy()
{
	FileRegisterWriteStrategy fileRegisterWriteStrategy("./readWriteTest.csv");
	fileRegisterWriteStrategy.write(0,1);
	readFileStrategy();
}

void TST_RegisterMapTest::writeFileStrategy()
{
	struct iio_device *dev = getIioDevice("ad9361-phy");
	IIORegisterWriteStrategy iioWriteStrategy(dev);
	iioWriteStrategy.write(0,0);
	readIIOStrategy();

}

iio_device *TST_RegisterMapTest::getIioDevice(const char *dev_name)
{
	struct iio_context *ctx = iio_create_context_from_uri("ip:127.0.0.1");
	auto deviceCount = iio_context_get_devices_count(ctx);

	for (int i = 0; i < deviceCount; i++) {
		iio_device *dev = iio_context_get_device(ctx, i);
		if (strcasecmp(iio_device_get_name(dev), dev_name) == 0) {
			return dev;
		}
	}
	return nullptr;
}

