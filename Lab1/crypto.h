#ifndef CRYPTO_H
#define CRYPTO_H

#include <QObject>

struct Credentials {
    QString site;
    QString account;
};

class Crypto : public QObject
{
    Q_OBJECT
public:
    explicit Crypto(QObject *parent = nullptr);

    QVector<Credentials> decryptFile(const QString &filename, const QByteArray &key);



signals:

};

#endif // CRYPTO_H
