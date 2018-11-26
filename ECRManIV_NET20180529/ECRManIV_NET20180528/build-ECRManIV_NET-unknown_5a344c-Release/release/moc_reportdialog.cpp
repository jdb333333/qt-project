/****************************************************************************
** Meta object code from reading C++ file 'reportdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ECRManIV_NET/reportdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reportdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_reportDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      30,   13,   13,   13, 0x05,
      52,   44,   13,   13, 0x05,
      72,   44,   13,   13, 0x05,
      95,   92,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     116,   13,   13,   13, 0x08,
     150,  142,   13,   13, 0x08,
     171,  166,   13,   13, 0x08,
     185,  166,   13,   13, 0x08,
     198,   13,   13,   13, 0x08,
     225,   13,   13,   13, 0x08,
     246,   13,   13,   13, 0x08,
     266,   13,   13,   13, 0x08,
     288,   13,   13,   13, 0x08,
     310,   13,   13,   13, 0x08,
     331,   13,   13,   13, 0x08,
     358,  352,   13,   13, 0x08,
     386,  378,   13,   13, 0x08,
     412,  406,   13,   13, 0x08,
     459,  448,   13,   13, 0x08,
     480,   13,   13,   13, 0x08,
     491,  448,   13,   13, 0x08,
     518,  448,   13,   13, 0x08,
     543,  448,   13,   13, 0x08,
     569,  448,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_reportDialog[] = {
    "reportDialog\0\0unconnecthost()\0"
    "connecthost()\0buf,len\0recvdata(char*,int)\0"
    "senddata(char*,int)\0IP\0setserverip(QString)\0"
    "on_DOWNLOADDATA_clicked()\0sizelen\0"
    "recvdataok(int)\0type\0tcpstate(int)\0"
    "dbstate(int)\0on_cleardbreport_clicked()\0"
    "on_TIMEBTN_clicked()\0on_PLUBTN_clicked()\0"
    "on_DAILYBTN_clicked()\0on_CLERKBTN_clicked()\0"
    "on_xreport_clicked()\0on_zreport_clicked()\0"
    "state\0slotsSelectAll(int)\0row,col\0"
    "changeTest(int,int)\0index\0"
    "on_tableWidget_clicked(QModelIndex)\0"
    "btnchecked\0checkedChanged(bool)\0"
    "showTime()\0zdailycheckedChanged(bool)\0"
    "zplucheckedChanged(bool)\0"
    "ztimecheckedChanged(bool)\0"
    "zclerkcheckedChanged(bool)\0"
};

void reportDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        reportDialog *_t = static_cast<reportDialog *>(_o);
        switch (_id) {
        case 0: _t->unconnecthost(); break;
        case 1: _t->connecthost(); break;
        case 2: _t->recvdata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->senddata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->setserverip((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->on_DOWNLOADDATA_clicked(); break;
        case 6: _t->recvdataok((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->tcpstate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->dbstate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_cleardbreport_clicked(); break;
        case 10: _t->on_TIMEBTN_clicked(); break;
        case 11: _t->on_PLUBTN_clicked(); break;
        case 12: _t->on_DAILYBTN_clicked(); break;
        case 13: _t->on_CLERKBTN_clicked(); break;
        case 14: _t->on_xreport_clicked(); break;
        case 15: _t->on_zreport_clicked(); break;
        case 16: _t->slotsSelectAll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->changeTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->on_tableWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 19: _t->checkedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->showTime(); break;
        case 21: _t->zdailycheckedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->zplucheckedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->ztimecheckedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->zclerkcheckedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData reportDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject reportDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_reportDialog,
      qt_meta_data_reportDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &reportDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *reportDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *reportDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_reportDialog))
        return static_cast<void*>(const_cast< reportDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int reportDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void reportDialog::unconnecthost()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void reportDialog::connecthost()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void reportDialog::recvdata(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void reportDialog::senddata(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void reportDialog::setserverip(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
