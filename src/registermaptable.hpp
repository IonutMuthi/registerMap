#ifndef REGISTERMAPTABLE_HPP
#define REGISTERMAPTABLE_HPP

#include <QWidget>
#include <QMap>


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


private:
	QVBoxLayout *layout;
	VerticalScrollArea  *scrollArea;
	QVBoxLayout *registerTableLayout;
	QWidget *registerTable;
};

#endif // REGISTERMAPTABLE_HPP
