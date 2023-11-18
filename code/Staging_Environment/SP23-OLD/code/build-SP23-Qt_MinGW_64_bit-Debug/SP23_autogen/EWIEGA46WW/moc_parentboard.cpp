/****************************************************************************
** Meta object code from reading C++ file 'parentboard.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SP23/parentboard.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parentboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSparentboardENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSparentboardENDCLASS = QtMocHelpers::stringData(
    "parentboard",
    "goBackToMainWindow",
    "",
    "on_taskboardButton_clicked",
    "on_backlogButton_clicked",
    "on_sprintsButton_clicked",
    "on_confluenceButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSparentboardENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[12];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[27];
    char stringdata4[25];
    char stringdata5[25];
    char stringdata6[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSparentboardENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSparentboardENDCLASS_t qt_meta_stringdata_CLASSparentboardENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "parentboard"
        QT_MOC_LITERAL(12, 18),  // "goBackToMainWindow"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 26),  // "on_taskboardButton_clicked"
        QT_MOC_LITERAL(59, 24),  // "on_backlogButton_clicked"
        QT_MOC_LITERAL(84, 24),  // "on_sprintsButton_clicked"
        QT_MOC_LITERAL(109, 27)   // "on_confluenceButton_clicked"
    },
    "parentboard",
    "goBackToMainWindow",
    "",
    "on_taskboardButton_clicked",
    "on_backlogButton_clicked",
    "on_sprintsButton_clicked",
    "on_confluenceButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSparentboardENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    0,   46,    2, 0x08,    3 /* Private */,
       5,    0,   47,    2, 0x08,    4 /* Private */,
       6,    0,   48,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject parentboard::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSparentboardENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSparentboardENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSparentboardENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<parentboard, std::true_type>,
        // method 'goBackToMainWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_taskboardButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_backlogButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sprintsButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_confluenceButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void parentboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<parentboard *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->goBackToMainWindow(); break;
        case 1: _t->on_taskboardButton_clicked(); break;
        case 2: _t->on_backlogButton_clicked(); break;
        case 3: _t->on_sprintsButton_clicked(); break;
        case 4: _t->on_confluenceButton_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *parentboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *parentboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSparentboardENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int parentboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
