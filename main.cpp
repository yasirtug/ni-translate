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
    int width = QSettings().value("windowWidth").toInt();
    int height = QSettings().value("windowHeight").toInt();
    if(QSettings().value("key") == 0)
    {
        QSettings().setValue("key", 58);
    }
    if(width && height)
    {
        w.resize(width, height);
    }

    return a.exec();
}
