#ifndef BITFIELDSIMPLEWIDGET_HPP
#define BITFIELDSIMPLEWIDGET_HPP

#include <QWidget>

class QVBoxLayout;
class QLabel;
class BitFieldSimpleWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BitFieldSimpleWidget(QString name,
				      int defaultValue,
				      QString description,
				      int width,
				      QString notes,
				      int regOffset,
				      QWidget *parent = nullptr);

	~BitFieldSimpleWidget();
	void updateValue(QString newValue);
	int getWidth() const;

private:
	QVBoxLayout *layout;
	QLabel *value;
	int width;
signals:

};

#endif // BITFIELDSIMPLEWIDGET_HPP
