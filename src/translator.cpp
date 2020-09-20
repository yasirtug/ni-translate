#include "translator.h"
#define TRANSLATE_DOMAIN "https://translate.google.com"

Translator::Translator(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
}

Translator::~Translator()
{
    if (reply)
        delete reply;
    delete manager;
}

void Translator::getResult()
{
    if(!reply)
        return;
    QString result = QString(reply->readAll());
    int index = result.indexOf("class=\"t0\">");
    if(index == -1)
    {
        result = "<p style=\"color:#ff0000;\">Incorrect result. May be access is forbidden due to too many requests.</a> </p>";
    }
    else
    {
        int begin = index + 11;
        int end = result.indexOf('<', begin);
        result = result.mid(begin, end - begin);
    }
    translationCompleted(result);
}

void Translator::getError(QNetworkReply::NetworkError error)
{
    QString result = QString("<p style=\"color:#ff0000;\">Network Error: %1\n").arg(error);
    if(error > 0 && error < 100)
        result += "Check your internet connection";
    result += "</p>";
    translationCompleted(result);
}

void Translator::translate(QString text, QString src, QString dest)
{
    // Generate API url
    //    QUrl url(QStringLiteral("https://translate.googleapis.com/translate_a/single"));
    //    url.setQuery(QStringLiteral("client=gtx&ie=UTF-8&oe=UTF-8&dt=bd&dt=ex&dt=ld&dt=md&dt=rw&dt=rm&dt=ss&dt=t&dt=at&dt=qc&sl=%1&tl=%2&hl=%3&q=%4")
    //                 .arg("en", "tr", "tr", QUrl::toPercentEncoding("communication")));

    //    reply = manager->get(QNetworkRequest(url));
    //    disconnect(connection);
    //    connection = connect(reply, &QNetworkReply::finished, this, &Translator::getResult);
    if(text == "")
        return;
    text = QUrl::toPercentEncoding(text);
    QString urlString = QString("%1%2%3%4%6%7%8").arg(TRANSLATE_DOMAIN, "/m?tl=", dest, "&sl=", src, "&q=", text);
    QUrl url(urlString);
    QNetworkRequest request(url);

    if(reply)
    {
        reply->close();
        delete reply;
    }
    reply = manager->get(request);
    disconnect(finishedSigConnection);
    disconnect(errorSigConnection);
    finishedSigConnection = connect(reply, &QNetworkReply::readyRead, this, &Translator::getResult);
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    errorSigConnection = connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &Translator::getError);
#else
    errorSigConnection = connect(reply, &QNetworkReply::errorOccurred, this, &Translator::getError);
#endif
}
