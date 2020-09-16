#ifndef KEYCATCHER_H
#define KEYCATCHER_H

#include <QObject>
#include <QSet>

#include <X11/extensions/XInput2.h>
// these undefs are necessary in Qt because of the above include
#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted

class KeyCatcher : public QObject
{
    Q_OBJECT
public:
    explicit KeyCatcher(QObject *parent = nullptr);
    XIRawEvent getKeyEvent();
    static void addKey(int);
    static void removeKey(int);
    static QString getKeyName(int);
private:
    char *keyboard_path;
    Display *display;
    static QSet<int> keysToCatch;
signals:
    void call(int key);
    void finished();
public slots:
    void keyCatcherLoop();
};

#endif // KEYCATCHER_H
