#ifndef BITFIELDDETAILEDWIDGETFACTORY_HPP
#define BITFIELDDETAILEDWIDGETFACTORY_HPP

#include <QObject>

class BitFieldModel;
class BitFieldDetailedWidget;
class BitFieldDetailedWidgetFactory : public QObject
{
	Q_OBJECT
public:
	explicit BitFieldDetailedWidgetFactory(QObject *parent = nullptr);

	BitFieldDetailedWidget *buildWidget(BitFieldModel *model);
signals:

};

#endif // BITFIELDDETAILEDWIDGETFACTORY_HPP
