#ifndef REGISTERMAPTABLE_HPP
#define REGISTERMAPTABLE_HPP

#include <QWidget>
#include <QMap>

class QGridLayout;

class QVBoxLayout;
class RegisterModel;
class RegisterSimpleWidget;
class VerticalScrollArea;

class RegisterMapTable : public QWidget
{
	Q_OBJECT
public:
	explicit RegisterMapTable(QMap<uint32_t, RegisterModel*> *registerModels, QWidget *parent = nullptr);
	~RegisterMapTable();

	QMap<uint32_t, RegisterSimpleWidget*> *registersMap;

	void valueUpdated(uint32_t address, uint32_t value);
	void setFilters(QList<uint32_t> filters);
	void hideAll();
	void showAll();
Q_SIGNALS:
	void registerSelected(uint32_t address);
	void filteredMapGenerated(QMap<uint32_t, RegisterModel*> *registersMap);

private:
	QList<uint32_t> filters;
	QList<uint32_t>::iterator filterIterator;
	const int  MAX_ROW = 10;
	QVBoxLayout *layout;
	VerticalScrollArea  *scrollArea;
//	QVBoxLayout *registerTableLayout;
	QGridLayout *registerTableLayout;
	QWidget *registerTable;
	QMap<uint32_t, RegisterModel *> *registerModels;
	QMap<uint32_t, RegisterModel *> *filteredRegisterModels;
	void scrollDown();
	void scrollUp();
	int currentRowCount;
	QMap<uint32_t, RegisterModel *>::iterator bottomWidgetIterator;
	QMap<uint32_t, RegisterModel *>::iterator topWidgetIterator;
	void populateMap();

	void generateWidget(RegisterModel *model);
	QMap<uint32_t, RegisterModel *> *applyFilter(QList<uint32_t> filters);
};

#endif // REGISTERMAPTABLE_HPP
