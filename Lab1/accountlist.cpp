#include "accountlist.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

AccountList::AccountList(QObject *parent): QObject{parent}
{

}

AccountList::AccountList(QString *filepath)
{
    this->read(filepath);
}

QVector<AccountItem> AccountList::items() const
{
    return mItems;
}

bool AccountList::setItemAt(int index, const AccountItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const AccountItem &oldItem = mItems.at(index);
    if (item.site == oldItem.site && item.username == oldItem.username && item.password == oldItem.password && item.deleted == oldItem.deleted)
        return false;

    mItems[index] = item;
    return true;
}

void AccountList::read(const QString *filepath)
{
    QFile file(*filepath);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open" ;
        return;
    }

    QTextStream fileText(&file);
    QString jsonString = fileText.readAll();
    file.close();

    QByteArray jsonBytes = jsonString.toLocal8Bit();
    QJsonDocument json =QJsonDocument::fromJson(jsonBytes);

    if (!json.isArray()) {
        qDebug() << "JSON is not array";
        return;
    }

    QJsonArray jsonArray = json.array();

    if  (jsonArray.isEmpty()) {
        qDebug() << "Array is empty";
        return;
    }

    for (int i = 0; i < jsonArray.count(); i++) {
        if (!jsonArray.at(i).isObject()) {
            qDebug() << "Not a JSON object";
            continue;
        }

        QJsonObject object = jsonArray.at(i).toObject();

        AccountItem item;

        if (object.contains("site") && object["site"].isString())
            item.site = object["site"].toString();

        if (object.contains("username") && object["username"].isString())
            item.username = object["username"].toString();

        if (object.contains("password") && object["password"].isString())
            item.password = object["password"].toString();

        this->mItems.append(item);

    }

}

void AccountList::appendItem()
{
    emit preItemAppended();

    AccountItem item;
    mItems.append(item);

    emit postItemAppended();
}

void AccountList::removeItem()
{
    for (int i = 0; i < mItems.size();) {
        if (mItems.at(i).deleted) {
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}
