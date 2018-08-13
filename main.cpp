#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    a.setOrganizationName("yasirtug");
    a.setApplicationName("ni-translate");

    MainWindow w;
    w.show();
    return a.exec();
}
