/****************************************************************************
** Meta object code from reading C++ file 'volslider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Work_Files/volslider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'volslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VolSlider_t {
    QByteArrayData data[13];
    char stringdata[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VolSlider_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VolSlider_t qt_meta_stringdata_VolSlider = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 9),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 5),
QT_MOC_LITERAL(4, 27, 6),
QT_MOC_LITERAL(5, 34, 18),
QT_MOC_LITERAL(6, 53, 7),
QT_MOC_LITERAL(7, 61, 16),
QT_MOC_LITERAL(8, 78, 12),
QT_MOC_LITERAL(9, 91, 12),
QT_MOC_LITERAL(10, 104, 13),
QT_MOC_LITERAL(11, 118, 10),
QT_MOC_LITERAL(12, 129, 11)
    },
    "VolSlider\0emitIndex\0\0index\0volume\0"
    "emitUnmutedChannel\0channel\0emitMutedChannel\0"
    "currentValue\0releaseIndex\0changeChannel\0"
    "channelSel\0muteChannel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VolSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    1,   49,    2, 0x06 /* Public */,
       7,    2,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   57,    2, 0x0a /* Public */,
      10,    1,   60,    2, 0x0a /* Public */,
      12,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,

       0        // eod
};

void VolSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VolSlider *_t = static_cast<VolSlider *>(_o);
        switch (_id) {
        case 0: _t->emitIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->emitUnmutedChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->emitMutedChannel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->releaseIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->muteChannel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VolSlider::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolSlider::emitIndex)) {
                *result = 0;
            }
        }
        {
            typedef void (VolSlider::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolSlider::emitUnmutedChannel)) {
                *result = 1;
            }
        }
        {
            typedef void (VolSlider::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolSlider::emitMutedChannel)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject VolSlider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_VolSlider.data,
      qt_meta_data_VolSlider,  qt_static_metacall, 0, 0}
};


const QMetaObject *VolSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VolSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VolSlider.stringdata))
        return static_cast<void*>(const_cast< VolSlider*>(this));
    return QSlider::qt_metacast(_clname);
}

int VolSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VolSlider::emitIndex(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VolSlider::emitUnmutedChannel(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VolSlider::emitMutedChannel(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
