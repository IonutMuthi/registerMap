#include "registerdetailedwidget.hpp"

#include <bitfielddetailedwidget.hpp>
#include <bitfielddetailedwidgetfactory.hpp>
#include <qboxlayout.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <registermodel.hpp>

RegisterDetailedWidget::RegisterDetailedWidget( RegisterModel *regModel, QWidget *parent)
	: QWidget{parent}
{

	QVBoxLayout *layout = new QVBoxLayout(this);
	setLayout(layout);
	description = new QLabel("Description : " + regModel->getDescription());

	layout->addWidget(description);

	QHBoxLayout *bitFieldsWidgetLayout = new QHBoxLayout();
	layout->addLayout(bitFieldsWidgetLayout);

	bitFieldList = new QVector<BitFieldDetailedWidget*>();

	BitFieldDetailedWidgetFactory bitFieldDetailedWidgetFactory;

	for (int i = regModel->getBitFields()->size() - 1; i >= 0; --i) {
		BitFieldDetailedWidget *bitFieldDetailedWidget = bitFieldDetailedWidgetFactory.buildWidget(regModel->getBitFields()->at(i));
		bitFieldsWidgetLayout->addWidget(bitFieldDetailedWidget, bitFieldDetailedWidget->getWidth());
		bitFieldList->push_back(bitFieldDetailedWidget);

		QObject::connect(bitFieldDetailedWidget, &BitFieldDetailedWidget::valueUpdated, this, [=](){
			Q_EMIT bitFieldValueChanged(getBitFieldsValue());
		});
	}
}

void RegisterDetailedWidget::updateBitFieldsValue(uint32_t value)
{
	int regOffset = 0;
	for (int i = bitFieldList->length() - 1; i >= 0; --i) {
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

QString RegisterDetailedWidget::getBitFieldsValue()
{
	QString val = "";
	for (int i = 0; i < bitFieldList->length(); ++i) {
		val += bitFieldList->at(i)->getValue();
	}
	bool ok;

	return QString::number(val.toInt(&ok,2),16);
}
