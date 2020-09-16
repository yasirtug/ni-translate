#include "keycatcher.h"
#include <QSettings>
#include <iostream>

QSet<int> KeyCatcher::keysToCatch;

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

void KeyCatcher::addKey(int key)
{
    keysToCatch.insert(key);
}
void KeyCatcher::removeKey(int key)
{
    keysToCatch.remove(key);
}

QString KeyCatcher::getKeyName(int key)
{
    int avr;
    KeySym* sym =  XGetKeyboardMapping(XOpenDisplay(NULL), key, 1, &avr);
    return XKeysymToString(*sym);
}

void KeyCatcher::keyCatcherLoop()
{
    int lastKey = 0;
    __time_t t = 0;
    while (1)
    {
        XIRawEvent event = getKeyEvent();
        for(auto key : keysToCatch)
        {
            if (event.detail == key)
            {
                if (lastKey == key && event.time - t < 2000)
                {
                    call(key);
                    lastKey = 0;
                }
                else
                {
                    lastKey = key;
                    t = event.time;
                }
                break;
            }
        }
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
