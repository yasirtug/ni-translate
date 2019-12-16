#include "keycatcher.h"
#include <QSettings>


KeyCatcher::KeyCatcher(QObject *parent) : QObject (parent)
{
    display = XOpenDisplay(NULL);
    Window win = DefaultRootWindow(display);

    XIEventMask m;
    m.deviceid = XIAllDevices;
    m.mask_len = XIMaskLen(XI_LASTEVENT);
    m.mask = (unsigned char *)calloc(m.mask_len, sizeof(char));
    XISetMask(m.mask, XI_KeyPress);

    XISelectEvents(display, win, &m, 1);
    free(m.mask);

    int xi_opcode, event, error;
    XQueryExtension(display, "XInputExtension", &xi_opcode, &event, &error);

}

void KeyCatcher::keyCatcherLoop()
{
    bool combo = false;
    __time_t t = 0;
    int key;
    while (1)
    {
        key = QSettings().value("key").toInt();
        XIRawEvent event = getKeyEvent();
        if (event.detail == key)
        {
            if (combo == true && event.time - t < 2000)
            {
                call();
                combo = false;
            }
            else
            {
                combo = true;
                t = event.time;
            }
        }
        else
            combo = false;
    }
}


XIRawEvent KeyCatcher::getKeyEvent()
{
    XEvent ev;
    XGenericEventCookie *cookie = (XGenericEventCookie *)&ev.xcookie;
    XNextEvent(display, &ev);
    XGetEventData(display, cookie);
    XIRawEvent result =  *((XIRawEvent *)cookie->data);
    XFreeEventData(display, cookie);
    return result;
}
