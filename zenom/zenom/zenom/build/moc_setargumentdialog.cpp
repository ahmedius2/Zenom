/****************************************************************************
** Meta object code from reading C++ file 'setargumentdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene/setargumentdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setargumentdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SetArgumentDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   19,   18,   18, 0x05,
      71,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      91,   18,   18,   18, 0x08,
     115,   18,   18,   18, 0x08,
     141,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SetArgumentDialog[] = {
    "SetArgumentDialog\0\0,pArguments\0"
    "binded(NodeData*,QVector<LogVariable*>)\0"
    "unbinded(NodeData*)\0on_bindButton_clicked()\0"
    "on_unbindButton_clicked()\0"
    "on_argumentTable_itemSelectionChanged()\0"
};

void SetArgumentDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SetArgumentDialog *_t = static_cast<SetArgumentDialog *>(_o);
        switch (_id) {
        case 0: _t->binded((*reinterpret_cast< NodeData*(*)>(_a[1])),(*reinterpret_cast< const QVector<LogVariable*>(*)>(_a[2]))); break;
        case 1: _t->unbinded((*reinterpret_cast< NodeData*(*)>(_a[1]))); break;
        case 2: _t->on_bindButton_clicked(); break;
        case 3: _t->on_unbindButton_clicked(); break;
        case 4: _t->on_argumentTable_itemSelectionChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SetArgumentDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SetArgumentDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetArgumentDialog,
      qt_meta_data_SetArgumentDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SetArgumentDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SetArgumentDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SetArgumentDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetArgumentDialog))
        return static_cast<void*>(const_cast< SetArgumentDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetArgumentDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SetArgumentDialog::binded(NodeData * _t1, const QVector<LogVariable*> _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SetArgumentDialog::unbinded(NodeData * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
