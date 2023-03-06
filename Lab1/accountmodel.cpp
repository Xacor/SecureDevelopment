#include "accountmodel.h"

AccountModel::AccountModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

}
int AccountModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const AccountItem item = mList->items().at(index.row());
    switch (role) {
    case siteRole:
        return QVariant(item.site);
    case usernameRole:
        return QVariant(item.username);
    case passwordRole:
        return QVariant(item.password);
    case deletedRole:
        return QVariant(item.deleted);
    }

    return QVariant();
}

bool AccountModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    AccountItem item = mList->items().at(index.row());
    switch (role) {
    case siteRole:
        item.site = value.toString();
        break;
    case usernameRole:
        item.username = value.toString();
        break;
    case passwordRole:
        item.password = value.toString();
        break;
    case deletedRole:
        item.deleted = value.toBool();
        break;
    }
    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags AccountModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}


QHash<int, QByteArray> AccountModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[siteRole] = "site";
    names[usernameRole] = "username";
    names[passwordRole] = "password";
    names[deletedRole] = "deleted";

    return names;
}

AccountList *AccountModel::list() const
{
    return mList;
}

void AccountModel::setlist(AccountList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &AccountList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(mList, &AccountList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &AccountList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(mList, &AccountList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
