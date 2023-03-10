#ifndef SEARCHBARWIDGET_HPP
#define SEARCHBARWIDGET_HPP

#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QLineEdit;
class SearchBarWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SearchBarWidget(QWidget *parent = nullptr);
	~SearchBarWidget();

Q_SIGNALS:
	void requestSearch(QString searchParam);
private:
	QLineEdit *searchBar;
	QPushButton *searchButton;
	QHBoxLayout *layout;
};

#endif // SEARCHBARWIDGET_HPP
