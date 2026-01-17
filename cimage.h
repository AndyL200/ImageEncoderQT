#ifndef CIMAGE_H
#define CIMAGE_H

#include <QObject>
#include <QQmlEngine>
#include <QUrl>
#include <QString>
#include <QImage>

class CImage : public QObject
{
    QML_ELEMENT
    Q_OBJECT
public:
    explicit CImage(QObject* parent = nullptr);
    Q_INVOKABLE void loadImage(const QUrl& imageFile);
    Q_INVOKABLE QString encode(const QString& message);
    Q_INVOKABLE QString decode();
    Q_INVOKABLE void setLoaded(bool v);
    Q_INVOKABLE bool getLoaded();
private:
    QUrl imgFile;
    QByteArray b_arr;
    QString m_mimeType;
    bool _loaded;
signals:
    void imageLoaded(const QString& dataUrl);
};

#endif // CIMAGE_H
