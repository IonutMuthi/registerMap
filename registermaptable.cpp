#include "registermaptable.hpp"
#include "verticalscrollarea.hpp"

#include <QLineEdit>
#include <qboxlayout.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <registermodel.hpp>
#include <registersimplewidget.hpp>
#include <registersimplewidgetfactory.hpp>

RegisterMapTable::RegisterMapTable(QMap<uint32_t, RegisterModel *> *registerModels, QWidget *parent)
	: QWidget{parent}
{
	layout = new QVBoxLayout();
	setLayout(layout);

	scrollArea = new VerticalScrollArea();
	registerTableLayout = new QVBoxLayout();
	registerTable = new QWidget();
	registerTable->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
	registerTable->setLayout(registerTableLayout);


	RegisterSimpleWidgetFactory registerSimpleWidgetFactory;
	registersMap = new QMap<uint32_t, RegisterSimpleWidget*>();
	QMap<uint32_t, RegisterModel *>::iterator mapIterator;

	for (mapIterator = registerModels->begin(); mapIterator != registerModels->end(); ++mapIterator) {
		RegisterSimpleWidget *registerSimpleWidget = registerSimpleWidgetFactory.buildWidget(mapIterator.value());
		QObject::connect(registerSimpleWidget, &RegisterSimpleWidget::registerSelected, this, &RegisterMapTable::registerSelected);
		registersMap->insert(mapIterator.key(), registerSimpleWidget);
		registerTableLayout->addWidget(registerSimpleWidget);
	}

	scrollArea->setWidget(registerTable);
	layout->addWidget(scrollArea);
}

RegisterMapTable::~RegisterMapTable()
{
	delete layout;
	delete scrollArea;

	delete registersMap;
}

void RegisterMapTable::valueUpdated(uint32_t address, uint32_t value)
{
	if (registersMap->contains(address)) {
		registersMap->value(address)->valueUpdated(value);
	} else {
		//TODO ADD DEBUG MESSAGE " no register was found for address X "
	}
}

void RegisterMapTable::setFilters(QList<uint32_t> filters)
{
	hideAll();
	foreach (uint32_t address, filters) {
		registersMap->value(address)->show();
	}
}

void RegisterMapTable::hideAll()
{
	QMap<uint32_t, RegisterSimpleWidget*>::iterator mapIterator;
	for (mapIterator = registersMap->begin(); mapIterator != registersMap->end(); ++mapIterator) {
		mapIterator.value()->hide();
	}
}

void RegisterMapTable::showAll()
{
	QMap<uint32_t, RegisterSimpleWidget*>::iterator mapIterator;
	for (mapIterator = registersMap->begin(); mapIterator != registersMap->end(); ++mapIterator) {
		mapIterator.value()->show();
	}
}
