/****************************************************************************
** Meta object code from reading C++ file 'output.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widget/output.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'output.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Output[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x0a,
      37,    8,    7,    7, 0x0a,
      67,    8,    7,    7, 0x0a,
      95,    8,    7,    7, 0x0a,
     122,    8,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Output[] = {
    "Output\0\0pText\0appendMessage(QString)\0"
    "appendWarningMessage(QString)\0"
    "appendErrorMessage(QString)\0"
    "appendUserMessage(QString)\0"
    "appendUserErrorMessage(QString)\0"
};

void Output::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Output *_t = static_cast<Output *>(_o);
        switch (_id) {
        case 0: _t->appendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->appendWarningMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->appendErrorMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->appendUserMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->appendUserErrorMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Output::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Output::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_Output,
      qt_meta_data_Output, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Output::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Output::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Output::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Output))
        return static_cast<void*>(const_cast< Output*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int Output::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
