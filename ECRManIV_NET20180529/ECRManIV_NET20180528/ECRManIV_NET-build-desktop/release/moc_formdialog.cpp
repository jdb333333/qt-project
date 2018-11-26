/****************************************************************************
** Meta object code from reading C++ file 'formdialog.h'
**
** Created: Tue May 29 10:39:49 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ECRManIV_NET/formdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_formDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      28,   11,   11,   11, 0x05,
      50,   42,   11,   11, 0x05,
      70,   42,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      98,   90,   11,   11, 0x08,
     119,  114,   11,   11, 0x08,
     133,   11,   11,   11, 0x08,
     155,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_formDialog[] = {
    "formDialog\0\0unconnecthost()\0connecthost()\0"
    "buf,len\0recvdata(char*,int)\0"
    "senddata(char*,int)\0sizelen\0recvdataok(int)\0"
    "type\0tcpstate(int)\0on_openfile_clicked()\0"
    "on_update_clicked()\0"
};

const QMetaObject formDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_formDialog,
      qt_meta_data_formDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &formDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *formDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *formDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_formDialog))
        return static_cast<void*>(const_cast< formDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int formDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: unconnecthost(); break;
        case 1: connecthost(); break;
        case 2: recvdata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: senddata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: recvdataok((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: tcpstate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_openfile_clicked(); break;
        case 7: on_update_clicked(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void formDialog::unconnecthost()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void formDialog::connecthost()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void formDialog::recvdata(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void formDialog::senddata(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
