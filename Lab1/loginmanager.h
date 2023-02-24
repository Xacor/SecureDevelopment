#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QObject>

class LoginManager : public QObject
{
    Q_OBJECT
public:
    explicit LoginManager(QObject *parent = 0);
    bool CheckPassword(QString password);

signals:
    void pwdChecked(bool ok);

public slots:
    void onLogIn(QString password);

private:
    const QString mPassword = "qwerty";
};



#endif // LOGINMANAGER_H