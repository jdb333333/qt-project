#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T14:39:30
#
#-------------------------------------------------

QT       += core gui
        #axcontainer  #//使用axcontainer�?;
CONFIG += qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testReadExcelDll
TEMPLATE = app

DESTDIR = ..\MyTest
CONFIG += \
        c++11  #//使用C++11规范;支持lamda写法;
LIBS += $$DESTDIR/ReadExcelClass.lib


SOURCES += main.cpp\
        mainwindow.cpp \
    ReadExcelClass.cpp

HEADERS  += mainwindow.h \
    ReadExcelClass.h

SUBDIRS += \
    ../ReadExcelClass/ReadExcelClass.pro
