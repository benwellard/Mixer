#-------------------------------------------------
#
# Project created by QtCreator 2014-07-07T15:19:20
#
#-------------------------------------------------

QT       += core gui\
            androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextFinder
TEMPLATE = app


SOURCES += main.cpp\
    mixer.cpp \
    volumelevel.cpp \
    volslider.cpp \
    decibelworker.cpp \
    usb_mixer.cpp \
    controller.cpp \
    volumelevelintermixer.cpp \
    interface.cpp \
    mixer_main.cpp \
    qfingerscrollarea.cpp \
    channelbox.cpp \
    outputbox.cpp

HEADERS  += \
    mixer.h \
    volumelevel.h \
    volslider.h \
    decibelworker.h \
    usb_mixer.h \
    controller.h \
    volumelevelintermixer.h \
    interface.h \
    mixer_main.h \
    libusb.h \
    qfingerscrollarea.h \
    channelbox.h \
    outputbox.h

FORMS    += \
    mixer_main.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES +=



ANDROID_PACKAGE_SOURCE_DIR += $$PWD/

ANDROID_PACKAGE_SOURCE_DIR/src = $$PWD/src

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/




#macx:LIBS += -L$$PWD/ -lusb-1.0.0

#INCLUDEPATH += $$PWD/
#DEPENDPATH += $$PWD/

LIBS += -L$$PWD/ -lusb1.0

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
