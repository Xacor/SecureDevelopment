#ifndef CRYPTOCONTROLLER_H
#define CRYPTOCONTROLLER_H
#include <QByteArray>

class CryptoController
{
public:
    CryptoController();

    static QByteArray GenerateKey(const QByteArray password);

    static QByteArray* DecodeFile(const QString &file_path);

    static bool DecryptFile(const QByteArray &key, const QString &file_path, QByteArray &buffer);
    static int EncryptFile(const QByteArray &key, const QString &file_path, const QByteArray &json);

    constexpr static unsigned char m_iv[17] = "4c48129675f9eff3";
};

#endif // CRYPTOCONTROLLER_H
