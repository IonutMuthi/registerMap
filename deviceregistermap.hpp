#ifndef DEVICEREGISTERMAP_HPP
#define DEVICEREGISTERMAP_HPP

#include <QMap>
#include <QObject>
#include <QWidget>

class QVBoxLayout;
class RegisterModel;
class BitFieldsDetailedWidget;
class RegisterController;
class RegisterMapValues;
class RegisterMapTemplate;
class SearchBarWidget;
class RegisterMapTable;

class DeviceRegisterMap : public QWidget
{
	Q_OBJECT
public:
	explicit DeviceRegisterMap(struct iio_device* dev, QString path,  QWidget *parent = nullptr);
	~DeviceRegisterMap();

	void registerChanged(RegisterModel *regModel, uint32_t value);

private:
	QVBoxLayout *layout;
	RegisterMapTemplate *registerMapTemplate;
	RegisterMapValues *registerMapValues;
	RegisterController *registerController;

	SearchBarWidget *searchBarWidget;
	RegisterMapTable *registerMapTableWidget;

	BitFieldsDetailedWidget *bitFieldsDetailedWidget = nullptr;
signals:

};

#endif // DEVICEREGISTERMAP_HPP
