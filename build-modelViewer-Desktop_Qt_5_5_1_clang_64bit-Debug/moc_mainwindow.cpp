/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../modelViewer/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "do_open"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "do_quit"
QT_MOC_LITERAL(4, 28, 7), // "do_save"
QT_MOC_LITERAL(5, 36, 8), // "do_trace"
QT_MOC_LITERAL(6, 45, 11), // "update_mesh"
QT_MOC_LITERAL(7, 57, 11), // "do_shift_up"
QT_MOC_LITERAL(8, 69, 13), // "do_shift_down"
QT_MOC_LITERAL(9, 83, 13), // "do_shift_left"
QT_MOC_LITERAL(10, 97, 14), // "do_shift_right"
QT_MOC_LITERAL(11, 112, 13), // "do_orbit_left"
QT_MOC_LITERAL(12, 126, 14), // "do_orbit_right"
QT_MOC_LITERAL(13, 141, 13), // "do_twist_left"
QT_MOC_LITERAL(14, 155, 14), // "do_twist_right"
QT_MOC_LITERAL(15, 170, 14), // "do_rotate_left"
QT_MOC_LITERAL(16, 185, 15), // "do_rotate_right"
QT_MOC_LITERAL(17, 201, 10), // "do_zoom_in"
QT_MOC_LITERAL(18, 212, 11), // "do_zoom_out"
QT_MOC_LITERAL(19, 224, 12) // "update_scene"

    },
    "MainWindow\0do_open\0\0do_quit\0do_save\0"
    "do_trace\0update_mesh\0do_shift_up\0"
    "do_shift_down\0do_shift_left\0do_shift_right\0"
    "do_orbit_left\0do_orbit_right\0do_twist_left\0"
    "do_twist_right\0do_rotate_left\0"
    "do_rotate_right\0do_zoom_in\0do_zoom_out\0"
    "update_scene"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a /* Public */,
       3,    0,  105,    2, 0x0a /* Public */,
       4,    0,  106,    2, 0x0a /* Public */,
       5,    0,  107,    2, 0x0a /* Public */,
       6,    0,  108,    2, 0x0a /* Public */,
       7,    0,  109,    2, 0x0a /* Public */,
       8,    0,  110,    2, 0x0a /* Public */,
       9,    0,  111,    2, 0x0a /* Public */,
      10,    0,  112,    2, 0x0a /* Public */,
      11,    0,  113,    2, 0x0a /* Public */,
      12,    0,  114,    2, 0x0a /* Public */,
      13,    0,  115,    2, 0x0a /* Public */,
      14,    0,  116,    2, 0x0a /* Public */,
      15,    0,  117,    2, 0x0a /* Public */,
      16,    0,  118,    2, 0x0a /* Public */,
      17,    0,  119,    2, 0x0a /* Public */,
      18,    0,  120,    2, 0x0a /* Public */,
      19,    0,  121,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->do_open(); break;
        case 1: _t->do_quit(); break;
        case 2: _t->do_save(); break;
        case 3: _t->do_trace(); break;
        case 4: _t->update_mesh(); break;
        case 5: _t->do_shift_up(); break;
        case 6: _t->do_shift_down(); break;
        case 7: _t->do_shift_left(); break;
        case 8: _t->do_shift_right(); break;
        case 9: _t->do_orbit_left(); break;
        case 10: _t->do_orbit_right(); break;
        case 11: _t->do_twist_left(); break;
        case 12: _t->do_twist_right(); break;
        case 13: _t->do_rotate_left(); break;
        case 14: _t->do_rotate_right(); break;
        case 15: _t->do_zoom_in(); break;
        case 16: _t->do_zoom_out(); break;
        case 17: _t->update_scene(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
