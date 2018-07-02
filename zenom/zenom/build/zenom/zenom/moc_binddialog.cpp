/****************************************************************************
** Meta object code from reading C++ file 'binddialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../zenom/scene/binddialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'binddialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BindDialog[] = {

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
      12,   11,   11,   11, 0x08,
      48,   37,   11,   11, 0x08,
     121,  100,   11,   11, 0x08,
     175,  165,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BindDialog[] = {
    "BindDialog\0\0on_closeButton_clicked()\0"
    "pNodeItem,\0"
    "on_nodeTree_itemDoubleClicked(QTreeWidgetItem*,int)\0"
    "pNodeData,pArguments\0"
    "bindedSlot(NodeData*,QVector<LogVariable*>)\0"
    "pNodeData\0unbindedSlot(NodeData*)\0"
};

void BindDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BindDialog *_t = static_cast<BindDialog *>(_o);
        switch (_id) {
        case 0: _t->on_closeButton_clicked(); break;
        case 1: _t->on_nodeTree_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->bindedSlot((*reinterpret_cast< NodeData*(*)>(_a[1])),(*reinterpret_cast< const QVector<LogVariable*>(*)>(_a[2]))); break;
        case 3: _t->unbindedSlot((*reinterpret_cast< NodeData*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BindDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BindDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BindDialog,
      qt_meta_data_BindDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BindDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BindDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BindDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BindDialog))
        return static_cast<void*>(const_cast< BindDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BindDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
