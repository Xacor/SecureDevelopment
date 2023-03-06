#ifndef CRYPTOCONTROLLER_H
#define CRYPTOCONTROLLER_H
#include <QByteArray>
#include <QObject>


class CryptoController
{
public:
    explicit CryptoController(QObject *parent = 0);

    static QByteArray GenerateKey(const QByteArray password);

    static bool DecryptFile(const QByteArray &key, const QString &file_path, QByteArray &buffer);
    static bool EncryptFile(const QByteArray &key, const QString &file_path, const QByteArray &json);

    constexpr static unsigned char m_iv[17] = "4c48129675f9eff3";
};

#endif // CRYPTOCONTROLLER_H
