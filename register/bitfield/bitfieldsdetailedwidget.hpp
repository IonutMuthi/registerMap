#ifndef BITFIELDSDETAILEDWIDGET_HPP
#define BITFIELDSDETAILEDWIDGET_HPP

#include <QWidget>

class BitFieldModel;
class BitFieldDetailedWidget;
class BitFieldsDetailedWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BitFieldsDetailedWidget( QVector<BitFieldModel*> *bitFields, QWidget *parent = nullptr);

	void updateBitFieldsValue(uint32_t value);
	QString getBitFieldsValue();

private:
	QVector<BitFieldDetailedWidget*> *bitFieldList;
signals:
	void bitFieldValueChanged(QString value);
};

#endif // BITFIELDSDETAILEDWIDGET_HPP
