/****************************************************************************
** Meta object code from reading C++ file 'mixer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Work_Files/mixer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mixer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Mixer_t {
    QByteArrayData data[27];
    char stringdata[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mixer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mixer_t qt_meta_stringdata_Mixer = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 10),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 3),
QT_MOC_LITERAL(4, 22, 7),
QT_MOC_LITERAL(5, 30, 12),
QT_MOC_LITERAL(6, 43, 8),
QT_MOC_LITERAL(7, 52, 17),
QT_MOC_LITERAL(8, 70, 6),
QT_MOC_LITERAL(9, 77, 12),
QT_MOC_LITERAL(10, 90, 8),
QT_MOC_LITERAL(11, 99, 14),
QT_MOC_LITERAL(12, 114, 11),
QT_MOC_LITERAL(13, 126, 1),
QT_MOC_LITERAL(14, 128, 10),
QT_MOC_LITERAL(15, 139, 9),
QT_MOC_LITERAL(16, 149, 16),
QT_MOC_LITERAL(17, 166, 16),
QT_MOC_LITERAL(18, 183, 21),
QT_MOC_LITERAL(19, 205, 7),
QT_MOC_LITERAL(20, 213, 23),
QT_MOC_LITERAL(21, 237, 6),
QT_MOC_LITERAL(22, 244, 10),
QT_MOC_LITERAL(23, 255, 15),
QT_MOC_LITERAL(24, 271, 17),
QT_MOC_LITERAL(25, 289, 12),
QT_MOC_LITERAL(26, 302, 5)
    },
    "Mixer\0emitVolume\0\0vol\0indexNo\0"
    "emitChannels\0channels\0emitCurrentOutput\0"
    "output\0changeVolume\0indexVal\0"
    "constructMixer\0setChannels\0n\0addChannel\0"
    "newSlider\0saveVolumesArray\0loadVolumesArray\0"
    "muteChannelController\0channel\0"
    "unMuteChannelController\0volume\0"
    "setOutputs\0populateOutputs\0dePopulateOutputs\0"
    "deMapChannel\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mixer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,
       5,    1,   99,    2, 0x06 /* Public */,
       7,    1,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,  105,    2, 0x0a /* Public */,
      11,    1,  110,    2, 0x0a /* Public */,
      12,    1,  113,    2, 0x0a /* Public */,
      14,    0,  116,    2, 0x0a /* Public */,
      15,    0,  117,    2, 0x0a /* Public */,
      16,    0,  118,    2, 0x0a /* Public */,
      17,    0,  119,    2, 0x0a /* Public */,
      18,    1,  120,    2, 0x0a /* Public */,
      20,    2,  123,    2, 0x0a /* Public */,
      22,    0,  128,    2, 0x0a /* Public */,
      23,    0,  129,    2, 0x0a /* Public */,
      24,    0,  130,    2, 0x0a /* Public */,
      25,    1,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,    3,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   19,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   26,

       0        // eod
};

void Mixer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Mixer *_t = static_cast<Mixer *>(_o);
        switch (_id) {
        case 0: _t->emitVolume((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->emitChannels((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->emitCurrentOutput((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeVolume((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->constructMixer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setChannels((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->addChannel(); break;
        case 7: _t->newSlider(); break;
        case 8: _t->saveVolumesArray(); break;
        case 9: _t->loadVolumesArray(); break;
        case 10: _t->muteChannelController((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->unMuteChannelController((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->setOutputs(); break;
        case 13: _t->populateOutputs(); break;
        case 14: _t->dePopulateOutputs(); break;
        case 15: _t->deMapChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Mixer::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mixer::emitVolume)) {
                *result = 0;
            }
        }
        {
            typedef void (Mixer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mixer::emitChannels)) {
                *result = 1;
            }
        }
        {
            typedef void (Mixer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mixer::emitCurrentOutput)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Mixer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Mixer.data,
      qt_meta_data_Mixer,  qt_static_metacall, 0, 0}
};


const QMetaObject *Mixer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mixer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mixer.stringdata))
        return static_cast<void*>(const_cast< Mixer*>(this));
    return QWidget::qt_metacast(_clname);
}

int Mixer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Mixer::emitVolume(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mixer::emitChannels(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mixer::emitCurrentOutput(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
