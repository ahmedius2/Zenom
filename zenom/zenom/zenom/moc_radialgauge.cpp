/****************************************************************************
** Meta object code from reading C++ file 'radialgauge.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gauge/radialgauge.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'radialgauge.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RadialGauge[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_RadialGauge[] = {
    "RadialGauge\0"
};

void RadialGauge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData RadialGauge::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RadialGauge::staticMetaObject = {
    { &QwtDial::staticMetaObject, qt_meta_stringdata_RadialGauge,
      qt_meta_data_RadialGauge, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RadialGauge::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RadialGauge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RadialGauge::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RadialGauge))
        return static_cast<void*>(const_cast< RadialGauge*>(this));
    if (!strcmp(_clname, "AbstractGauge"))
        return static_cast< AbstractGauge*>(const_cast< RadialGauge*>(this));
    return QwtDial::qt_metacast(_clname);
}

int RadialGauge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtDial::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
