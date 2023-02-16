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

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    qmlRegisterType<AccountModel>("Account", 1, 0, "AccountModel");
    qmlRegisterUncreatableType<AccountList>("Account", 1,0, "AccountList",
        "AccountList shoud not be created in QML");


    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    // Ниже происходит объявление объектов и проброс их в QML
    LoginManager lm;
    context->setContextProperty("lm", &lm);

    QString filepath = QCoreApplication::applicationDirPath() + "/data.json";
    AccountList accountList(&filepath);
    context->setContextProperty("accountList", &accountList);

    // QCoreApplication::applicationDirPath() + "/data.json"



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

    return app.exec();
}
