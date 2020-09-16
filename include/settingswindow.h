#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#ifdef OCR
#include <QVector>
#include "tesseract/baseapi.h"
#include "tesseract/genericvector.h"
#include "tesseract/strngs.h"
#endif

namespace Ui {
class SettingsWindow;
}

enum Selectors{
    sSelected,
    sScreen
};

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    void update(int, int);
    int w, h;
#ifdef OCR
    tesseract::TessBaseAPI *tesseractAPI = nullptr;
    QStringList tesseractLanguages;
#endif
private:
    Ui::SettingsWindow *ui;
    void keyPressEvent(QKeyEvent *event);
signals:

public slots:
    void setDefaultSize();
    void selectKey(Selectors);
#ifdef OCR
    void ocrLangChange(int index);
#endif
};

#endif // SETTINGSWINDOW_H
