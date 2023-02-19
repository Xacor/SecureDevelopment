#include "loginmanager.h"

LoginManager::LoginManager(QObject *parent) : QObject(parent)
{
}

bool LoginManager::CheckPassword(QString password) {
    return this->mPassword == password;
}

void LoginManager::onLogIn(QString password) {
    bool ok = this->CheckPassword(password);
    emit pwdChecked(ok);
}
