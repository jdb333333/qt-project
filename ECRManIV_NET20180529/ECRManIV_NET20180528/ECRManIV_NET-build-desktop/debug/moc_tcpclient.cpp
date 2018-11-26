/****************************************************************************
** Meta object code from reading C++ file 'tcpclient.h'
**
** Created: Mon May 28 15:43:14 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ECRManIV_NET/tcpclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_tcpclient[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x05,
      40,   35,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   10,   10,   10, 0x08,
      72,   10,   68,   10, 0x08,
      87,   10,   10,   10, 0x08,
     136,  130,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_tcpclient[] = {
    "tcpclient\0\0sizelen\0recvdataok(int)\0"
    "type\0tcpstate(int)\0readMessage()\0int\0"
    "writeMessage()\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "state\0sltStateChanged(QAbstractSocket::SocketState)\0"
};

const QMetaObject tcpclient::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_tcpclient,
      qt_meta_data_tcpclient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &tcpclient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *tcpclient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *tcpclient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcpclient))
        return static_cast<void*>(const_cast< tcpclient*>(this));
    return QWidget::qt_metacast(_clname);
}

int tcpclient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: recvdataok((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: tcpstate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: readMessage(); break;
        case 3: { int _r = writeMessage();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: sltStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void tcpclient::recvdataok(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tcpclient::tcpstate(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
