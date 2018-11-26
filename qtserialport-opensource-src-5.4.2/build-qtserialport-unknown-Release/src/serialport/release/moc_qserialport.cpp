/****************************************************************************
** Meta object code from reading C++ file 'qserialport.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../qtserialport-opensource-src-5.4.2/src/serialport/qserialport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qserialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QSerialPort[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       8,   84, // properties
       8,  116, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   13,   12,   12, 0x05,
      90,   81,   12,   12, 0x05,
     136,  129,   12,   12, 0x05,
     180,  171,   12,   12, 0x05,
     231,  219,   12,   12, 0x05,
     283,  276,   12,   12, 0x05,
     340,  336,   12,   12, 0x05,
     371,  336,   12,   12, 0x05,
     414,  398,   12,   12, 0x05,
     458,  450,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     500,   12,  495,   12, 0x08,
     532,   12,  495,   12, 0x08,
     555,   12,  495,   12, 0x08,
     579,   12,  495,   12, 0x08,

 // properties: name, type, flags
     607,  600, 0x02495103,
      81,  616, 0x0049510b,
     129,  625, 0x0049510b,
     171,  632, 0x0049510b,
     219,  641, 0x0049510b,
     653,  495, 0x01495103,
     671,  495, 0x01495103,
     701,  685, 0x0049500d,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       6,
       7,
       8,

 // enums: name, flags, count, data
     707, 0x1,    3,  148,
     718, 0x0,    9,  154,
     616, 0x0,    5,  172,
     625, 0x0,    6,  182,
     632, 0x0,    4,  194,
     641, 0x0,    4,  202,
     727, 0x1,   11,  210,
     685, 0x0,   14,  232,

 // enum data: key, value
     741, uint(QSerialPort::Input),
     747, uint(QSerialPort::Output),
     754, uint(QSerialPort::AllDirections),
     768, uint(QSerialPort::Baud1200),
     777, uint(QSerialPort::Baud2400),
     786, uint(QSerialPort::Baud4800),
     795, uint(QSerialPort::Baud9600),
     804, uint(QSerialPort::Baud19200),
     814, uint(QSerialPort::Baud38400),
     824, uint(QSerialPort::Baud57600),
     834, uint(QSerialPort::Baud115200),
     845, uint(QSerialPort::UnknownBaud),
     857, uint(QSerialPort::Data5),
     863, uint(QSerialPort::Data6),
     869, uint(QSerialPort::Data7),
     875, uint(QSerialPort::Data8),
     881, uint(QSerialPort::UnknownDataBits),
     897, uint(QSerialPort::NoParity),
     906, uint(QSerialPort::EvenParity),
     917, uint(QSerialPort::OddParity),
     927, uint(QSerialPort::SpaceParity),
     939, uint(QSerialPort::MarkParity),
     950, uint(QSerialPort::UnknownParity),
     964, uint(QSerialPort::OneStop),
     972, uint(QSerialPort::OneAndHalfStop),
     987, uint(QSerialPort::TwoStop),
     995, uint(QSerialPort::UnknownStopBits),
    1011, uint(QSerialPort::NoFlowControl),
    1025, uint(QSerialPort::HardwareControl),
    1041, uint(QSerialPort::SoftwareControl),
    1057, uint(QSerialPort::UnknownFlowControl),
    1076, uint(QSerialPort::NoSignal),
    1085, uint(QSerialPort::TransmittedDataSignal),
    1107, uint(QSerialPort::ReceivedDataSignal),
    1126, uint(QSerialPort::DataTerminalReadySignal),
    1150, uint(QSerialPort::DataCarrierDetectSignal),
    1174, uint(QSerialPort::DataSetReadySignal),
    1193, uint(QSerialPort::RingIndicatorSignal),
    1213, uint(QSerialPort::RequestToSendSignal),
    1233, uint(QSerialPort::ClearToSendSignal),
    1251, uint(QSerialPort::SecondaryTransmittedDataSignal),
    1282, uint(QSerialPort::SecondaryReceivedDataSignal),
    1310, uint(QSerialPort::NoError),
    1318, uint(QSerialPort::DeviceNotFoundError),
    1338, uint(QSerialPort::PermissionError),
    1354, uint(QSerialPort::OpenError),
    1364, uint(QSerialPort::ParityError),
    1376, uint(QSerialPort::FramingError),
    1389, uint(QSerialPort::BreakConditionError),
    1409, uint(QSerialPort::WriteError),
    1420, uint(QSerialPort::ReadError),
    1430, uint(QSerialPort::ResourceError),
    1444, uint(QSerialPort::UnsupportedOperationError),
    1470, uint(QSerialPort::UnknownError),
    1483, uint(QSerialPort::TimeoutError),
    1496, uint(QSerialPort::NotOpenError),

       0        // eod
};

static const char qt_meta_stringdata_QSerialPort[] = {
    "QSerialPort\0\0baudRate,directions\0"
    "baudRateChanged(qint32,QSerialPort::Directions)\0"
    "dataBits\0dataBitsChanged(QSerialPort::DataBits)\0"
    "parity\0parityChanged(QSerialPort::Parity)\0"
    "stopBits\0stopBitsChanged(QSerialPort::StopBits)\0"
    "flowControl\0flowControlChanged(QSerialPort::FlowControl)\0"
    "policy\0dataErrorPolicyChanged(QSerialPort::DataErrorPolicy)\0"
    "set\0dataTerminalReadyChanged(bool)\0"
    "requestToSendChanged(bool)\0serialPortError\0"
    "error(QSerialPort::SerialPortError)\0"
    "restore\0settingsRestoredOnCloseChanged(bool)\0"
    "bool\0_q_completeAsyncCommunication()\0"
    "_q_completeAsyncRead()\0_q_completeAsyncWrite()\0"
    "_q_startAsyncWrite()\0qint32\0baudRate\0"
    "DataBits\0Parity\0StopBits\0FlowControl\0"
    "dataTerminalReady\0requestToSend\0"
    "SerialPortError\0error\0Directions\0"
    "BaudRate\0PinoutSignals\0Input\0Output\0"
    "AllDirections\0Baud1200\0Baud2400\0"
    "Baud4800\0Baud9600\0Baud19200\0Baud38400\0"
    "Baud57600\0Baud115200\0UnknownBaud\0Data5\0"
    "Data6\0Data7\0Data8\0UnknownDataBits\0"
    "NoParity\0EvenParity\0OddParity\0SpaceParity\0"
    "MarkParity\0UnknownParity\0OneStop\0"
    "OneAndHalfStop\0TwoStop\0UnknownStopBits\0"
    "NoFlowControl\0HardwareControl\0"
    "SoftwareControl\0UnknownFlowControl\0"
    "NoSignal\0TransmittedDataSignal\0"
    "ReceivedDataSignal\0DataTerminalReadySignal\0"
    "DataCarrierDetectSignal\0DataSetReadySignal\0"
    "RingIndicatorSignal\0RequestToSendSignal\0"
    "ClearToSendSignal\0SecondaryTransmittedDataSignal\0"
    "SecondaryReceivedDataSignal\0NoError\0"
    "DeviceNotFoundError\0PermissionError\0"
    "OpenError\0ParityError\0FramingError\0"
    "BreakConditionError\0WriteError\0ReadError\0"
    "ResourceError\0UnsupportedOperationError\0"
    "UnknownError\0TimeoutError\0NotOpenError\0"
};

void QSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QSerialPort *_t = static_cast<QSerialPort *>(_o);
        switch (_id) {
        case 0: _t->baudRateChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QSerialPort::Directions(*)>(_a[2]))); break;
        case 1: _t->dataBitsChanged((*reinterpret_cast< QSerialPort::DataBits(*)>(_a[1]))); break;
        case 2: _t->parityChanged((*reinterpret_cast< QSerialPort::Parity(*)>(_a[1]))); break;
        case 3: _t->stopBitsChanged((*reinterpret_cast< QSerialPort::StopBits(*)>(_a[1]))); break;
        case 4: _t->flowControlChanged((*reinterpret_cast< QSerialPort::FlowControl(*)>(_a[1]))); break;
        case 5: _t->dataErrorPolicyChanged((*reinterpret_cast< QSerialPort::DataErrorPolicy(*)>(_a[1]))); break;
        case 6: _t->dataTerminalReadyChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->requestToSendChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->error((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 9: _t->settingsRestoredOnCloseChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: { bool _r = _t->d_func()->_q_completeAsyncCommunication();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->d_func()->_q_completeAsyncRead();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->d_func()->_q_completeAsyncWrite();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->d_func()->_q_startAsyncWrite();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QSerialPort::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QSerialPort::staticMetaObject = {
    { &QIODevice::staticMetaObject, qt_meta_stringdata_QSerialPort,
      qt_meta_data_QSerialPort, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QSerialPort::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialPort))
        return static_cast<void*>(const_cast< QSerialPort*>(this));
    return QIODevice::qt_metacast(_clname);
}

int QSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIODevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint32*>(_v) = baudRate(); break;
        case 1: *reinterpret_cast< DataBits*>(_v) = dataBits(); break;
        case 2: *reinterpret_cast< Parity*>(_v) = parity(); break;
        case 3: *reinterpret_cast< StopBits*>(_v) = stopBits(); break;
        case 4: *reinterpret_cast< FlowControl*>(_v) = flowControl(); break;
        case 5: *reinterpret_cast< bool*>(_v) = isDataTerminalReady(); break;
        case 6: *reinterpret_cast< bool*>(_v) = isRequestToSend(); break;
        case 7: *reinterpret_cast< SerialPortError*>(_v) = error(); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setBaudRate(*reinterpret_cast< qint32*>(_v)); break;
        case 1: setDataBits(*reinterpret_cast< DataBits*>(_v)); break;
        case 2: setParity(*reinterpret_cast< Parity*>(_v)); break;
        case 3: setStopBits(*reinterpret_cast< StopBits*>(_v)); break;
        case 4: setFlowControl(*reinterpret_cast< FlowControl*>(_v)); break;
        case 5: setDataTerminalReady(*reinterpret_cast< bool*>(_v)); break;
        case 6: setRequestToSend(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::ResetProperty) {
        switch (_id) {
        case 7: clearError(); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QSerialPort::baudRateChanged(qint32 _t1, QSerialPort::Directions _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QSerialPort::dataBitsChanged(QSerialPort::DataBits _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QSerialPort::parityChanged(QSerialPort::Parity _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QSerialPort::stopBitsChanged(QSerialPort::StopBits _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QSerialPort::flowControlChanged(QSerialPort::FlowControl _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QSerialPort::dataErrorPolicyChanged(QSerialPort::DataErrorPolicy _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QSerialPort::dataTerminalReadyChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QSerialPort::requestToSendChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QSerialPort::error(QSerialPort::SerialPortError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QSerialPort::settingsRestoredOnCloseChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
