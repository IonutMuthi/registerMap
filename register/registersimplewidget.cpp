#include "bitfieldsimplewidget.hpp"
#include "registersimplewidget.hpp"

#include <QLabel>
#include <qboxlayout.h>
#include <qcoreevent.h>

#include <qdebug.h>


RegisterSimpleWidget::RegisterSimpleWidget(QString name, QString address, QString description,
					   QString notes, QVector<BitFieldSimpleWidget *> *bitFields, QWidget *parent)
	:bitFields(bitFields),
	  address(address)
{
	installEventFilter(this);

	setMinimumWidth(10);
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
	setStyleSheet("border: 1px solid black");

	QHBoxLayout *layout = new QHBoxLayout();
	setLayout(layout);

	QVBoxLayout *regBaseInfo = new QVBoxLayout();
	regBaseInfo->addWidget(new QLabel(address + " " + name));
	value = new QLabel("Value: Not Read");
	regBaseInfo->addWidget(value);

	layout->addLayout(regBaseInfo,1);

	QHBoxLayout *bitFieldsWidgetLayout = new QHBoxLayout();
	// add bitfield widgets
	for (int i = bitFields->length() - 1; i >= 0; i--) {
		bitFieldsWidgetLayout->addWidget(bitFields->at(i), bitFields->at(i)->getWidth());
	}
	layout->addLayout(bitFieldsWidgetLayout,8);

	QString toolTip = "Name : " + name + "\n"
			+ "Address : " + address + "\n"
			+ "Description : " + description + "\n"
			+ "Notes : " + notes + "\n" ;

	setToolTip(toolTip);
}

RegisterSimpleWidget::~RegisterSimpleWidget()
{
	delete value;
}

void RegisterSimpleWidget::valueUpdated(uint32_t value)
{
	int regOffset = 0;
	for (int i = 0; i < bitFields->length(); ++i) {
		bitFields->at(i)->blockSignals(true);

		int width = bitFields->at(i)->getWidth();
		int bfVal = ( ((1 << (regOffset + width) ) - 1 ) & value) >> regOffset;
		QString bitFieldValue =  QString::number(bfVal,16);
		if (bitFieldValue.size() < width) {
			QString aux = "";
			while ( aux.size() < (width - bitFieldValue.size() )) {
				aux += "0";
			}
			bitFieldValue = aux + bitFieldValue;
		}
		bitFields->at(i)->updateValue(bitFieldValue);
		regOffset += width;

		bitFields->at(i)->blockSignals(false);
	}

	this->value->setText(QString::number(value,16));
}

bool RegisterSimpleWidget::eventFilter(QObject *object, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick) {
		bool ok;
		Q_EMIT registerSelected(address.toInt(&ok,16));
	}
	return QWidget::eventFilter(object,event);
}

