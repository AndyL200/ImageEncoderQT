#include "cimage.h"
#include <QFile>

CImage::CImage(QObject* parent) {setLoaded(false);}

void CImage::loadImage(const QUrl& imgFile) {
    this->imgFile = imgFile;
    QString localpath = imgFile.toLocalFile();

    QFile file(localpath);
    if (file.open(QIODevice::ReadOnly)) {
        this->b_arr = file.readAll();
        this->size = b_arr.size();
        setLoaded(true);
        qDebug() << "Loaded image from " << localpath << " of size " << size;

    }
    else {
        setLoaded(false);
        qDebug() << "Failed to load image";
    }
}

QImage CImage::encode(const QString& message) {
    if(!_loaded) {
        return QImage();
    }

    QByteArray msgBytes = message.toUtf8();

    if(size < (size_t)(msgBytes.size() * 8 + 8)) //+8 for null terminator
    {
        qDebug() << "Message too large to encode";
        return QImage();
    }

    int byteIndex = 0;

    //Encode each character
    for(int i = 0; i < msgBytes.size(); i++) {
        unsigned char c = static_cast<unsigned char>(msgBytes.at(i));

        //8 bits per character
        for(int bit = 7; bit >= 0; bit--) {
            //Clear LSB bit
            b_arr[byteIndex] &= 0xFE;

            //Set LSB to current bit of c
            b_arr[byteIndex] |= ((c >> bit) & 1);
            byteIndex++;
        }
    }

    //Encoding the null terminator (is this necessary?)
    for(int bit = 7; bit >= 0; bit--) {
        b_arr[byteIndex] &= 0xFE;
        b_arr[byteIndex] |= 0;
        byteIndex++;
    }

    return QImage();
}

QString CImage::decode() {
    if (!_loaded) {
        return "";
    }

    //get size of image
    int byteIndex = 0;
    std::string res = "";

    while(byteIndex + 8 <= size) {
        unsigned char c = 0;
        for(int bit = 7; bit >= 0; bit--) {
            unsigned char byte = b_arr[byteIndex];
            c |= (byte & 1) << bit;
            byteIndex++;
        }

        if(c == '\0') {
            break;
        }

        res += c;
    }

    return QString(res.c_str());
}

void CImage::setLoaded(bool v) {
    _loaded = v;
}
bool CImage::getLoaded() {
    return _loaded;
}
