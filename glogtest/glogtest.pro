#-------------------------------------------------
#
# Project created by QtCreator 2018-09-12T09:37:40
#
#-------------------------------------------------

QT       += core gui
CONFIG += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = glogtest
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    rs232thread.cpp \
    configure.cpp \
    switchbutton.cpp

HEADERS  += dialog.h \
    rs232thread.h \
    configure.h \
    switchbutton.h

FORMS    += dialog.ui

RESOURCES += \
    image.qrc

RC_FILE += myico.rc
