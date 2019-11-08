#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QSettings>
#include "translator.h"
#include "keycatcher.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    connect(this->ui->setWindowSize, SIGNAL(clicked(bool)), this, SLOT(setDefaultSize()));
    connect(this->ui->selectKey, SIGNAL(pressed()), this, SLOT(selectKey()));
}
void SettingsWindow::update(int w, int h)
{
    int key = QSettings().value("key").toInt();
    this->ui->selectedKey->setText(QString::number(key));
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

void SettingsWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
    }
}
SettingsWindow::~SettingsWindow()
{
    delete ui;
}
