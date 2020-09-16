#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/icon.png"));
    ui->setupUi(this);
    matchIconsToPallete();
    settingsWindow = new SettingsWindow();
    settingsWindow->setWindowModality(Qt::ApplicationModal);

#ifdef OCR
    if(QSettings().contains("ocr_lang") == false)
    {
        QSettings().setValue("ocr_lang", "eng");
    }
    tesseractAPI = new tesseract::TessBaseAPI();
    if (tesseractAPI->Init(NULL, QSettings().value("ocr_lang").toString().toLocal8Bit(), tesseract::OEM_LSTM_ONLY, NULL, 0, NULL, NULL, true)) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    settingsWindow->tesseractAPI = tesseractAPI;
#endif

    QThread* thread = new QThread;
    KeyCatcher* catcher = new KeyCatcher();
    catcher->moveToThread(thread);
    connect(catcher, SIGNAL(call(int)), this, SLOT(catchedKey(int)));
    connect(thread, SIGNAL (started()), catcher, SLOT (keyCatcherLoop()));
    connect(catcher, SIGNAL (finished()), thread, SLOT (quit()));
    connect(catcher , SIGNAL (finished()), catcher, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();

    KeyCatcher::addKey(QSettings().value("translate_selected_hotkey").toInt());
    KeyCatcher::addKey(QSettings().value("translate_screen_hotkey").toInt());

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
    connect(this->ui->translateButton, SIGNAL(clicked(bool)), this, SLOT(translate()));
    connect(qApp,&QApplication::paletteChanged, this, &MainWindow::matchIconsToPallete);

    this->move(QApplication::primaryScreen()->geometry().center() - this->geometry().center());

    this->ui->inputField->setFocus();
}
void MainWindow::matchIconsToPallete()
{
    QColor color = QGuiApplication::palette().text().color();
    QPixmap swapIcon = QPixmap(":/swap.png");
    QPixmap settingsIcon = QPixmap(":/settings.png");

    QPainter painter(&swapIcon);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(swapIcon.rect(), color);
    painter.end();
    painter.begin(&settingsIcon);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(settingsIcon.rect(), color);
    painter.end();

    this->ui->swapButton->setIcon(swapIcon);
    this->ui->settingsButton->setIcon(settingsIcon);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
    }
    if(event->key() == Qt::Key_Return)
    {
        if(this->ui->inputField->hasFocus())
            translate(TranslateOption::Input);
    }
}
void MainWindow::forceRaise()
{
    if(this->isActiveWindow())
        return;
    this->hide();
    this->show();
    this->raise();
    this->activateWindow();
}
void MainWindow::settingsButtonClicked(bool)
{
    settingsWindow->show();
    settingsWindow->update(this->width(), this->height());
}

void MainWindow::srcBoxChange(int index)
{
    QSettings().setValue("src", index);
    translate(TranslateOption::Input);
}

void MainWindow::destBoxChange(int index)
{
    QSettings().setValue("dest", index);
    translate(TranslateOption::Input);
}

void MainWindow::swapButtonClicked(bool)
{
    int temp;
    temp = this->ui->srcBox->currentIndex();
    this->ui->srcBox->setCurrentIndex(this->ui->destBox->currentIndex() + 1);
    this->ui->destBox->setCurrentIndex(temp - 1);
    translate(TranslateOption::Input);
}
void MainWindow::catchedKey(int key)
{
    QSettings().sync();
    if(key == QSettings().value("translate_selected_hotkey").toInt())
        translate(TranslateOption::Selection);
#ifdef OCR
    else if(key == QSettings().value("translate_screen_hotkey").toInt())
        grabScreen();
#endif
}

void MainWindow::translate(TranslateOption option)
{
    int srcIndex = this->ui->srcBox->currentIndex();
    int destIndex = this->ui->destBox->currentIndex();
    QList<QString> values = map.values();
    switch (option) {
    case TranslateOption::Input:
        translator->translate(this->ui->inputField->toPlainText(), values[srcIndex], values[destIndex + 1]);
        break;
    case TranslateOption::Screen:
        this->ui->inputField->setText(tesseractResult);
        translator->translate(tesseractResult, values[srcIndex], values[destIndex + 1]);
        break;
    case TranslateOption::Selection:
        QString selection = QApplication::clipboard()->text(QClipboard::Selection);
        this->ui->inputField->setText(selection);
        translator->translate(selection, values[srcIndex], values[destIndex + 1]);
        break;
    }
}

void MainWindow::translationCompleted(QString result)
{
    result.push_front("<html>");
    this->ui->resultField->setText(result);
    forceRaise();
}

#ifdef OCR
void MainWindow::grabScreen()
{
    QScreen *screen =  window()->screen();
    mPixmap = screen->grabWindow(0);
    if(!mQuickEditor) {
        mQuickEditor = std::make_unique<QuickEditor>(mPixmap);
        connect(mQuickEditor.get(), &QuickEditor::grabDone, this, &MainWindow::grapCompleted);
        connect(mQuickEditor.get(), &QuickEditor::grabCancelled, this, &MainWindow::grabCanceled);
        mQuickEditor->show();
        return;
    } else {
        mQuickEditor->hide();
        mQuickEditor.reset(nullptr);
    }
}
void MainWindow::grapCompleted(const QPixmap &result)
{
    mQuickEditor->close();
    mQuickEditor.reset(nullptr);
    QImage i = result.toImage();
    tesseractAPI->SetImage((unsigned char*)i.constBits(),i.width(), i.height(), 4, i.bytesPerLine());
    char* resultText = tesseractAPI->GetUTF8Text();
    tesseractResult = resultText;
    delete [] resultText;
    this->ui->inputField->setText(tesseractResult);

    translate(TranslateOption::Screen);
}
void MainWindow::grabCanceled()
{
    mQuickEditor->close();
    mQuickEditor.reset(nullptr);
}
#endif

MainWindow::~MainWindow()
{
    delete ui;
}
