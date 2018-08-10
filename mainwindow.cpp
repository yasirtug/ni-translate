#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QApplication>
#include <QClipboard>
#include <keycatcher.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QThread* thread = new QThread;
    KeyCatcher* catcher = new KeyCatcher();
    catcher->moveToThread(thread);
    connect(catcher, SIGNAL(Translate()), this, SLOT(Translate()));
    connect(thread, SIGNAL (started()), catcher, SLOT (process()));
    connect(catcher, SIGNAL (finished()), thread, SLOT (quit()));
    connect(catcher , SIGNAL (finished()), catcher, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}
void MainWindow::Translate()
{
    QString selection = QApplication::clipboard()->text(QClipboard::Selection);
    std::string cmd = "python3 translate.py \"" + selection.toStdString() + "\" tr";
    system(cmd.c_str());

    FILE* f = fopen(".result", "r");

    char dest[10];
    char src[10];
    fscanf(f, "%s %s ", dest, src);

    char result[15000];
    int t = 0;
    while(fscanf(f, "%c", result + t++) != EOF);
    result[t-1] = 0;

    this->ui->resultText->setText(result);

    this->show();
    this->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}
