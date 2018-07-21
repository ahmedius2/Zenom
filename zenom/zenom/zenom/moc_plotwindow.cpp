/****************************************************************************
** Meta object code from reading C++ file 'plotwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "plot/plotwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlotWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   11,   11,   11, 0x08,
      59,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
     115,   11,   11,   11, 0x08,
     143,   11,   11,   11, 0x08,
     184,   11,   11,   11, 0x08,
     232,  223,   11,   11, 0x08,
     267,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlotWindow[] = {
    "PlotWindow\0\0closed(PlotWindow*)\0"
    "on_action_Open_triggered()\0"
    "on_action_Save_triggered()\0"
    "on_action_Export_triggered()\0"
    "on_action_Close_triggered()\0"
    "on_actionAttach_Log_Variable_triggered()\0"
    "on_actionSet_Time_Interval_triggered()\0"
    "pChecked\0on_actionAutoscale_triggered(bool)\0"
    "autoscaleOffSlot()\0"
};

void PlotWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlotWindow *_t = static_cast<PlotWindow *>(_o);
        switch (_id) {
        case 0: _t->closed((*reinterpret_cast< PlotWindow*(*)>(_a[1]))); break;
        case 1: _t->on_action_Open_triggered(); break;
        case 2: _t->on_action_Save_triggered(); break;
        case 3: _t->on_action_Export_triggered(); break;
        case 4: _t->on_action_Close_triggered(); break;
        case 5: _t->on_actionAttach_Log_Variable_triggered(); break;
        case 6: _t->on_actionSet_Time_Interval_triggered(); break;
        case 7: _t->on_actionAutoscale_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->autoscaleOffSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlotWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlotWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PlotWindow,
      qt_meta_data_PlotWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlotWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlotWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlotWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlotWindow))
        return static_cast<void*>(const_cast< PlotWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PlotWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PlotWindow::closed(PlotWindow * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
