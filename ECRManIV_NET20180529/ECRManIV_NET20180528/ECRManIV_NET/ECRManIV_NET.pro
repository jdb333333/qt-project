#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T11:20:27
#
#-------------------------------------------------

QT       += core gui
QT += network sql

CONFIG += qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ECRManIV_NET
TEMPLATE = app


SOURCES += main.cpp\
        ecrmaniv_net.cpp \
    netdialog.cpp \
    tcpclient.cpp \
    clerk/clerk.cpp \
    dept/dept.cpp \
    reportdialog.cpp \
    reportdb.cpp \
    itemreport.cpp \
    reportdisp.cpp \
    tcpthread.cpp \
    excelbase.cpp \
    excelbaseprivate.cpp \
    udpclient.cpp \
    qvariantlistlistmodel.cpp \
    plu.cpp \
    formdialog.cpp \
    mycheckboxheader.cpp \
    checkbox_header.cpp \
    button/switchbutton.cpp \
    ticket.cpp \
    formwidget.cpp

HEADERS  += ecrmaniv_net.h \
    netdialog.h \
    tcpclient.h \
    clerk/clerk.h \
    dept/dept.h \
    reportdialog.h \
    reportdb.h \
    itemreport.h \
    reportdisp.h \
    tcpthread.h \
    excelbase.h \
    excelbaseprivate.h \
    udpclient.h \
    qvariantlistlistmodel.h \
    plu.h \
    formdialog.h \
    mycheckboxheader.h \
    checkbox_header.h \
    button/switchbutton.h \
    ticket.h \
    formwidget.h

FORMS    += ecrmaniv_net.ui \
    netdialog.ui \
    reportdialog.ui \
    itemreport.ui \
    reportdisp.ui \
    formdialog.ui \
    ticket.ui \
    formwidget.ui

RESOURCES += \
    ecrmainiv_rc.qrc

#RC_ICONS = myico.ico
RC_FILE += myico.rc
