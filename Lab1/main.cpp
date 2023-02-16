#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>

#include <LoginManager.h>
#include <AccountList.h>
#include <AccountModel.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<AccountModel>("Account", 1, 0, "AccountModel");
    qmlRegisterUncreatableType<AccountList>("Account", 1,0, "AccountList",
        "AccountList shoud not be created in QML");


    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();


    LoginManager lm;
    context->setContextProperty("lm", &lm);

    AccountList accountList;
    context->setContextProperty("accountList", &accountList);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
