#ifndef REGISTERMAPCONTROLLER_HPP
#define REGISTERMAPCONTROLLER_HPP

#include <QMap>
#include <QObject>
#include <QWidget>

class RegisterController;
class RegisterMapValues;
class RegisterMapTemplate;


class RegisterMapController : public QWidget
{
	Q_OBJECT
public:
	explicit RegisterMapController(struct iio_device* dev, QString path,  QWidget *parent = nullptr);
	~RegisterMapController();


private:
	RegisterMapTemplate *registerMapTemplate;
	RegisterMapValues *registerMapValues;
	RegisterController *registerController;
signals:
};

#endif // REGISTERMAPCONTROLLER_HPP
