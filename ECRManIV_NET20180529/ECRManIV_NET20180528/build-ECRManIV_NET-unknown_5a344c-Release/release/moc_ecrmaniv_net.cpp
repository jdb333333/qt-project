/****************************************************************************
** Meta object code from reading C++ file 'ecrmaniv_net.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ECRManIV_NET/ecrmaniv_net.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ecrmaniv_net.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ECRManIV_NET[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      55,   39,   13,   13, 0x08,
      82,   39,   13,   13, 0x08,
     117,  110,   13,   13, 0x08,
     139,  133,   13,   13, 0x08,
     177,   13,   13,   13, 0x08,
     192,   13,   13,   13, 0x08,
     213,  205,   13,   13, 0x08,
     236,  205,   13,   13, 0x08,
     259,   13,   13,   13, 0x08,
     278,   13,   13,   13, 0x08,
     297,   13,   13,   13, 0x08,
     325,   13,   13,   13, 0x08,
     342,   13,   13,   13, 0x08,
     366,   13,   13,   13, 0x08,
     393,   13,   13,   13, 0x08,
     411,   13,   13,   13, 0x08,
     431,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ECRManIV_NET[] = {
    "ECRManIV_NET\0\0on_actionADD_triggered()\0"
    "ip1,ip2,ip3,ip4\0getipitem(int,int,int,int)\0"
    "setlocalip(int,int,int,int)\0ipitem\0"
    "searchipok(int)\0index\0"
    "on_tableWidget_2_clicked(QModelIndex)\0"
    "tcpunconnect()\0tcpconnect()\0buf,len\0"
    "tcprecvdata(char*,int)\0tcpsenddata(char*,int)\0"
    "on_zport_clicked()\0on_clerk_clicked()\0"
    "on_actionDELETE_triggered()\0"
    "on_plu_clicked()\0on_pushButton_clicked()\0"
    "on_actionLOCAL_triggered()\0on_dept_clicked()\0"
    "on_ticket_clicked()\0on_disc_clicked()\0"
};

void ECRManIV_NET::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ECRManIV_NET *_t = static_cast<ECRManIV_NET *>(_o);
        switch (_id) {
        case 0: _t->on_actionADD_triggered(); break;
        case 1: _t->getipitem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->setlocalip((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: _t->searchipok((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_tableWidget_2_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->tcpunconnect(); break;
        case 6: _t->tcpconnect(); break;
        case 7: _t->tcprecvdata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->tcpsenddata((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->on_zport_clicked(); break;
        case 10: _t->on_clerk_clicked(); break;
        case 11: _t->on_actionDELETE_triggered(); break;
        case 12: _t->on_plu_clicked(); break;
        case 13: _t->on_pushButton_clicked(); break;
        case 14: _t->on_actionLOCAL_triggered(); break;
        case 15: _t->on_dept_clicked(); break;
        case 16: _t->on_ticket_clicked(); break;
        case 17: _t->on_disc_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ECRManIV_NET::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ECRManIV_NET::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ECRManIV_NET,
      qt_meta_data_ECRManIV_NET, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ECRManIV_NET::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ECRManIV_NET::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ECRManIV_NET::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ECRManIV_NET))
        return static_cast<void*>(const_cast< ECRManIV_NET*>(this));
    return QWidget::qt_metacast(_clname);
}

int ECRManIV_NET::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
