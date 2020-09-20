#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QIODevice>
#include <QMap>

class Translator : public QObject
{
    Q_OBJECT
public:
    explicit Translator(QObject *parent = nullptr);
    ~Translator();
    QMap<QString, QString> getLanguages();
    void getResult();
    void getError(QNetworkReply::NetworkError error);
    void translate(QString text, QString dest, QString src = "auto");
private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply = 0;
    QMetaObject::Connection finishedSigConnection;
    QMetaObject::Connection errorSigConnection;

signals:
    void translationCompleted(QString text);
public slots:
};
#endif // TRANSLATOR_H
