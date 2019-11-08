#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QApplication>
#include <QClipboard>
#include <keycatcher.h>
#include "translator.h"
#include <QSettings>
#include <languages.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/icon.png"));
    ui->setupUi(this);
    sw = new SettingsWindow();
    sw->setWindowModality(Qt::ApplicationModal);
    QThread* thread = new QThread;
    KeyCatcher* catcher = new KeyCatcher();
    catcher->moveToThread(thread);
    connect(catcher, SIGNAL(call()), this, SLOT(translate()));
    connect(thread, SIGNAL (started()), catcher, SLOT (process()));
    connect(catcher, SIGNAL (finished()), thread, SLOT (quit()));
    connect(catcher , SIGNAL (finished()), catcher, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();

    translator = new Translator();
    connect(translator, SIGNAL(translationCompleted(QString)),this, SLOT(translationCompleted(QString)));

    map = {LANGUAGES};

    int length = map.size();
    this->ui->srcBox->addItem(map.keys()[0]);
    for(int i = 1; i < length; ++i)
    {
        this->ui->srcBox->addItem(map.keys()[i]);
        this->ui->destBox->addItem(map.keys()[i]);
    }
    int src = QSettings().value("src").toInt();
    int dest = QSettings().value("dest").toInt();
    this->ui->srcBox->setCurrentIndex(src);
    this->ui->destBox->setCurrentIndex(dest);

    connect(this->ui->srcBox, SIGNAL(currentIndexChanged(int)), this, SLOT(srcBoxChange(int)));
    connect(this->ui->destBox, SIGNAL(currentIndexChanged(int)), this, SLOT(destBoxChange(int)));
    connect(this->ui->swapButton, SIGNAL(clicked(bool)), this, SLOT(swapButtonClicked(bool)));
    connect(this->ui->settingsButton, SIGNAL(clicked(bool)), this, SLOT(settingsButtonClicked(bool)));
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
    }
}
void MainWindow::settingsButtonClicked(bool)
{
    sw->show();
    sw->update(this->width(), this->height());
}

void MainWindow::srcBoxChange(int index)
{
    QSettings().setValue("src", index);
    translate();
}

void MainWindow::destBoxChange(int index)
{
    QSettings().setValue("dest", index);
    translate();
}

void MainWindow::swapButtonClicked(bool)
{
    int temp;
    temp = this->ui->srcBox->currentIndex();
    this->ui->srcBox->setCurrentIndex(this->ui->destBox->currentIndex() + 1);
    this->ui->destBox->setCurrentIndex(temp - 1);
    translate();
}
void MainWindow::translate()
{
    QString selection = QApplication::clipboard()->text(QClipboard::Selection);

    int srcIndex = this->ui->srcBox->currentIndex();
    int destIndex = this->ui->destBox->currentIndex();
    QList<QString> values = map.values();
    translator->translate(selection, values[srcIndex], values[destIndex + 1]);
}
void MainWindow::translationCompleted(QString result)
{
    result.push_front("<html>");
    this->ui->resultText->setText(result);
    this->show();
    this->raise();
    this->activateWindow();
}
MainWindow::~MainWindow()
{
    delete ui;
}
