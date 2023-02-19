#ifndef BITFIELDSIMPLEWIDGETFACTORY_HPP
#define BITFIELDSIMPLEWIDGETFACTORY_HPP

#include <QObject>

class BitFieldSimpleWidget;
class BitFieldModel;
class BitFieldSimpleWidgetFactory : public QObject
{
	Q_OBJECT
public:
	explicit BitFieldSimpleWidgetFactory(QObject *parent = nullptr);

	BitFieldSimpleWidget *buildWidget(BitFieldModel *model);
signals:

};

#endif // BITFIELDSIMPLEWIDGETFACTORY_HPP
