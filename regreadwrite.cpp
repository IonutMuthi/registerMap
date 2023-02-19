#include "regreadwrite.hpp"
#include <iio.h>
#include <qdebug.h>

RegReadWrite::RegReadWrite(struct iio_device *dev, QObject *parent)
	: dev(dev),
	  QObject{parent}
{}

RegReadWrite::~RegReadWrite()
{}

void RegReadWrite::read(uint32_t address)
{
	uint32_t reg_val;

	ssize_t read = iio_device_reg_read(dev, address, &reg_val);
	if (read < 0) {
		Q_EMIT readError("device read error");
	} else {
		Q_EMIT readDone(address,reg_val);
	}
}

void RegReadWrite::write(uint32_t address, uint32_t val)
{
	ssize_t write = iio_device_reg_write(dev, address, val);
	if (write < 0) {
		Q_EMIT writeError("device write err");
	} else {
		Q_EMIT writeSuccess(address);
	}
}
