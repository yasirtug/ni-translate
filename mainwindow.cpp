#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QApplication>
#include <QClipboard>
#include <keycatcher.h>
#include "utils.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QThread* thread = new QThread;
    KeyCatcher* catcher = new KeyCatcher();
    catcher->moveToThread(thread);
    connect(catcher, SIGNAL(call()), this, SLOT(call()));
    connect(thread, SIGNAL (started()), catcher, SLOT (process()));
    connect(catcher, SIGNAL (finished()), thread, SLOT (quit()));
    connect(catcher , SIGNAL (finished()), catcher, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();

    QMap<std::string, std::string> map = Utils().getLanguages();
}

void MainWindow::call()
{
    QString selection = QApplication::clipboard()->text(QClipboard::Selection);

    Utils().translate(selection.toStdString());

    struct result result = Utils().getResult();
    this->ui->resultText->setText(result.text);

    this->show();
    this->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}
