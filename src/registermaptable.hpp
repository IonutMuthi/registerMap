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

	void setMaxVisibleRows(int newMaxVisibleRows);

Q_SIGNALS:
	void registerSelected(uint32_t address);

private:

	int  m_maxVisibleRows = 10;
	QVBoxLayout *m_layout;
	QGridLayout *m_registerTableLayout;
	VerticalScrollArea  *m_scrollArea;
	QWidget *m_registerTable;
	QMap<uint32_t, RegisterModel *> *registerModels;

	QList<uint32_t> activeWidgets;
	QList<uint32_t>::iterator activeWidgetTop;
	QList<uint32_t>::iterator activeWidgetBottom;

	void scrollDown();
	void scrollUp();
	void populateMap();
	void generateWidget(RegisterModel *model);
};

#endif // REGISTERMAPTABLE_HPP
