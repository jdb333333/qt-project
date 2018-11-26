#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T11:30:23
#
#-------------------------------------------------

QT       += core gui widgets \
        axcontainer     #//使用axcontainer时;

TARGET = ReadExcelClass
TEMPLATE = lib

///
DESTDIR = ..\MyTest
DEFINES += READEXCELCLASS_LIBRARY
#CONFIG += qaxcontainer #//使用qaxcontainer时;
///--

SOURCES += ReadExcelClass.cpp

HEADERS += ReadExcelClass.h\
    #    readexcelclass_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
