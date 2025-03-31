/****************************************************************************
** Meta object code from reading C++ file 'ToolbarWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/view/ToolbarWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToolbarWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
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
struct qt_meta_tag_ZN4view13ToolbarWidgetE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN4view13ToolbarWidgetE = QtMocHelpers::stringData(
    "view::ToolbarWidget",
    "addAndGate",
    "",
    "addOrGate",
    "addNotGate",
    "addSourceNode",
    "model::LogicState",
    "state",
    "addSinkNode",
    "simulate",
    "clearCircuit",
    "addXorGate",
    "addNandGate",
    "addNorGate",
    "handleButtonClick"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN4view13ToolbarWidgetE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,
       3,    0,   81,    2, 0x06,    2 /* Public */,
       4,    0,   82,    2, 0x06,    3 /* Public */,
       5,    1,   83,    2, 0x06,    4 /* Public */,
       8,    0,   86,    2, 0x06,    6 /* Public */,
       9,    0,   87,    2, 0x06,    7 /* Public */,
      10,    0,   88,    2, 0x06,    8 /* Public */,
      11,    0,   89,    2, 0x06,    9 /* Public */,
      12,    0,   90,    2, 0x06,   10 /* Public */,
      13,    0,   91,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    0,   92,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject view::ToolbarWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN4view13ToolbarWidgetE.offsetsAndSizes,
    qt_meta_data_ZN4view13ToolbarWidgetE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN4view13ToolbarWidgetE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ToolbarWidget, std::true_type>,
        // method 'addAndGate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addOrGate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNotGate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addSourceNode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<model::LogicState, std::false_type>,
        // method 'addSinkNode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'simulate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearCircuit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addXorGate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNandGate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNorGate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleButtonClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void view::ToolbarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ToolbarWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addAndGate(); break;
        case 1: _t->addOrGate(); break;
        case 2: _t->addNotGate(); break;
        case 3: _t->addSourceNode((*reinterpret_cast< std::add_pointer_t<model::LogicState>>(_a[1]))); break;
        case 4: _t->addSinkNode(); break;
        case 5: _t->simulate(); break;
        case 6: _t->clearCircuit(); break;
        case 7: _t->addXorGate(); break;
        case 8: _t->addNandGate(); break;
        case 9: _t->addNorGate(); break;
        case 10: _t->handleButtonClick(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::addAndGate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::addOrGate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::addNotGate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)(model::LogicState );
            if (_q_method_type _q_method = &ToolbarWidget::addSourceNode; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::addSinkNode; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::simulate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::clearCircuit; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::addXorGate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::addNandGate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _q_method_type = void (ToolbarWidget::*)();
            if (_q_method_type _q_method = &ToolbarWidget::addNorGate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *view::ToolbarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *view::ToolbarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN4view13ToolbarWidgetE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int view::ToolbarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void view::ToolbarWidget::addAndGate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void view::ToolbarWidget::addOrGate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void view::ToolbarWidget::addNotGate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void view::ToolbarWidget::addSourceNode(model::LogicState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void view::ToolbarWidget::addSinkNode()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void view::ToolbarWidget::simulate()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void view::ToolbarWidget::clearCircuit()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void view::ToolbarWidget::addXorGate()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void view::ToolbarWidget::addNandGate()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void view::ToolbarWidget::addNorGate()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
