#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QApplication>
#include <QClipboard>
#include <keycatcher.h>
#include "utils.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sw = new SettingsWindow();
    sw->setWindowModality(Qt::ApplicationModal);
    QThread* thread = new QThread;
    KeyCatcher* catcher = new KeyCatcher();
    catcher->moveToThread(thread);
    connect(catcher, SIGNAL(call()), this, SLOT(call()));
    connect(thread, SIGNAL (started()), catcher, SLOT (process()));
    connect(catcher, SIGNAL (finished()), thread, SLOT (quit()));
    connect(catcher , SIGNAL (finished()), catcher, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();

    map = Utils().getLanguages();
    int length = map.size();
    for(int i = 0; i < length; ++i)
    {
        this->ui->srcBox->addItem(QString::fromStdString(map.values()[i]));
        this->ui->destBox->addItem(QString::fromStdString(map.values()[i]));
    }
    map.insert("auto", "<auto>");
    QString src = QSettings().value("src").toString();
    QString dest = QSettings().value("dest").toString();

    this->ui->srcBox->setCurrentText(src);
    this->ui->destBox->setCurrentText(dest);
    connect(this->ui->srcBox, SIGNAL(currentTextChanged(QString)), this, SLOT(srcBoxChange(QString)));
    connect(this->ui->destBox, SIGNAL(currentTextChanged(QString)), this, SLOT(destBoxChange(QString)));
    connect(this->ui->swapButton, SIGNAL(clicked(bool)), this, SLOT(swapButtonClicked(bool)));
    connect(this->ui->settingsButton, SIGNAL(clicked(bool)), this, SLOT(settingsButtonClicked(bool)));
}

void MainWindow::settingsButtonClicked(bool)
{
    sw->show();
    sw->currentSizeInformation(this->width(), this->height());
}

void MainWindow::srcBoxChange(QString text)
{
    QSettings().setValue("src", text);
}

void MainWindow::destBoxChange(QString text)
{
    QSettings().setValue("dest", text);
}

void MainWindow::swapButtonClicked(bool)
{
    int temp;
    temp = this->ui->srcBox->currentIndex();
    this->ui->srcBox->setCurrentIndex(this->ui->destBox->currentIndex() + 1);
    this->ui->destBox->setCurrentIndex(temp - 1);
}

void MainWindow::call()
{
    QString selection = QApplication::clipboard()->text(QClipboard::Selection);

    std::string src = this->ui->srcBox->currentText().toStdString();
    std::string dest = this->ui->destBox->currentText().toStdString();

    src = map.key(src);
    dest = map.key(dest);

    Utils().translate(selection.toStdString(), dest, src);
    struct result result = Utils().getResult();


    this->ui->resultText->setText(result.text);

    this->show();
    this->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}
