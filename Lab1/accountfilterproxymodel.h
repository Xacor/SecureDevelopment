#ifndef ACCOUNTFILTERPROXYMODEL_H
#define ACCOUNTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

// Класс осуществляющий фильтрацию по вводу в поле
class AccountFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit AccountFilterProxyModel(QObject *parent = nullptr);
    AccountFilterProxyModel(QAbstractItemModel *source, int role);

public slots:
    void onSearchInputChanged(QString input);
};

#endif // ACCOUNTFILTERPROXYMODEL_H
