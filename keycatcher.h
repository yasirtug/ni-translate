#ifndef KEYCATCHER_H
#define KEYCATCHER_H

#include <QObject>

class KeyCatcher : public QObject
{
    Q_OBJECT
public:
    explicit KeyCatcher(QObject *parent = nullptr);

    int getKeyCode();
private:
    char *keyboard_path;
signals:
    void call();
    void finished();
public slots:
    void process();
};

#endif // KEYCATCHER_H
