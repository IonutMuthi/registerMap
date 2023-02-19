#include "bitfieldsimplewidget.hpp"
#include "bitfieldsimplewidgetfactory.hpp"
#include "registermodel.hpp"
#include "registersimplewidget.hpp"
#include "registersimplewidgetfactory.hpp"

RegisterSimpleWidgetFactory::RegisterSimpleWidgetFactory(QObject *parent)
	: QObject{parent}
{ }

RegisterSimpleWidget *RegisterSimpleWidgetFactory::buildWidget(RegisterModel *model)
{
	QVector<BitFieldSimpleWidget*> *bitFields = new QVector<BitFieldSimpleWidget*>;

	BitFieldSimpleWidgetFactory bitFieldSimpleWidgetFactory;
	for (int i = 0 ; i < model->getBitFields()->size(); ++i) {
		bitFields->push_back(bitFieldSimpleWidgetFactory.buildWidget(model->getBitFields()->at(i)));
	}

	return new RegisterSimpleWidget(model->getName(),
					QString::number(model->getAddress(),16),
					model->getDescription(),
					model->getNotes(),
					bitFields) ;
}
