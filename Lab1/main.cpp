#include <AccountFilterProxyModel.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include <LoginManager.h>
#include <AccountList.h>
#include <AccountModel.h>
#include <QFile>
#include <QJsonDocument>
#include <QDir>
#include <qDebug>
#include <CryptoController.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    // Ниже происходит объявление объектов и проброс их в QML
    QString filepath = QCoreApplication::applicationDirPath() + "/data.json";
    AccountList accountList(filepath);
    context->setContextProperty("accountList", &accountList);

    LoginManager lm(filepath);
    context->setContextProperty("lm", &lm);

    QObject::connect(&lm, &LoginManager::keyGenerated, &accountList, &AccountList::onKeyGenerated);

    AccountModel am;
    am.setlist(&accountList);

    // Объявление прокси модели для фильтрации по вводу
    AccountFilterProxyModel proxyModel(&am, am.siteRole);
    context->setContextProperty("filterModel", &proxyModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    QObject *loginPage = engine.rootObjects().constFirst()->children().at(2);
    QObject::connect(loginPage, SIGNAL(login(QString)), &lm, SLOT(onLogIn(QString)));

    QObject *formPage = engine.rootObjects().constFirst()->children().at(3);
    QObject::connect(formPage, SIGNAL(accountCreated(QString,QString,QString)), &accountList, SLOT(onAccountCreated(QString,QString,QString)));


    return app.exec();
}
