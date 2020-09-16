#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <settingswindow.h>
#include "translator.h"
#include <QKeyEvent>
#include "QuickEditor.h"
#include <QThread>
#include <QApplication>
#include <QClipboard>
#include <keycatcher.h>
#include "translator.h"
#include <QSettings>
#include <languages.h>
#include <QScreen>
#include <iostream>
#include <algorithm>
#include <QPalette>

#ifdef OCR
#include "tesseract/baseapi.h"
#endif

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum TranslateOption
    {
        Selection,
        Screen,
        Input
    };
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void catchedKey(int key);
    void translate(TranslateOption option = Input);
    void translationCompleted(QString result);
    void srcBoxChange(int);
    void destBoxChange(int);
    void swapButtonClicked(bool);
    void settingsButtonClicked(bool);
    void matchIconsToPallete();
#ifdef OCR
    void grapCompleted(const QPixmap &result);
    void grabCanceled();
#endif
signals:
private:
    void keyPressEvent(QKeyEvent *event);
    void forceRaise();
    Ui::MainWindow *ui;
    QMap<QString, QString> map;
    SettingsWindow *settingsWindow;
    Translator *translator;
    QPixmap mPixmap;
    QString tesseractResult;
#ifdef OCR
    std::unique_ptr<QuickEditor> mQuickEditor;
    tesseract::TessBaseAPI *tesseractAPI;
    void grabScreen();
#endif
};

#endif // MAINWINDOW_H
