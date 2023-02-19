#include "bitfieldsdetailedwidget.hpp"

#include <bitfielddetailedwidget.hpp>
#include <bitfielddetailedwidgetfactory.hpp>
#include <qboxlayout.h>

BitFieldsDetailedWidget::BitFieldsDetailedWidget( QVector<BitFieldModel*> *bitFields, QWidget *parent)
	: QWidget{parent}
{
	QHBoxLayout *bitFieldsWidgetLayout = new QHBoxLayout();
	setLayout(bitFieldsWidgetLayout);

	bitFieldList = new QVector<BitFieldDetailedWidget*>();

	BitFieldDetailedWidgetFactory bitFieldDetailedWidgetFactory;

	for (int i = 0 ; i < bitFields->size(); ++i) {
		BitFieldDetailedWidget *bitFieldDetailedWidget = bitFieldDetailedWidgetFactory.buildWidget(bitFields->at(i));
		bitFieldsWidgetLayout->addWidget(bitFieldDetailedWidget, bitFieldDetailedWidget->getWidth());
		bitFieldList->push_back(bitFieldDetailedWidget);

		QObject::connect(bitFieldDetailedWidget, &BitFieldDetailedWidget::valueUpdated, this, [=](){
			Q_EMIT bitFieldValueChanged(getBitFieldsValue());
		});
	}
}

void BitFieldsDetailedWidget::updateBitFieldsValue(uint32_t value)
{
	int regOffset = 0;
	for (int i = 0; i < bitFieldList->length(); ++i) {
		bitFieldList->at(i)->blockSignals(true);

		int width = bitFieldList->at(i)->getWidth();
		int bfVal = ( ((1 << (regOffset + width) ) - 1 ) & value) >> regOffset;
		QString bitFieldValue =  QString::number(bfVal,16);
		if (bitFieldValue.size() < width) {
			QString aux = "";
			while ( aux.size() < (width - bitFieldValue.size() )) {
				aux += "0";

			}
			bitFieldValue = aux + bitFieldValue;
		}
		bitFieldList->at(i)->updateValue(bitFieldValue);
		regOffset += width;

		bitFieldList->at(i)->blockSignals(false);
	}
}

QString BitFieldsDetailedWidget::getBitFieldsValue()
{
	QString val = "";
	for (int i = bitFieldList->length() - 1; i >= 0; --i) {
		val += bitFieldList->at(i)->getValue();
	}
	bool ok;

	return QString::number(val.toInt(&ok,2),16);
}
