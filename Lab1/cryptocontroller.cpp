#include "cryptocontroller.h"
#include <QString>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <QBuffer>
#include <openssl/evp.h>

CryptoController::CryptoController()
{

}

QByteArray CryptoController::GenerateKey(QByteArray password)
{
    QByteArray hash = QCryptographicHash::hash(password, QCryptographicHash::Sha256).toHex().mid(0, 32);
    return hash;
}

QByteArray *CryptoController::DecodeFile(const QString &file_path)
{
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly)) {
        qDebug()<<"Failed to open file:" << file_path;
        return nullptr;
    }

    int read_len = 0;
    QByteArray* result = new QByteArray;
    while(!file.atEnd()) {
        char read_bufer[256] = {0};
        unsigned char decrypted_buf[512] = {0};
        read_len = file.read(read_bufer, 256) ;
        // TODO: frombase64 возвращает по 192, а не 256
        QByteArray encoded_bytes(read_bufer);
        QByteArray::FromBase64Result base64 = QByteArray::fromBase64Encoding(encoded_bytes);
        result->append(base64.decoded);
    }

    qDebug() <<"Decode\n" <<  result->data();
    file.close();
    return result;
}

bool CryptoController::DecryptFile(const QByteArray &key, const QString &file_path, QByteArray &buffer)
{
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly)) {
        qDebug()<<"Failed to open file:" << file_path;
        return false;
    }

    QByteArray decoded_buf = QByteArray::fromHex(file.readAll());

    QBuffer buffer_stream(&decoded_buf);
    if (!buffer_stream.open(QBuffer::ReadOnly)) {
        qDebug()<<"Failed to open buffer";
        return false;
    }

    EVP_CIPHER_CTX *ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return false;
    }

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char *)key.data(), m_iv)) {
        return false;
    }

    int read_len=0, decrypted_len = 0;

    while(!buffer_stream.atEnd()) {
        char encrypted_buf[256] = {0};
        unsigned char decrypted_buf[512] = {0};

        read_len = buffer_stream.read(encrypted_buf, 256);

        if (!EVP_DecryptUpdate(ctx, decrypted_buf, &decrypted_len, (unsigned char*)encrypted_buf, read_len)) {
            return false;
        }

        if (read_len < 256) {
            int tmplen;
            if (!EVP_DecryptFinal_ex(ctx, decrypted_buf + decrypted_len, &tmplen)) {
                EVP_CIPHER_CTX_free(ctx);
                return false;
            }
            decrypted_len += tmplen;
            buffer += QByteArray((char *)decrypted_buf, decrypted_len);
        }
        buffer += QByteArray((char*)decrypted_buf, decrypted_len);

    }
    EVP_CIPHER_CTX_free(ctx);
    qDebug() << "Buffer: "<< buffer;
    return true;
}
