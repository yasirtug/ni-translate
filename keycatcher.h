#ifndef KEYCATCHER_H
#define KEYCATCHER_H

#include <QObject>

class KeyCatcher : public QObject
{
    Q_OBJECT
public:

signals:
    void call();
    void finished();
public slots:
    void process();
};

#endif // KEYCATCHER_H
