/****************************************************************************
** Meta object code from reading C++ file 'logvariableswidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../zenom/logvariableswidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logvariableswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogVariablesWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   20,   19,   19, 0x08,
      92,   76,   19,   19, 0x08,
     133,  124,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LogVariablesWidget[] = {
    "LogVariablesWidget\0\0item\0"
    "on_logVariableTable_itemChanged(QTableWidgetItem*)\0"
    "pIndex,pChecked\0setLogVariableChecked(int,bool)\0"
    "pChecked\0toggleView(bool)\0"
};

void LogVariablesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LogVariablesWidget *_t = static_cast<LogVariablesWidget *>(_o);
        switch (_id) {
        case 0: _t->on_logVariableTable_itemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->setLogVariableChecked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->toggleView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LogVariablesWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LogVariablesWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LogVariablesWidget,
      qt_meta_data_LogVariablesWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LogVariablesWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LogVariablesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LogVariablesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogVariablesWidget))
        return static_cast<void*>(const_cast< LogVariablesWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int LogVariablesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
