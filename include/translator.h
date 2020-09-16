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
    QMap<QString, QString> getLanguages();
    void getResult();
    void translate(QString text, QString dest, QString src = "auto");
private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QMetaObject::Connection connection;

signals:
    void translationCompleted(QString text);
public slots:
};
#endif // TRANSLATOR_H
