#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

#include <QObject>
#include <QVector>

struct AccountItem {
    QString site;
    QString username;
    QString password;
    bool deleted;
};

class AccountList : public QObject
{
    Q_OBJECT
public:
    explicit AccountList(QObject *parent = nullptr);

    QVector<AccountItem> items() const;

    bool setItemAt(int index, const AccountItem &item);

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
