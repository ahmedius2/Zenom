/****************************************************************************
** Meta object code from reading C++ file 'checkedheader.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../zenom/zenom/widget/checkedheader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'checkedheader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckedHeader[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   47,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CheckedHeader[] = {
    "CheckedHeader\0\0index,checked\0"
    "toggled(int,bool)\0,newCount\0"
    "sectionCountChanged(int,int)\0"
};

void CheckedHeader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckedHeader *_t = static_cast<CheckedHeader *>(_o);
        switch (_id) {
        case 0: _t->toggled((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->sectionCountChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CheckedHeader::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckedHeader::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_CheckedHeader,
      qt_meta_data_CheckedHeader, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckedHeader::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckedHeader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckedHeader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckedHeader))
        return static_cast<void*>(const_cast< CheckedHeader*>(this));
    return QHeaderView::qt_metacast(_clname);
}

int CheckedHeader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CheckedHeader::toggled(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
