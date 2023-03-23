#include "qguiapplication.h"
#include <accountlist.h>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <CryptoController.h>
#include <QClipboard>
#include <QTimer>

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
    if (item.site == oldItem.site && item.credentials == oldItem.credentials && item.deleted == oldItem.deleted)
        return false;

    m_items[index] = item;
    return true;
}

bool AccountList::load()
{
    QByteArray jsonBytes;
    CryptoController::DecryptFileW(this->key, this->file_path, jsonBytes);
    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(jsonBytes, &err);

    if (json_doc.isNull()) {
//        qDebug() <<"Error when parsing JSON:" <<err.errorString();
        return false;
    }

    if (!json_doc.isArray()) {
//        qDebug() << "JSON is not array";
        return false;
    }

    QJsonArray jsonArray = json_doc.array();

    this->m_items.clear();

    for (int i = 0; i < jsonArray.count(); i++) {
        if (!jsonArray.at(i).isObject()) {
//            qDebug() << "Not a JSON object";
            continue;
        }

        QJsonObject object = jsonArray.at(i).toObject();

        AccountItem item;

        if (object.contains("site") && object["site"].isString())
            item.site = object["site"].toString();

        if (object.contains("credentials") && object["credentials"].isString())
            item.credentials = object["credentials"].toString().toUtf8();

        this->appendItem(item);
    }


    return true;
}

bool AccountList::save()
{

    QJsonArray jsonArray;

    for (int i = 0; i < this->m_items.count(); i++) {
        QJsonObject itemObject;
        itemObject["site"] = this->m_items.at(i).site;
        itemObject["credentials"] = QString(this->m_items.at(i).credentials);
        jsonArray.append(itemObject);
    }

    QJsonDocument jsonDoc(jsonArray);
    QByteArray jsonBytes = jsonDoc.toJson();
    bool ok = CryptoController::EncryptFile(this->key, this->file_path, jsonBytes);

    return ok;
}

void AccountList::onAccountCreated(QString site, QString username, QString password)
{
    emit preItemAppended();

    AccountItem item;
    item.site = site;

    QJsonObject credentials;
    credentials["username"] = username;
    credentials["password"] = password;

    QJsonDocument jsonDoc(credentials);
    QByteArray bytes = jsonDoc.toJson();

    QByteArray enc_creds;
    CryptoController::EncryptCredentials(this->key, bytes, enc_creds);

    item.credentials = enc_creds;
    m_items.append(item);
    this->save();

    emit postItemAppended();
}

void AccountList::appendItem(AccountItem item)
{
    emit preItemAppended();

    m_items.append(item);


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

void AccountList::onCopyToClipboard(int id, int role)
{
    QByteArray encrypted_cred = this->m_items.at(id).credentials;
    QByteArray decrypted_cred;

    CryptoController::DecryptCredentials(this->key, encrypted_cred, decrypted_cred);

    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(decrypted_cred, &err);

    if (json_doc.isNull()) {
        //qDebug() <<"Error when parsing JSON:" <<err.errorString();
    }

    QJsonObject object = json_doc.object();
    Credentials creds;

    if (object.contains("username") && object["username"].isString())
        creds.username = object["username"].toString();

    if (object.contains("password") && object["password"].isString())
        creds.password = object["password"].toString();


    QClipboard *clipboard = QGuiApplication::clipboard();
    if (role == 1)
        clipboard->setText(creds.username);
    else
        clipboard->setText(creds.password);
}
