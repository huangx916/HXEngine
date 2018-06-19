/****************************************************************************
** Meta object code from reading C++ file 'HXInspectorWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HXInspectorWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HXInspectorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HXInspectorWidget_t {
    QByteArrayData data[12];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HXInspectorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HXInspectorWidget_t qt_meta_stringdata_HXInspectorWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "HXInspectorWidget"
QT_MOC_LITERAL(1, 18, 21), // "PositionXValueChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 5), // "value"
QT_MOC_LITERAL(4, 47, 21), // "PositionYValueChanged"
QT_MOC_LITERAL(5, 69, 21), // "PositionZValueChanged"
QT_MOC_LITERAL(6, 91, 21), // "RotationXValueChanged"
QT_MOC_LITERAL(7, 113, 21), // "RotationYValueChanged"
QT_MOC_LITERAL(8, 135, 21), // "RotationZValueChanged"
QT_MOC_LITERAL(9, 157, 18), // "ScaleXValueChanged"
QT_MOC_LITERAL(10, 176, 18), // "ScaleYValueChanged"
QT_MOC_LITERAL(11, 195, 18) // "ScaleZValueChanged"

    },
    "HXInspectorWidget\0PositionXValueChanged\0"
    "\0value\0PositionYValueChanged\0"
    "PositionZValueChanged\0RotationXValueChanged\0"
    "RotationYValueChanged\0RotationZValueChanged\0"
    "ScaleXValueChanged\0ScaleYValueChanged\0"
    "ScaleZValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HXInspectorWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    1,   62,    2, 0x0a /* Public */,
       5,    1,   65,    2, 0x0a /* Public */,
       6,    1,   68,    2, 0x0a /* Public */,
       7,    1,   71,    2, 0x0a /* Public */,
       8,    1,   74,    2, 0x0a /* Public */,
       9,    1,   77,    2, 0x0a /* Public */,
      10,    1,   80,    2, 0x0a /* Public */,
      11,    1,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

       0        // eod
};

void HXInspectorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HXInspectorWidget *_t = static_cast<HXInspectorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PositionXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->PositionYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->PositionZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->RotationXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->RotationYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->RotationZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->ScaleXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->ScaleYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->ScaleZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HXInspectorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HXInspectorWidget.data,
      qt_meta_data_HXInspectorWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HXInspectorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HXInspectorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HXInspectorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HXInspectorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
