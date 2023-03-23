#include "accountfilterproxymodel.h"

AccountFilterProxyModel::AccountFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->setDynamicSortFilter(true);
}

AccountFilterProxyModel::AccountFilterProxyModel(QAbstractItemModel *source, int role)
{
    this->setSourceModel(source);
    this->setFilterRole(role);
    this->setDynamicSortFilter(true);
}

void AccountFilterProxyModel::onSearchInputChanged(QString input)
{
    this->setFilterFixedString(input);
}
