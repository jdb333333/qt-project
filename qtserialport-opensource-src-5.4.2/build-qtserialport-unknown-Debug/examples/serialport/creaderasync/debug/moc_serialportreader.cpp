/****************************************************************************
** Meta object code from reading C++ file 'serialportreader.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../qtserialport-opensource-src-5.4.2/examples/serialport/creaderasync/serialportreader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialportreader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SerialPortReader[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      36,   17,   17,   17, 0x08,
      58,   52,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SerialPortReader[] = {
    "SerialPortReader\0\0handleReadyRead()\0"
    "handleTimeout()\0error\0"
    "handleError(QSerialPort::SerialPortError)\0"
};

void SerialPortReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialPortReader *_t = static_cast<SerialPortReader *>(_o);
        switch (_id) {
        case 0: _t->handleReadyRead(); break;
        case 1: _t->handleTimeout(); break;
        case 2: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SerialPortReader::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialPortReader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SerialPortReader,
      qt_meta_data_SerialPortReader, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialPortReader::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialPortReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialPortReader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPortReader))
        return static_cast<void*>(const_cast< SerialPortReader*>(this));
    return QObject::qt_metacast(_clname);
}

int SerialPortReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
