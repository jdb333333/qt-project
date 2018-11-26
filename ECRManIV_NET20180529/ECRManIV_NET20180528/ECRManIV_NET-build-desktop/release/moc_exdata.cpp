/****************************************************************************
** Meta object code from reading C++ file 'exdata.h'
**
** Created: Tue May 29 10:39:38 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ECRManIV_NET/exdata.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'exdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_exdata[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      24,    7,    7,    7, 0x05,
      46,   38,    7,    7, 0x05,
      66,   38,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      86,    7,    7,    7, 0x08,
     112,    7,    7,    7, 0x08,
     134,    7,    7,    7, 0x08,
     166,  158,    7,    7, 0x08,
     187,  182,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_exdata[] = {
    "exdata\0\0unconnecthost()\0connecthost()\0"
    "buf,len\0recvdata(char*,int)\0"
    "senddata(char*,int)\0on_pushButton_2_clicked()\0"
    "on_openfile_clicked()\0on_pushButton_clicked()\0"
    "sizelen\0recvdataok(int)\0type\0tcpstate(int)\0"
};

const QMetaObject exdata::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_exdata,
      qt_meta_data_exdata, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &exdata::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *exdata::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *exdata::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_exdata))
        return static_cast<void*>(const_cast< exdata*>(this));
    return QWidget::qt_metacast(_clname);
}

int exdata::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: unconnecthost(); break;
        case 1: connecthost(); break;
        case 2: recvdata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: senddata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: on_pushButton_2_clicked(); break;
        case 5: on_openfile_clicked(); break;
        case 6: on_pushButton_clicked(); break;
        case 7: recvdataok((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: tcpstate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void exdata::unconnecthost()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void exdata::connecthost()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void exdata::recvdata(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void exdata::senddata(char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
