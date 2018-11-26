#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T11:20:27
#
#-------------------------------------------------

QT       += core gui
QT += network sql

CONFIG += qaxcontainer
CONFIG += serialport

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
    formwidget.cpp \
    disc/disc.cpp \
    tax/tax.cpp \
    offer/offprice.cpp \
    flowbill/flowbill.cpp \
    ejdb/ejdb.cpp \
    comm.cpp \
    csv/csv.cpp \
    logindialog.cpp \
    usr/usrdialog.cpp \
    usr/usrdb.cpp \
    usr/usrmoddialog.cpp \
    update/updateapp.cpp \
    RS232/rs232dialog.cpp \
    RS232/rs232thread.cpp

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
    formwidget.h \
    disc/disc.h \
    tax/tax.h \
    offer/offprice.h \
    flowbill/flowbill.h \
    ejdb/ejdb.h \
    comm.h \
    csv/csv.h \
    logindialog.h \
    usr/usrdialog.h \
    usr/usrdb.h \
    usr/usrmoddialog.h \
    message/message.h \
    update/updateapp.h \
    RS232/rs232dialog.h \
    RS232/rs232thread.h

FORMS    += ecrmaniv_net.ui \
    netdialog.ui \
    reportdialog.ui \
    itemreport.ui \
    reportdisp.ui \
    formdialog.ui \
    ticket.ui \
    formwidget.ui \
    logindialog.ui \
    usr/usrdialog.ui \
    usr/usrmoddialog.ui \
    RS232/rs232dialog.ui

RESOURCES += \
    ecrmainiv_rc.qrc

#RC_ICONS = myico.ico
RC_FILE += myico.rc
