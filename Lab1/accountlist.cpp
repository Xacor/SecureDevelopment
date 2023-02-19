#include "accountlist.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

AccountList::AccountList(QObject *parent): QObject{parent}
{

}

AccountList::AccountList(QString filePath) : mFile(filePath)
{

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

bool AccountList::load()
{

    //Возможно стоит читать построчно для экономии памяти
    if(!this->mFile.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open";
        return false;
    }
    QTextStream textStream(&this->mFile);
    QString jsonString = textStream.readAll();
    this->mFile.close();

    qDebug() << jsonString;

    QByteArray jsonBytes = jsonString.toLocal8Bit();
    QJsonDocument json =QJsonDocument::fromJson(jsonBytes);

    if (!json.isArray()) {
        qDebug() << "JSON is not array";
        return false;
    }

    QJsonArray jsonArray = json.array();

    if  (jsonArray.isEmpty()) {
        qDebug() << "Array is empty";
        return false;
    }

    this->mItems.clear();

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


        this->appendItem(item, false);
    }
    return true;
}

bool AccountList::save()
{

    QJsonArray jsonArray;

    for (int i = 0; i < this->mItems.count(); i++) {
        QJsonObject itemObject;
        itemObject["site"] = this->mItems.at(i).site;
        itemObject["username"] = this->mItems.at(i).username;
        itemObject["password"] = this->mItems.at(i).password;
        jsonArray.append(itemObject);
    }

    QJsonDocument jsonDoc(jsonArray);

    if(!this->mFile.open(QIODevice::WriteOnly)){
        qDebug()<<"Failed to open on write";
        return false;
    }
    this->mFile.write(jsonDoc.toJson());
    this->mFile.close();
    return true;
}

void AccountList::appendItem(QString site, QString username, QString password)
{
    emit preItemAppended();

    AccountItem item;
    item.site = site;
    item.username = username;
    item.password = password;
    mItems.append(item);
    this->save();

    emit postItemAppended();
}

void AccountList::appendItem(AccountItem item, bool save)
{
    emit preItemAppended();

    mItems.append(item);
    if (save)
        this->save();

    emit postItemAppended();
}

void AccountList::removeItem()
{
    for (int i = 0; i < mItems.size();) {
        if (mItems.at(i).deleted) {
            emit preItemRemoved(i);

            mItems.removeAt(i);
            this->save();

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}

void AccountList::onPwdChecked(bool ok)
{
    if (ok)
        this->load();

}
