#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QCryptographicHash>
#include "windows.h"

#include <LoginManager.h>
#include <AccountList.h>
#include <AccountModel.h>
#include <CryptoController.h>
#include <AccountFilterProxyModel.h>

int main(int argc, char *argv[])
{
    // Определить начало сегмента .text
    unsigned long long moduleBase = (unsigned long long)GetModuleHandle(NULL);
    unsigned long long text_segment_start = moduleBase + 0x1000;
    // Определить его длину
    PIMAGE_DOS_HEADER pIDH = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase);
    PIMAGE_NT_HEADERS pINH = reinterpret_cast<PIMAGE_NT_HEADERS>(moduleBase + pIDH->e_lfanew);
    unsigned long long size_of_text = pINH -> OptionalHeader.SizeOfCode; // размер .text

    QByteArray text_segment_contents = QByteArray((char*)text_segment_start, size_of_text);
    QByteArray current_hash = QCryptographicHash::hash(text_segment_contents, QCryptographicHash::Sha256);
    QByteArray current_hash_base64 = current_hash.toBase64();

    const QByteArray hash_needed_base64 = QByteArray("xxuvF22ggf0GIV94aCY6mVySBqvkY7jmGAZhS84GvB8=");

    qDebug() <<  current_hash_base64;

    bool hash_ok = (hash_needed_base64 == current_hash_base64);

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
    if (!hash_ok) {
        emit lm.showAlert("Хэши не совпадают!");
    }
//    if (IsDebuggerPresent()) {
//        emit lm.showAlert("Debugger is present!");

//    }

    QObject *loginPage = engine.rootObjects().constFirst()->children().at(2);
    QObject::connect(loginPage, SIGNAL(login(QString)), &lm, SLOT(onLogIn(QString)));

    QObject *formPage = engine.rootObjects().constFirst()->children().at(3);
    QObject::connect(formPage, SIGNAL(accountCreated(QString,QString,QString)), &accountList, SLOT(onAccountCreated(QString,QString,QString)));

    QObject *indexPage = engine.rootObjects().constFirst()->children().at(4);
    QObject::connect(indexPage, SIGNAL(copyToClipboard(int,int)), &accountList, SLOT(onCopyToClipboard(int,int)));


    return app.exec();
}
