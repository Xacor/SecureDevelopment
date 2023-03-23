#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QAbstractListModel>
#include <accountlist.h>

// Представление данных.
// Несмотря на название, это класс отвечает только за рендер списка.
// Вся логика добавления, удаления, изменения реализована в <accountlist.h>
// https://doc.qt.io/qt-6/model-view-programming.html
class AccountModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(AccountList *list READ list WRITE setlist)
public:
    explicit AccountModel(QObject *parent = nullptr);

    enum {
        siteRole,
        credentialsRole,
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
