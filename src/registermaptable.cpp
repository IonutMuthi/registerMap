#include "registermaptable.hpp"
#include "verticalscrollarea.hpp"
#include <QLineEdit>
#include <qboxlayout.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include "register/registersimplewidgetfactory.hpp"
#include "register/registermodel.hpp"
#include "register/bitfield/bitfieldmodel.hpp"
#include "register/registersimplewidget.hpp"
#include <QScrollBar>
#include <QDebug>
#include <QGridLayout>

RegisterMapTable::RegisterMapTable(QMap<uint32_t, RegisterModel *> *registerModels, QWidget *parent)
	: registerModels(registerModels),
	  QWidget{parent}
{
	layout = new QVBoxLayout();
	setLayout(layout);
	setStyleSheet("border: 1px solid black");
	scrollArea = new VerticalScrollArea();
	scrollArea->setTabletTracking(true);
	QObject::connect(scrollArea->verticalScrollBar(), &QAbstractSlider::valueChanged, this, [=](int value){
		qDebug() << "SCROLL ";
		if (value == scrollArea->verticalScrollBar()->minimum()) {
			scrollUp();
		}
		if (value == scrollArea->verticalScrollBar()->maximum()){
			scrollDown();
		}
	});
	//	registerTableLayout = new QVBoxLayout();
	registerTableLayout = new QGridLayout();
	registerTable = new QWidget();
	registerTable->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
	registerTable->setLayout(registerTableLayout);



	registersMap = new QMap<uint32_t, RegisterSimpleWidget*>();
	filteredRegisterModels = registerModels;
	populateMap();
	scrollArea->setWidget(registerTable);
	layout->addWidget(scrollArea);

	QObject::connect(this, &RegisterMapTable::filteredMapGenerated, this, &RegisterMapTable::populateMap);
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
	this->filters = filters;
	filterIterator= this->filters.begin();

	hideAll();
	filteredRegisterModels = applyFilter(filters);
	populateMap();
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
	//TODO SHOW FIRST X ELEMENTS
	QMap<uint32_t, RegisterSimpleWidget*>::iterator mapIterator;
	for (mapIterator = registersMap->begin(); mapIterator != registersMap->end(); ++mapIterator) {
		mapIterator.value()->show();
	}
}

void RegisterMapTable::scrollDown()
{
	// delete first
	// draw all row - 1
	// add widget at bottom
	qDebug() << "SCROLL DOWN";
	if (bottomWidgetIterator != filteredRegisterModels->end()) {

		registersMap->value(topWidgetIterator.key())->hide();

		if (registersMap->contains(bottomWidgetIterator.key())) {
			registersMap->value(bottomWidgetIterator.key())->show();
		}
		else {
			generateWidget(bottomWidgetIterator.value());
		}

		// TODO optimize
		scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum() - registersMap->value(bottomWidgetIterator.key())->sizeHint().height());
		topWidgetIterator++;
		bottomWidgetIterator++;
	}
}

void RegisterMapTable::scrollUp()
{
	// delete last
	// draw row +1
	// add at top
	qDebug() << "SCROLL UP";
	if (topWidgetIterator != filteredRegisterModels->begin()) {

		topWidgetIterator--;
		bottomWidgetIterator--;

		registersMap->value(bottomWidgetIterator.key())->hide();
		if (registersMap->contains(topWidgetIterator.key())) {
			registersMap->value(topWidgetIterator.key())->show();
		}
		else {
			generateWidget(topWidgetIterator.value());
		}

		// TODO optimize
		scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->minimum() + registersMap->value(topWidgetIterator.key())->sizeHint().height());
	}
}

void RegisterMapTable::populateMap()
{
	QMap<uint32_t, RegisterModel *>::iterator mapIterator = filteredRegisterModels->begin();
	int i = 0;
	//	if (filters.isEmpty()) {
	while ( i < MAX_ROW && mapIterator != filteredRegisterModels->end()) {
		if (registersMap->contains(mapIterator.key())) {
			registersMap->value(mapIterator.key())->show();
		}
		else {
			generateWidget(mapIterator.value());
		}
		++mapIterator;
		++i;
	}
	currentRowCount = i;
	bottomWidgetIterator = mapIterator;
	topWidgetIterator = filteredRegisterModels->begin();

	//	}
}

void RegisterMapTable::generateWidget(RegisterModel *model)
{
	RegisterSimpleWidgetFactory registerSimpleWidgetFactory;
	RegisterSimpleWidget *registerSimpleWidget = registerSimpleWidgetFactory.buildWidget(model);
	QObject::connect(registerSimpleWidget, &RegisterSimpleWidget::registerSelected, this, &RegisterMapTable::registerSelected);
	registersMap->insert(model->getAddress(), registerSimpleWidget);
	registerTableLayout->addWidget(registerSimpleWidget,currentRowCount,0);
	++currentRowCount;
}

QMap<uint32_t, RegisterModel*>* RegisterMapTable::applyFilter(QList<uint32_t> filters)
{
	QMap<uint32_t, RegisterModel*> *filteredRegisterModels = new QMap<uint32_t, RegisterModel*>();

	foreach (uint32_t address, filters) {
		filteredRegisterModels->insert(address,registerModels->value(address));
	}

	return filteredRegisterModels;

}
