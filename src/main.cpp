#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    a.setOrganizationName("yasirtug");
    a.setApplicationName("ni-translate");

    a.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings, true);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    int width = QSettings().value("windowWidth").toInt();
    int height = QSettings().value("windowHeight").toInt();

    if(QSettings().contains("translate_selected_hotkey") == false)
    {
        QSettings().setValue("translate_selected_hotkey", 66); // Should be Caps_Lock on US layout
    }
    if(QSettings().contains("translate_screen_hotkey") == false)
    {
        QSettings().setValue("translate_screen_hotkey", 50); // Should be Shift_L on US layout
    }

    MainWindow w;
    w.show();
    if(width && height)
    {
        w.resize(width, height);
    }

    return a.exec();
}
