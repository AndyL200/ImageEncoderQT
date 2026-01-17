#include "cimage.h"
#include <QFile>
#include <QFileInfo>
#include <QBuffer>

CImage::CImage(QObject* parent) : QObject(parent) {setLoaded(false);}

void CImage::loadImage(const QUrl& imgFile) {
    this->imgFile = imgFile;
    QString localpath = imgFile.toLocalFile();

    QFile file(localpath);

    if (file.open(QIODevice::ReadOnly)) {
        this->b_arr = file.readAll();
        setLoaded(true);

        // Set MIME type
        QFileInfo info(localpath);
        QString ext = info.suffix().toLower();
        if (ext == "png") m_mimeType = "image/png";
        else if (ext == "jpg" || ext == "jpeg") m_mimeType = "image/jpeg";
        else if (ext == "bmp") m_mimeType = "image/bmp";
        else m_mimeType = "image/png";

        QString dataUrl = "data:" + m_mimeType + ";base64," + QString::fromLatin1(b_arr.toBase64());
        emit imageLoaded(dataUrl);

        qDebug() << "Loaded image from " << localpath << " of size " << this->b_arr.size();

    }
    else {
        setLoaded(false);
        qDebug() << "Failed to load image";
    }


}

QString CImage::encode(const QString& message) {
    if(!_loaded) {
        return QString();
    }

    QByteArray msgBytes = message.toUtf8();

    int byteIndex = 0;
    QImage imgdecode = QImage::fromData(b_arr);
    if (imgdecode.isNull()) {
        qDebug() << "Failed to decode image";
        return QString();  // or "" for decode()
    }
    //Use a consistent format
    imgdecode = imgdecode.convertToFormat(QImage::Format_RGB32);
    uchar* pixels = imgdecode.bits();
    int totalSizeInBytes = imgdecode.sizeInBytes();

    if(totalSizeInBytes < (size_t)(msgBytes.size() * 8 + 8)) //+8 for null terminator
    {
        qDebug() << "Message too large to encode";
        return QString();
    }

    //Encode each character
    for(int i = 0; i < msgBytes.size(); i++) {
        unsigned char c = static_cast<unsigned char>(msgBytes.at(i));

        //8 bits per character
        for(int bit = 7; bit >= 0; bit--) {
            //Clear LSB bit
            pixels[byteIndex] &= 0xFE;

            //Set LSB to current bit of c
            pixels[byteIndex] |= ((c >> bit) & 1);
            byteIndex++;
        }
    }

    //Encoding the null terminator (is this necessary?)
    for(int bit = 7; bit >= 0; bit--) {
        pixels[byteIndex] &= 0xFE;
        pixels[byteIndex] |= 0;
        byteIndex++;
    }

    // Return as data URL (QImage will re-encode as valid PNG)
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    imgdecode.save(&buffer, "PNG");
    this->b_arr = byteArray;

    return "data:image/png;base64," + QString::fromLatin1(byteArray.toBase64());
}

QString CImage::decode() {
    if (!_loaded) {
        return "";
    }
    QImage imgdecode = QImage::fromData(b_arr);
    //Use a consistent format
    imgdecode = imgdecode.convertToFormat(QImage::Format_RGB32);
    uchar* pixels = imgdecode.bits();
    int totalSizeInBytes = imgdecode.sizeInBytes();

    //get size of image
    int byteIndex = 0;
    QByteArray bar;

    while(byteIndex + 8 <= totalSizeInBytes) {
        unsigned char c = 0;
        for(int bit = 7; bit >= 0; bit--) {
            unsigned char byte = pixels[byteIndex];
            c |= (byte & 1) << bit;
            byteIndex++;
        }

        if(c == '\0') {
            break;
        }

        bar.append(c);
    }
    QString res = QString::fromUtf8(bar);
    return res;
}

void CImage::setLoaded(bool v) {
    _loaded = v;
}
bool CImage::getLoaded() {
    return _loaded;
}
