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
    connect(this->ui->setKey0, &QPushButton::pressed, this, [&]{selectKey(sSelected);});
    connect(this->ui->setKey1, &QPushButton::pressed, this, [&]{selectKey(sScreen);});
#ifndef OCR
    this->ui->ocrSettings->setVisible(false);
#endif
}
void SettingsWindow::update(int w, int h)
{
    int key = QSettings().value("translate_selected_hotkey").toInt();
    this->ui->selectedKey0->setText(KeyCatcher::getKeyName(key));
    int key2 = QSettings().value("translate_screen_hotkey").toInt();
    this->ui->selectedKey1->setText(KeyCatcher::getKeyName(key2));
    this->w = w;
    this->h = h;
#ifdef OCR
    connect(this->ui->langsComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ocrLangChange(int)));
    tesseractLanguages.clear();
    GenericVector<STRING> languages;
    if(tesseractAPI)
        tesseractAPI->GetAvailableLanguagesAsVector(&languages);
    for (int i = 0; i < languages.size(); ++i) {
        tesseractLanguages.push_back(languages[i].c_str());
    }
    QString last = QSettings().value("ocr_lang").toString();
    this->ui->langsComboBox->blockSignals(true);
    this->ui->langsComboBox->clear();
    this->ui->langsComboBox->addItems(tesseractLanguages);
    this->ui->langsComboBox->setCurrentText(last);
    this->ui->langsComboBox->blockSignals(false);
#endif
}

void SettingsWindow::selectKey(Selectors s)
{
    int key = KeyCatcher().getKeyEvent().detail;
    if(s == sSelected)
    {
        KeyCatcher::removeKey(QSettings().value("translate_selected_hotkey").toInt());
        KeyCatcher::addKey(key);
        QSettings().setValue("translate_selected_hotkey", key);
        this->ui->selectedKey0->setText(KeyCatcher::getKeyName(key));
    }
    else{
        KeyCatcher::removeKey(QSettings().value("translate_screen_hotkey").toInt());
        KeyCatcher::addKey(key);
        QSettings().setValue("translate_screen_hotkey", key);
        this->ui->selectedKey1->setText(KeyCatcher::getKeyName(key));
    }
}
#ifdef OCR
void SettingsWindow::ocrLangChange(int index)
{
    QString lang = this->ui->langsComboBox->itemText(index);
    if (tesseractAPI->Init(NULL, lang.toLocal8Bit(), tesseract::OEM_LSTM_ONLY, NULL, 0, NULL, NULL, true)) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    QSettings().setValue("ocr_lang", lang);
}
#endif

void SettingsWindow::setDefaultSize()
{
    QSettings().setValue("windowWidth", w);
    QSettings().setValue("windowHeight", h);
}

void SettingsWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        this->close();
    }
}
SettingsWindow::~SettingsWindow()
{
    delete ui;
}
