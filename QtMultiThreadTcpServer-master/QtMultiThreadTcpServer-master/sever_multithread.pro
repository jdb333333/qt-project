#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T20:38:29
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sever_multithread
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    serverthread.cpp \
    server.cpp \
    mysocket.cpp \
    database/flowbill/flowbilldb.cpp \
    database/connectionpool.cpp

HEADERS  += dialog.h \
    serverthread.h \
    server.h \
    mysocket.h \
    database/flowbill/flowbilldb.h \
    database/connectionpool.h

FORMS    += dialog.ui
