#ifndef REGISTERCONTROLLER_HPP
#define REGISTERCONTROLLER_HPP

#include <QWidget>

class RegisterMapTable;
class BitFieldsDetailedWidget;
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
	explicit RegisterController(QMap<uint32_t, RegisterModel *> *registerModelList, QWidget *parent = nullptr);

	~RegisterController();

	void registerChanged(RegisterModel *regModel, uint32_t value);
	void registerValueChanged(uint32_t address, uint32_t value);

private:

	QVBoxLayout *layout;
	QLineEdit *regValue;
	QPushButton *readButton;
	QPushButton *writeButton;
	QLabel *description;
	QTextSpinBox *addressPicker;
	BitFieldsDetailedWidget *bitFieldsDetailedWidget = nullptr;
	RegisterMapTable *registerMapTableWidget;

	bool addressChanged = false;

signals:
	void requestRead(uint32_t address);
	void requestWrite(uint32_t address, uint32_t value);
	void registerAddressChanged(uint32_t address);
	void requestSearch(QString searchParam);
	void searchFinished(QList<uint32_t> searchResult);
};

#endif // REGISTERCONTROLLER_HPP
