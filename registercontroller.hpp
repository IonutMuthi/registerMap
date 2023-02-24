#ifndef REGISTERCONTROLLER_HPP
#define REGISTERCONTROLLER_HPP

#include <QWidget>

class QTextSpinBox;
class QLabel;
class QPushButton;
class QLineEdit;
class QVBoxLayout;
class RegisterModel;

class RegisterController : public QWidget
{
	Q_OBJECT
public:
	explicit RegisterController(QWidget *parent = nullptr);

	~RegisterController();

	void registerChanged(RegisterModel *regModel, uint32_t value);
	void registerValueChanged(QString value);
	void setAddressRange(QList<uint32_t> val);

private:

	QVBoxLayout *layout;
	QLineEdit *regValue;
	QPushButton *readButton;
	QPushButton *writeButton;
	QTextSpinBox *addressPicker;
	bool addressChanged = false;

Q_SIGNALS:
	void requestRead(uint32_t address);
	void requestWrite(uint32_t address, uint32_t value);
	void registerAddressChanged(uint32_t address);
	void valueChanged(QString value);
};

#endif // REGISTERCONTROLLER_HPP
