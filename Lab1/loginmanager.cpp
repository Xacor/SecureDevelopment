#include "loginmanager.h"
#include "cryptocontroller.h"

#include <QFile>

LoginManager::LoginManager(QObject *parent) : QObject(parent)
{
}

LoginManager::LoginManager(QString &file_path)
{
    this->file_path = file_path;
}

bool LoginManager::CheckPassword(QByteArray &key) {
    QFile file(this->file_path);
    // Создать файл, если его нет
    if (file.open(QFile::NewOnly)) {
        file.close();
        return true;
    }

    QByteArray *buff = new QByteArray;
    bool ok = CryptoController::DecryptFile(key, this->file_path, *buff);

    delete buff;
    return ok;
}

void LoginManager::onLogIn(QString password) {
    QByteArray key = CryptoController::GenerateKey(password.toUtf8());
    bool ok = this->CheckPassword(key);
    emit pwdChecked(ok);

    if (ok) emit keyGenerated(key);
}
