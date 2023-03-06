#include "cryptocontroller.h"
#include <QString>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <QBuffer>
#include <openssl/evp.h>


QByteArray CryptoController::GenerateKey(QByteArray password)
{
    QByteArray hash = QCryptographicHash::hash(password, QCryptographicHash::Sha256).toHex().mid(0, 32);
    return hash;
}

bool CryptoController::DecryptFile(const QByteArray &key, const QString &file_path, QByteArray &buffer)
{
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly)) {
        qDebug()<<"Failed to open file:" << file_path;
        return false;
    }

    EVP_CIPHER_CTX *ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return false;
    }

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char *)key.data(), m_iv)) {
        return false;
    }

    int decrypted_len = 0;

    while(!file.atEnd()) {
        char encoded_buf[256] = {0};
        unsigned char decrypted_buf[512] = {0};

        // Считывание по 512, так как файл в HEX кодировке (2hex = 1 char)
        file.read(encoded_buf, 512);

        QByteArray decoded_buf = QByteArray::fromHex(QByteArray(encoded_buf));
        int decoded_len = decoded_buf.size();


        if (!EVP_DecryptUpdate(ctx, decrypted_buf, &decrypted_len, (unsigned char*)decoded_buf.data(), decoded_len)) {
            return false;
        }

        if (decoded_len < 256) {
            int tmplen;
            if (!EVP_DecryptFinal_ex(ctx, decrypted_buf + decrypted_len, &tmplen)) {
                EVP_CIPHER_CTX_free(ctx);
                return false;
            }
            decrypted_len += tmplen;
        }
        buffer += QByteArray((char*)decrypted_buf, decrypted_len);

    }
    EVP_CIPHER_CTX_free(ctx);
    file.close();
    return true;
}

