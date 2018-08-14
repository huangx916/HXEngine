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
    QByteArrayData data[79];
    char stringdata0[1536];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HXInspectorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HXInspectorWidget_t qt_meta_stringdata_HXInspectorWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "HXInspectorWidget"
QT_MOC_LITERAL(1, 18, 15), // "ActivityToggled"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "activity"
QT_MOC_LITERAL(4, 44, 13), // "StaticToggled"
QT_MOC_LITERAL(5, 58, 7), // "bStatic"
QT_MOC_LITERAL(6, 66, 17), // "CastShadowToggled"
QT_MOC_LITERAL(7, 84, 10), // "castShadow"
QT_MOC_LITERAL(8, 95, 14), // "LayerActivated"
QT_MOC_LITERAL(9, 110, 5), // "index"
QT_MOC_LITERAL(10, 116, 21), // "PositionXValueChanged"
QT_MOC_LITERAL(11, 138, 5), // "value"
QT_MOC_LITERAL(12, 144, 21), // "PositionYValueChanged"
QT_MOC_LITERAL(13, 166, 21), // "PositionZValueChanged"
QT_MOC_LITERAL(14, 188, 21), // "RotationXValueChanged"
QT_MOC_LITERAL(15, 210, 21), // "RotationYValueChanged"
QT_MOC_LITERAL(16, 232, 21), // "RotationZValueChanged"
QT_MOC_LITERAL(17, 254, 18), // "ScaleXValueChanged"
QT_MOC_LITERAL(18, 273, 18), // "ScaleYValueChanged"
QT_MOC_LITERAL(19, 292, 18), // "ScaleZValueChanged"
QT_MOC_LITERAL(20, 311, 10), // "FogToggled"
QT_MOC_LITERAL(21, 322, 6), // "useFog"
QT_MOC_LITERAL(22, 329, 16), // "FogTypeActivated"
QT_MOC_LITERAL(23, 346, 16), // "FogColorRChanged"
QT_MOC_LITERAL(24, 363, 16), // "FogColorGChanged"
QT_MOC_LITERAL(25, 380, 16), // "FogColorBChanged"
QT_MOC_LITERAL(26, 397, 15), // "FogStartChanged"
QT_MOC_LITERAL(27, 413, 13), // "FogEndChanged"
QT_MOC_LITERAL(28, 427, 17), // "FogDensityChanged"
QT_MOC_LITERAL(29, 445, 18), // "FogGradiantChanged"
QT_MOC_LITERAL(30, 464, 20), // "AmbientColorRChanged"
QT_MOC_LITERAL(31, 485, 20), // "AmbientColorGChanged"
QT_MOC_LITERAL(32, 506, 20), // "AmbientColorBChanged"
QT_MOC_LITERAL(33, 527, 13), // "CameraToggled"
QT_MOC_LITERAL(34, 541, 9), // "useCamera"
QT_MOC_LITERAL(35, 551, 18), // "CameraFieldChanged"
QT_MOC_LITERAL(36, 570, 17), // "CameraSizeChanged"
QT_MOC_LITERAL(37, 588, 17), // "CameraNearChanged"
QT_MOC_LITERAL(38, 606, 16), // "CameraFarChanged"
QT_MOC_LITERAL(39, 623, 22), // "CameraViewportXChanged"
QT_MOC_LITERAL(40, 646, 22), // "CameraViewportYChanged"
QT_MOC_LITERAL(41, 669, 22), // "CameraViewportWChanged"
QT_MOC_LITERAL(42, 692, 22), // "CameraViewportHChanged"
QT_MOC_LITERAL(43, 715, 18), // "ClearFlagActivated"
QT_MOC_LITERAL(44, 734, 15), // "BGColorRChanged"
QT_MOC_LITERAL(45, 750, 15), // "BGColorGChanged"
QT_MOC_LITERAL(46, 766, 15), // "BGColorBChanged"
QT_MOC_LITERAL(47, 782, 20), // "CullingMaskActivated"
QT_MOC_LITERAL(48, 803, 19), // "ProjectionActivated"
QT_MOC_LITERAL(49, 823, 12), // "DepthChanged"
QT_MOC_LITERAL(50, 836, 16), // "TransSyncOnClick"
QT_MOC_LITERAL(51, 853, 27), // "CameraPositionXValueChanged"
QT_MOC_LITERAL(52, 881, 27), // "CameraPositionYValueChanged"
QT_MOC_LITERAL(53, 909, 27), // "CameraPositionZValueChanged"
QT_MOC_LITERAL(54, 937, 27), // "CameraRotationXValueChanged"
QT_MOC_LITERAL(55, 965, 27), // "CameraRotationYValueChanged"
QT_MOC_LITERAL(56, 993, 27), // "CameraRotationZValueChanged"
QT_MOC_LITERAL(57, 1021, 12), // "LightToggled"
QT_MOC_LITERAL(58, 1034, 8), // "useLight"
QT_MOC_LITERAL(59, 1043, 18), // "LightTypeActivated"
QT_MOC_LITERAL(60, 1062, 21), // "ShininessValueChanged"
QT_MOC_LITERAL(61, 1084, 20), // "StrengthValueChanged"
QT_MOC_LITERAL(62, 1105, 31), // "ConstantAttenuationValueChanged"
QT_MOC_LITERAL(63, 1137, 29), // "LinearAttenuationValueChanged"
QT_MOC_LITERAL(64, 1167, 32), // "QuadraticAttenuationValueChanged"
QT_MOC_LITERAL(65, 1200, 25), // "SpotCosCutoffValueChanged"
QT_MOC_LITERAL(66, 1226, 24), // "SpotExponentValueChanged"
QT_MOC_LITERAL(67, 1251, 18), // "LightColorRChanged"
QT_MOC_LITERAL(68, 1270, 18), // "LightColorGChanged"
QT_MOC_LITERAL(69, 1289, 18), // "LightColorBChanged"
QT_MOC_LITERAL(70, 1308, 26), // "LightPositionXValueChanged"
QT_MOC_LITERAL(71, 1335, 26), // "LightPositionYValueChanged"
QT_MOC_LITERAL(72, 1362, 26), // "LightPositionZValueChanged"
QT_MOC_LITERAL(73, 1389, 27), // "LightDirectionXValueChanged"
QT_MOC_LITERAL(74, 1417, 27), // "LightDirectionYValueChanged"
QT_MOC_LITERAL(75, 1445, 27), // "LightDirectionZValueChanged"
QT_MOC_LITERAL(76, 1473, 20), // "ConeDirXValueChanged"
QT_MOC_LITERAL(77, 1494, 20), // "ConeDirYValueChanged"
QT_MOC_LITERAL(78, 1515, 20) // "ConeDirZValueChanged"

    },
    "HXInspectorWidget\0ActivityToggled\0\0"
    "activity\0StaticToggled\0bStatic\0"
    "CastShadowToggled\0castShadow\0"
    "LayerActivated\0index\0PositionXValueChanged\0"
    "value\0PositionYValueChanged\0"
    "PositionZValueChanged\0RotationXValueChanged\0"
    "RotationYValueChanged\0RotationZValueChanged\0"
    "ScaleXValueChanged\0ScaleYValueChanged\0"
    "ScaleZValueChanged\0FogToggled\0useFog\0"
    "FogTypeActivated\0FogColorRChanged\0"
    "FogColorGChanged\0FogColorBChanged\0"
    "FogStartChanged\0FogEndChanged\0"
    "FogDensityChanged\0FogGradiantChanged\0"
    "AmbientColorRChanged\0AmbientColorGChanged\0"
    "AmbientColorBChanged\0CameraToggled\0"
    "useCamera\0CameraFieldChanged\0"
    "CameraSizeChanged\0CameraNearChanged\0"
    "CameraFarChanged\0CameraViewportXChanged\0"
    "CameraViewportYChanged\0CameraViewportWChanged\0"
    "CameraViewportHChanged\0ClearFlagActivated\0"
    "BGColorRChanged\0BGColorGChanged\0"
    "BGColorBChanged\0CullingMaskActivated\0"
    "ProjectionActivated\0DepthChanged\0"
    "TransSyncOnClick\0CameraPositionXValueChanged\0"
    "CameraPositionYValueChanged\0"
    "CameraPositionZValueChanged\0"
    "CameraRotationXValueChanged\0"
    "CameraRotationYValueChanged\0"
    "CameraRotationZValueChanged\0LightToggled\0"
    "useLight\0LightTypeActivated\0"
    "ShininessValueChanged\0StrengthValueChanged\0"
    "ConstantAttenuationValueChanged\0"
    "LinearAttenuationValueChanged\0"
    "QuadraticAttenuationValueChanged\0"
    "SpotCosCutoffValueChanged\0"
    "SpotExponentValueChanged\0LightColorRChanged\0"
    "LightColorGChanged\0LightColorBChanged\0"
    "LightPositionXValueChanged\0"
    "LightPositionYValueChanged\0"
    "LightPositionZValueChanged\0"
    "LightDirectionXValueChanged\0"
    "LightDirectionYValueChanged\0"
    "LightDirectionZValueChanged\0"
    "ConeDirXValueChanged\0ConeDirYValueChanged\0"
    "ConeDirZValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HXInspectorWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      69,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  359,    2, 0x0a /* Public */,
       4,    1,  362,    2, 0x0a /* Public */,
       6,    1,  365,    2, 0x0a /* Public */,
       8,    1,  368,    2, 0x0a /* Public */,
      10,    1,  371,    2, 0x0a /* Public */,
      12,    1,  374,    2, 0x0a /* Public */,
      13,    1,  377,    2, 0x0a /* Public */,
      14,    1,  380,    2, 0x0a /* Public */,
      15,    1,  383,    2, 0x0a /* Public */,
      16,    1,  386,    2, 0x0a /* Public */,
      17,    1,  389,    2, 0x0a /* Public */,
      18,    1,  392,    2, 0x0a /* Public */,
      19,    1,  395,    2, 0x0a /* Public */,
      20,    1,  398,    2, 0x0a /* Public */,
      22,    1,  401,    2, 0x0a /* Public */,
      23,    1,  404,    2, 0x0a /* Public */,
      24,    1,  407,    2, 0x0a /* Public */,
      25,    1,  410,    2, 0x0a /* Public */,
      26,    1,  413,    2, 0x0a /* Public */,
      27,    1,  416,    2, 0x0a /* Public */,
      28,    1,  419,    2, 0x0a /* Public */,
      29,    1,  422,    2, 0x0a /* Public */,
      30,    1,  425,    2, 0x0a /* Public */,
      31,    1,  428,    2, 0x0a /* Public */,
      32,    1,  431,    2, 0x0a /* Public */,
      33,    1,  434,    2, 0x0a /* Public */,
      35,    1,  437,    2, 0x0a /* Public */,
      36,    1,  440,    2, 0x0a /* Public */,
      37,    1,  443,    2, 0x0a /* Public */,
      38,    1,  446,    2, 0x0a /* Public */,
      39,    1,  449,    2, 0x0a /* Public */,
      40,    1,  452,    2, 0x0a /* Public */,
      41,    1,  455,    2, 0x0a /* Public */,
      42,    1,  458,    2, 0x0a /* Public */,
      43,    1,  461,    2, 0x0a /* Public */,
      44,    1,  464,    2, 0x0a /* Public */,
      45,    1,  467,    2, 0x0a /* Public */,
      46,    1,  470,    2, 0x0a /* Public */,
      47,    1,  473,    2, 0x0a /* Public */,
      48,    1,  476,    2, 0x0a /* Public */,
      49,    1,  479,    2, 0x0a /* Public */,
      50,    0,  482,    2, 0x0a /* Public */,
      51,    1,  483,    2, 0x0a /* Public */,
      52,    1,  486,    2, 0x0a /* Public */,
      53,    1,  489,    2, 0x0a /* Public */,
      54,    1,  492,    2, 0x0a /* Public */,
      55,    1,  495,    2, 0x0a /* Public */,
      56,    1,  498,    2, 0x0a /* Public */,
      57,    1,  501,    2, 0x0a /* Public */,
      59,    1,  504,    2, 0x0a /* Public */,
      60,    1,  507,    2, 0x0a /* Public */,
      61,    1,  510,    2, 0x0a /* Public */,
      62,    1,  513,    2, 0x0a /* Public */,
      63,    1,  516,    2, 0x0a /* Public */,
      64,    1,  519,    2, 0x0a /* Public */,
      65,    1,  522,    2, 0x0a /* Public */,
      66,    1,  525,    2, 0x0a /* Public */,
      67,    1,  528,    2, 0x0a /* Public */,
      68,    1,  531,    2, 0x0a /* Public */,
      69,    1,  534,    2, 0x0a /* Public */,
      70,    1,  537,    2, 0x0a /* Public */,
      71,    1,  540,    2, 0x0a /* Public */,
      72,    1,  543,    2, 0x0a /* Public */,
      73,    1,  546,    2, 0x0a /* Public */,
      74,    1,  549,    2, 0x0a /* Public */,
      75,    1,  552,    2, 0x0a /* Public */,
      76,    1,  555,    2, 0x0a /* Public */,
      77,    1,  558,    2, 0x0a /* Public */,
      78,    1,  561,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Bool,   34,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Bool,   58,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Double,   11,

       0        // eod
};

void HXInspectorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HXInspectorWidget *_t = static_cast<HXInspectorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ActivityToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->StaticToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->CastShadowToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->LayerActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->PositionXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->PositionYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->PositionZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->RotationXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->RotationYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->RotationZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->ScaleXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->ScaleYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->ScaleZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->FogToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->FogTypeActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->FogColorRChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->FogColorGChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->FogColorBChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->FogStartChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->FogEndChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->FogDensityChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->FogGradiantChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 22: _t->AmbientColorRChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->AmbientColorGChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->AmbientColorBChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->CameraToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->CameraFieldChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->CameraSizeChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 28: _t->CameraNearChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->CameraFarChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->CameraViewportXChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 31: _t->CameraViewportYChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 32: _t->CameraViewportWChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 33: _t->CameraViewportHChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 34: _t->ClearFlagActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->BGColorRChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->BGColorGChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->BGColorBChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->CullingMaskActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->ProjectionActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->DepthChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->TransSyncOnClick(); break;
        case 42: _t->CameraPositionXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 43: _t->CameraPositionYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 44: _t->CameraPositionZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 45: _t->CameraRotationXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 46: _t->CameraRotationYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 47: _t->CameraRotationZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 48: _t->LightToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 49: _t->LightTypeActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->ShininessValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 51: _t->StrengthValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 52: _t->ConstantAttenuationValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 53: _t->LinearAttenuationValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 54: _t->QuadraticAttenuationValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 55: _t->SpotCosCutoffValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 56: _t->SpotExponentValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 57: _t->LightColorRChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 58: _t->LightColorGChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 59: _t->LightColorBChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 60: _t->LightPositionXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 61: _t->LightPositionYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 62: _t->LightPositionZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 63: _t->LightDirectionXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 64: _t->LightDirectionYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 65: _t->LightDirectionZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 66: _t->ConeDirXValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 67: _t->ConeDirYValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 68: _t->ConeDirZValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HXInspectorWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_HXInspectorWidget.data,
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
    return QTreeWidget::qt_metacast(_clname);
}

int HXInspectorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 69)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 69;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 69)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 69;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
