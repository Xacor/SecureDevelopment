#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QAbstractListModel>
#include <accountlist.h>

class AccountModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(AccountList *list READ list WRITE setlist /*NOTIFY listChanged*/)
public:
    explicit AccountModel(QObject *parent = nullptr);

    enum {
        siteRole,
        usernameRole,
        passwordRole,
        deletedRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    AccountList *list() const;
    void setlist(AccountList *list);

private:
    AccountList *mList;
};

#endif // ACCOUNTMODEL_H
