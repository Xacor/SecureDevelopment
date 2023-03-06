#include "loginmanager.h"
#include "cryptocontroller.h"

LoginManager::LoginManager(QObject *parent) : QObject(parent)
{
}

bool LoginManager::CheckPassword(QString password) {
    return this->mPassword == password;
}

void LoginManager::onLogIn(QString password) {
    bool ok = this->CheckPassword(password);
    CryptoController::GenerateKey(password.toUtf8());
    emit pwdChecked(ok);
}
