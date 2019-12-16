#ifndef KEYCATCHER_H
#define KEYCATCHER_H

#include <QObject>

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
private:
    char *keyboard_path;
    Display *display;
signals:
    void call();
    void finished();
public slots:
    void keyCatcherLoop();
};

#endif // KEYCATCHER_H
