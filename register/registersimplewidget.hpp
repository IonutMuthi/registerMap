#ifndef REGISTERSIMPLEWIDGET_HPP
#define REGISTERSIMPLEWIDGET_HPP

#include <QWidget>

class QLabel;
class BitFieldSimpleWidget;
class QHBoxLayout;
class RegisterSimpleWidget : public QWidget
{
	Q_OBJECT
public:
	explicit RegisterSimpleWidget(QString name,
				      QString address,
				      QString description,
				      QString notes,
				      QVector<BitFieldSimpleWidget*> *bitFields,
				      QWidget *parent = nullptr);

	~RegisterSimpleWidget();


	void valueUpdated(uint32_t value);
private:
	QHBoxLayout *layout;
	QLabel *value;
	QVector<BitFieldSimpleWidget*> *bitFields;
	QString address;
protected:
    bool eventFilter(QObject *object, QEvent *event) override;
Q_SIGNALS:
    void registerSelected(uint32_t address);
};

#endif // REGISTERSIMPLEWIDGET_HPP
