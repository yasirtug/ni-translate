#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <settingswindow.h>
#include "translator.h"
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setText(QString text);
    QMap<QString, QString> map;
    SettingsWindow *sw;
    Translator *translator;
public slots:
    void translate();
    void translationCompleted(QString result);
    void srcBoxChange(int);
    void destBoxChange(int);
    void swapButtonClicked(bool);
    void settingsButtonClicked(bool);
signals:
private:
    void keyPressEvent(QKeyEvent *event);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
