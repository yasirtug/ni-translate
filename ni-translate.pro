#-------------------------------------------------
#
# Project created by QtCreator 2018-08-11T01:06:52
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ni-translate
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include/

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/keycatcher.cpp \
    src/settingswindow.cpp \
    src/translator.cpp

HEADERS += \
    include/mainwindow.h \
    include/keycatcher.h \
    include/settingswindow.h \
    include/languages.h \
    include/translator.h
#CONFIG += ocr
ocr {
    DEFINES += OCR
    SOURCES += src/QuickEditor.cpp
    HEADERS += include/QuickEditor.h
    LIBS += -ltesseract
}

FORMS += \
    include/mainwindow.ui \
    include/settingswindow.ui \

RESOURCES += \
    resources/resources.qrc

LIBS += \
    -lX11 -lXi

CONFIG += \
    c++14 \
