#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    void update(int, int);
    int w, h;
private:
    Ui::SettingsWindow *ui;
signals:

public slots:
    void setDefaultSize();
    void selectKey();
};

#endif // SETTINGSWINDOW_H
