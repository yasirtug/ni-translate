#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QSettings>
#include "utils.h"
#include "keycatcher.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    int key = QSettings().value("key").toInt();
    this->ui->selectedKey->setText(QString::number(key));
    connect(this->ui->setWindowSize, SIGNAL(clicked(bool)), this, SLOT(setDefaultSize()));
    connect(this->ui->selectKey, SIGNAL(pressed()), this, SLOT(selectKey()));
}
void SettingsWindow::currentSizeInformation(int w, int h)
{
    this->w = w;
    this->h = h;
}

void SettingsWindow::selectKey()
{
    int key = KeyCatcher().getKeyCode();
    QSettings().setValue("key", key);
    this->ui->selectedKey->setText(QString::number(key));
}

void SettingsWindow::setDefaultSize()
{
    QSettings().setValue("windowWidth", w);
    QSettings().setValue("windowHeight", h);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
