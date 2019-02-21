#include "translator.h"

#define TRANSLATE_DOMAIN "https://translate.google.com"

Translator::Translator(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
}

void Translator::getResult()
{
    QString result = QString(reply->readAll());
    int begin = result.indexOf("class=\"t0\">") + 11;
    int end = result.indexOf('<', begin);
    result = result.mid(begin, end - begin);
    translationCompleted(result);
}

void Translator::translate(QString text, QString src, QString dest)
{
    disconnect(connection);
    text = QUrl::toPercentEncoding(text);
    QString urlString = QString("%1%2%3%4%6%7%8").arg(TRANSLATE_DOMAIN, "/m?tl=", dest, "&sl=", src, "&q=", text);

    QUrl url(urlString);
    QNetworkRequest request(url);
    reply = manager->get(request);
    connection = connect(reply, &QNetworkReply::finished, this, &Translator::getResult);
}
