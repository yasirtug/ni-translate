#include "keycatcher.h"
#include <linux/input.h>
#include <unistd.h>
#include <sys/file.h>
#include <QSettings>
#include <stdio.h>

#define GREP_PATH "grep"
#define MAX_PATH_SIZE 100

KeyCatcher::KeyCatcher(QObject *parent) : QObject (parent)
{
    keyboard_path = new char[MAX_PATH_SIZE];
    int cursor = sprintf(keyboard_path, "%s", "/dev/input/");
    const char *cmd = GREP_PATH " -E 'Handlers|EV=' /proc/bus/input/devices | "
            GREP_PATH " -B1 'EV=1[02]001[3Ff]' | " GREP_PATH " -Eo 'event[0-9]+' ";

    FILE *pipe = popen(cmd, "r");
    fscanf(pipe, "%s", keyboard_path + cursor);
}

void KeyCatcher::process()
{
    int fl = open(keyboard_path, O_RDONLY);
    input_event event;
    bool combo = false;
    __time_t t = 0;
    int key;
    while (read(fl, &event, sizeof event))
    {
        // if event is not key down event
        if (event.type != EV_KEY || event.value != 1)
            continue;
        key = QSettings().value("key").toInt();
        if (event.code == key)
        {
            if (combo == true && event.time.tv_sec - t < 2)
            {
                call();
                combo = false;
            }
            else
            {
                combo = true;
                t = event.time.tv_sec;
            }
        }
        else
        {
            combo = false;
        }
    }
}


int KeyCatcher::getKeyCode()
{
    int fl = open(keyboard_path, O_RDONLY);
    input_event event;
    while(read(fl, &event, sizeof event))
    {
        if (event.type != EV_KEY || event.value != 1)
            continue;
        else
            break;
    }
    return event.code;
}
