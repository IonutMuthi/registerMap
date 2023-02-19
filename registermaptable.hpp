#ifndef REGISTERMAPTABLE_HPP
#define REGISTERMAPTABLE_HPP

#include <QWidget>
#include <QMap>

class SearchBarWidget;
class QVBoxLayout;
class RegisterModel;
class RegisterSimpleWidget;
class VerticalScrollArea;
class RegisterMapTable : public QWidget
{
	Q_OBJECT
public:
	explicit RegisterMapTable(QMap<uint32_t, RegisterModel*> *registerModels,QWidget *parent = nullptr);
	~RegisterMapTable();

	QMap<uint32_t, RegisterSimpleWidget*> *registersMap;

	void valueUpdated(uint32_t address, uint32_t value);
	void showSearchResults(QList<uint32_t> searchResult);
	void hideAll();
	void showAll();
signals:
	void registerSelected(uint32_t address);
	void requestSearch(QString param);

private:
	QVBoxLayout *layout;
	SearchBarWidget *searchBarWidget;
	VerticalScrollArea  *scrollArea;
	QVBoxLayout *registerTableLayout;
	QWidget *registerTable;
};

#endif // REGISTERMAPTABLE_HPP
