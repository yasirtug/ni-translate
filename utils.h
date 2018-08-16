#ifndef UTILS_H
#define UTILS_H
#include <QMap>
#include <mainwindow.h>
#include "ui_mainwindow.h"

struct result{
    char dest[10];
    char src[10];
    char text[16000];
};

class Utils
{
public:
    Utils();
    QMap<std::string, std::string> getLanguages();
    struct result getResult();
    void translate(std::string text, std::string dest, std::string src = "auto");
    std::string exe_path;
};

#endif // UTILS_H
