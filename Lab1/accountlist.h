#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

#include <QObject>
#include <QVector>

struct AccountItem {
    QString site;
    QString username;
    QString password;
    bool deleted = false;
};

// Модель данных
class AccountList : public QObject
{
    Q_OBJECT
public:
    explicit AccountList(QObject *parent = nullptr);
    AccountList(QString *filepath);

    QVector<AccountItem> items() const;
    bool setItemAt(int index, const AccountItem &item);

    void read(const QString *filepath);
    void write(QJsonDocument &json) const;

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeItem();

private:
    QVector<AccountItem> mItems;
};

#endif // ACCOUNTLIST_H
