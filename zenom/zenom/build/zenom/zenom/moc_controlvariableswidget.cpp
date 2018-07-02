/****************************************************************************
** Meta object code from reading C++ file 'controlvariableswidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../zenom/controlvariableswidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlvariableswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControlVariablesWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      43,   23,   23,   23, 0x08,
      69,   63,   23,   23, 0x08,
     109,  100,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ControlVariablesWidget[] = {
    "ControlVariablesWidget\0\0on_apply_clicked()\0"
    "on_cancel_clicked()\0pItem\0"
    "itemChanged(QTableWidgetItem*)\0pChecked\0"
    "toggleView(bool)\0"
};

void ControlVariablesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ControlVariablesWidget *_t = static_cast<ControlVariablesWidget *>(_o);
        switch (_id) {
        case 0: _t->on_apply_clicked(); break;
        case 1: _t->on_cancel_clicked(); break;
        case 2: _t->itemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->toggleView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ControlVariablesWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ControlVariablesWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlVariablesWidget,
      qt_meta_data_ControlVariablesWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ControlVariablesWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ControlVariablesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ControlVariablesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlVariablesWidget))
        return static_cast<void*>(const_cast< ControlVariablesWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlVariablesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
