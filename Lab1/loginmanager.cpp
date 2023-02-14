#include "loginmanager.h"
#include "qdebug.h"

LoginManager::LoginManager(QObject *parent) : QObject(parent)
{
}

bool LoginManager::CheckPassword(QString password) {
    return this->password == password;
}

void LoginManager::onLogIn(QString password) {
    bool ok = this->CheckPassword(password);
    emit pwdAccepted(ok);
}
