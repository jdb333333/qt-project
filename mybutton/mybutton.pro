#-------------------------------------------------
#
# Project created by QtCreator 2018-06-05T09:10:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mybutton
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    button/switchbutton.cpp

HEADERS  += widget.h \
    button/switchbutton.h

FORMS    += widget.ui

RESOURCES += \
    btn.qrc
