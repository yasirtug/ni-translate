#include "keycatcher.h"
#include <linux/input.h>
#include <unistd.h>
#include <sys/file.h>

#define GREP_PATH "grep"

std::string find_path()
{
    const char *cmd = GREP_PATH " -E 'Handlers|EV=' /proc/bus/input/devices | "
            GREP_PATH " -B1 'EV=1[02]001[3Ff]' | " GREP_PATH " -Eo 'event[0-9]+' ";

    FILE *pipe = popen(cmd, "r");

    char buff[30];
    fscanf(pipe, "%s", buff);

    pclose(pipe);

    return "/dev/input/" + std::string(buff);
}
void KeyCatcher::process()
{
    std::string address = find_path();
    int fl = open(address.c_str(), O_RDONLY);
    input_event event;
    bool combo = false;
    __time_t t;
    while (read(fl, &event, sizeof event))
    {
        if (event.type != EV_KEY || event.value != 1)
            continue;
        // if event is not key down event

        if (event.code == 29) //ctrl
        {
            if (combo == true && event.time.tv_sec - t < 2)
            {
                Translate();
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
