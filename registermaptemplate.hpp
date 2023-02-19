#ifndef REGISTERMAPTEMPLATE_HPP
#define REGISTERMAPTEMPLATE_HPP

#include <QObject>

class RegisterModel;
class RegisterMapTemplate : public QObject
{
	Q_OBJECT
public:
	explicit RegisterMapTemplate(struct iio_device *dev, QString filePath, QObject *parent = nullptr);
	~RegisterMapTemplate();

	QMap<uint32_t, RegisterModel *> *getRegisterList() const;
	void setRegisterList(QMap<uint32_t, RegisterModel *> *newRegisterList);
	void searchForRegisters(QString searchParam);

private:
	QMap<uint32_t, RegisterModel*> *registerList;
signals:
	void searchDone(QList<uint32_t> searchResults);
};

#endif // REGISTERMAPTEMPLATE_HPP
