#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setText(QString text);
    QMap<std::string, std::string> map;
public slots:
    void call();
    void srcBoxChange(QString);
    void destBoxChange(QString);
    void swapButtonClicked(bool);
signals:
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
