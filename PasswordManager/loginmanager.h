#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QObject>

class LoginManager : public QObject
{
    Q_OBJECT
public:
    explicit LoginManager(QObject *parent = 0);
    LoginManager(QString &file_path);
    bool CheckPassword(QByteArray &key);

signals:
    void pwdChecked(bool ok);
    void keyGenerated(QByteArray key);
    void showAlert(QString text);

public slots:
    void onLogIn(QString password);

private:
    QString file_path;
};



#endif // LOGINMANAGER_H
