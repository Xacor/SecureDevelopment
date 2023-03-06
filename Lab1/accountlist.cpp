#include <accountlist.h>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <CryptoController.h>

AccountList::AccountList(QObject *parent): QObject{parent}
{

}

AccountList::AccountList(QString file_path) : file_path(file_path)
{

}

QVector<AccountItem> AccountList::items() const
{
    return m_items;
}

bool AccountList::setItemAt(int index, const AccountItem &item)
{
    if (index < 0 || index >= m_items.size())
        return false;

    const AccountItem &oldItem = m_items.at(index);
    if (item.site == oldItem.site && item.username == oldItem.username && item.password == oldItem.password && item.deleted == oldItem.deleted)
        return false;

    m_items[index] = item;
    return true;
}

bool AccountList::load()
{
    QByteArray jsonBytes;
    CryptoController::DecryptFile(this->key, this->file_path, jsonBytes);

    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(jsonBytes, &err);

    if (json_doc.isNull()) {
        qDebug() <<"Error when parsing JSON:" <<err.errorString();
        return false;
    }

    if (!json_doc.isArray()) {
        qDebug() << "JSON is not array";
        return false;
    }

    QJsonArray jsonArray = json_doc.array();

    if  (jsonArray.isEmpty()) {
        qDebug() << "Array is empty";
        return false;
    }

    this->m_items.clear();

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

    for (int i = 0; i < this->m_items.count(); i++) {
        QJsonObject itemObject;
        itemObject["site"] = this->m_items.at(i).site;
        itemObject["username"] = this->m_items.at(i).username;
        itemObject["password"] = this->m_items.at(i).password;
        jsonArray.append(itemObject);
    }

    QJsonDocument jsonDoc(jsonArray);

//    if(!this->mFile.open(QIODevice::WriteOnly)){
//        qDebug()<<"Failed to open on write";
//        return false;
//    }
//    this->mFile.write(jsonDoc.toJson());
//    this->mFile.close();
    return true;
}

void AccountList::onAccountCreated(QString site, QString username, QString password)
{
    emit preItemAppended();

    AccountItem item;
    item.site = site;
    item.username = username;
    item.password = password;
    m_items.append(item);
    this->save();

    emit postItemAppended();
}

void AccountList::appendItem(AccountItem item, bool save)
{
    emit preItemAppended();

    m_items.append(item);
    if (save)
        this->save();

    emit postItemAppended();
}

void AccountList::removeItem()
{
    for (int i = 0; i < m_items.size();) {
        if (m_items.at(i).deleted) {
            emit preItemRemoved(i);

            m_items.removeAt(i);
            this->save();

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}

void AccountList::onKeyGenerated(QByteArray key)
{
    this->key = key;
    this->load();
}
