#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H

#include <QFile>
#include <QObject>
#include <QVector>
#include <QTextStream>
struct Credentials {
    QString username;
    QString password;
};

struct AccountItem {
    QString site;
    QByteArray credentials;
    bool deleted = false;
};


// Модель данных
class AccountList : public QObject
{
    Q_OBJECT
public:
    explicit AccountList(QObject *parent = nullptr);
    AccountList(QString filePath);

    QVector<AccountItem> items() const;
    bool setItemAt(int index, const AccountItem &item);

    bool load();
    bool save();

//    QString decrypt(QString cText);
//    QString encrypt(QString pText);
    void appendItem(AccountItem item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void onAccountCreated(QString site, QString username, QString password);
    void removeItem();
    void onKeyGenerated(QByteArray key);
    void onCopyToClipboard(int id, int role);

private:
    QVector<AccountItem> m_items;
    QString file_path;
    QByteArray key;
};

#endif // ACCOUNTLIST_H
