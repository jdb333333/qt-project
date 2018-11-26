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
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      30,   13,   13,   13, 0x05,
      52,   44,   13,   13, 0x05,
      72,   44,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      92,   13,   13,   13, 0x08,
     124,  116,   13,   13, 0x08,
     145,  140,   13,   13, 0x08,
     159,   13,   13,   13, 0x08,
     183,   13,   13,   13, 0x08,
     207,   13,   13,   13, 0x08,
     227,   13,   13,   13, 0x08,
     247,   13,   13,   13, 0x08,
     271,   13,   13,   13, 0x08,
     293,   13,   13,   13, 0x08,
     310,   13,   13,   13, 0x08,
     336,   13,   13,   13, 0x08,
     362,   13,   13,   13, 0x08,
     384,   13,   13,   13, 0x08,
     406,   13,   13,   13, 0x08,
     432,   13,   13,   13, 0x08,
     456,   13,   13,   13, 0x08,
     475,   13,   13,   13, 0x08,
     501,   13,   13,   13, 0x08,
     523,   13,   13,   13, 0x08,
     545,   13,   13,   13, 0x08,
     571,   13,   13,   13, 0x08,
     595,   13,   13,   13, 0x08,
     621,   13,   13,   13, 0x08,
     643,   13,   13,   13, 0x08,
     669,   13,   13,   13, 0x08,
     693,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_reportDialog[] = {
    "reportDialog\0\0unconnecthost()\0"
    "connecthost()\0buf,len\0recvdata(char*,int)\0"
    "senddata(char*,int)\0on_pushButton_clicked()\0"
    "sizelen\0recvdataok(int)\0type\0tcpstate(int)\0"
    "on_grandtotal_clicked()\0on_department_clicked()\0"
    "on_tender_clicked()\0on_drawer_clicked()\0"
    "on_correction_clicked()\0on_discount_clicked()\0"
    "on_tax_clicked()\0on_grandtotal_2_clicked()\0"
    "on_department_2_clicked()\0"
    "on_tender_2_clicked()\0on_drawer_2_clicked()\0"
    "on_correction_2_clicked()\0"
    "on_discount_2_clicked()\0on_tax_2_clicked()\0"
    "on_grandtotal_3_clicked()\0"
    "on_tender_3_clicked()\0on_drawer_3_clicked()\0"
    "on_correction_3_clicked()\0"
    "on_discount_3_clicked()\0"
    "on_grandtotal_4_clicked()\0"
    "on_tender_4_clicked()\0on_correction_4_clicked()\0"
    "on_discount_4_clicked()\0"
    "on_cleardbreport_clicked()\0"
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
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->recvdataok((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->tcpstate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_grandtotal_clicked(); break;
        case 8: _t->on_department_clicked(); break;
        case 9: _t->on_tender_clicked(); break;
        case 10: _t->on_drawer_clicked(); break;
        case 11: _t->on_correction_clicked(); break;
        case 12: _t->on_discount_clicked(); break;
        case 13: _t->on_tax_clicked(); break;
        case 14: _t->on_grandtotal_2_clicked(); break;
        case 15: _t->on_department_2_clicked(); break;
        case 16: _t->on_tender_2_clicked(); break;
        case 17: _t->on_drawer_2_clicked(); break;
        case 18: _t->on_correction_2_clicked(); break;
        case 19: _t->on_discount_2_clicked(); break;
        case 20: _t->on_tax_2_clicked(); break;
        case 21: _t->on_grandtotal_3_clicked(); break;
        case 22: _t->on_tender_3_clicked(); break;
        case 23: _t->on_drawer_3_clicked(); break;
        case 24: _t->on_correction_3_clicked(); break;
        case 25: _t->on_discount_3_clicked(); break;
        case 26: _t->on_grandtotal_4_clicked(); break;
        case 27: _t->on_tender_4_clicked(); break;
        case 28: _t->on_correction_4_clicked(); break;
        case 29: _t->on_discount_4_clicked(); break;
        case 30: _t->on_cleardbreport_clicked(); break;
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
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
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
QT_END_MOC_NAMESPACE
