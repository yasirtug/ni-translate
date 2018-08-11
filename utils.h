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
    QMap<std::string, std::string> getLanguages();
    struct result getResult();
    void translate(std::string text);
};

#endif // UTILS_H
