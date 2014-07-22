#-------------------------------------------------
#
# Project created by QtCreator 2014-07-07T15:19:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextFinder
TEMPLATE = app


SOURCES += main.cpp\
    mixer.cpp \
    volumelevel.cpp \
    volslider.cpp \
    decibelworker.cpp \
    usb_mixer.cpp \
    mixer_app.cpp \
    controller.cpp \
    volumelevelintermixer.cpp \
    interface.cpp \
    mixer_main.cpp

HEADERS  += \
    mixer.h \
    volumelevel.h \
    volslider.h \
    decibelworker.h \
    libusb.h \
    usb_mixer.h \
    controller.h \
    volumelevelintermixer.h \
    interface.h \
    mixer_main.h

FORMS    += \
    mixer_main.ui

RESOURCES +=

OTHER_FILES +=



macx: LIBS += -L$$PWD/ -lusb-1.0.0

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/


