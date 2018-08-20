#include "keycatcher.h"
#include <linux/input.h>
#include <unistd.h>
#include <sys/file.h>
#include <QSettings>
#include <iostream>

#define GREP_PATH "grep"

KeyCatcher::KeyCatcher()
{
    keyboard_path = find_path();
}

void KeyCatcher::process()
{
    int fl = open(keyboard_path.c_str(), O_RDONLY);
    input_event event;
    bool combo = false;
    __time_t t;
    int key;
    while (read(fl, &event, sizeof event))
    {
        // if event is not key down event
        key = QSettings().value("key").toInt();
        if (event.type != EV_KEY || event.value != 1)
            continue;
        if (event.code == key)
        {
            if (combo == true && event.time.tv_sec - t < 2)
            {
                call();
            }
            t = event.time.tv_sec;
            combo = true;
        }
        else
        {
            combo = false;
        }
    }
}

std::string KeyCatcher::find_path()
{
    const char *cmd = GREP_PATH " -E 'Handlers|EV=' /proc/bus/input/devices | "
            GREP_PATH " -B1 'EV=1[02]001[3Ff]' | " GREP_PATH " -Eo 'event[0-9]+' ";

    FILE *pipe = popen(cmd, "r");

    char buff[30];
    fscanf(pipe, "%s", buff);

    pclose(pipe);

    return "/dev/input/" + std::string(buff);
}

int KeyCatcher::getKeyCode()
{
    int fl = open(keyboard_path.c_str(), O_RDONLY);
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
