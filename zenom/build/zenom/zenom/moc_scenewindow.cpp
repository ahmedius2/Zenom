/****************************************************************************
** Meta object code from reading C++ file 'scenewindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../zenom/zenom/scene/scenewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scenewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SceneWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      40,   34,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   12,   12,   12, 0x08,
      90,   12,   12,   12, 0x08,
     123,  117,   12,   12, 0x08,
     153,   12,   12,   12, 0x08,
     193,   12,   12,   12, 0x08,
     229,   12,   12,   12, 0x08,
     270,   12,   12,   12, 0x08,
     308,   12,   12,   12, 0x08,
     354,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SceneWindow[] = {
    "SceneWindow\0\0closed(SceneWindow*)\0"
    "pText\0warningMessage(QString)\0"
    "on_actionOpen_triggered()\0"
    "on_actionClose_triggered()\0pName\0"
    "viewpointChangedSlot(QString)\0"
    "on_actionPrevious_Viewpoint_triggered()\0"
    "on_actionNext_Viewpoint_triggered()\0"
    "on_actionReturn_to_Viewpoint_triggered()\0"
    "on_actionCreate_Viewpoint_triggered()\0"
    "on_actionRemove_Current_Viewpoint_triggered()\0"
    "on_actionBind_Parameters_triggered()\0"
};

void SceneWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SceneWindow *_t = static_cast<SceneWindow *>(_o);
        switch (_id) {
        case 0: _t->closed((*reinterpret_cast< SceneWindow*(*)>(_a[1]))); break;
        case 1: _t->warningMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_actionOpen_triggered(); break;
        case 3: _t->on_actionClose_triggered(); break;
        case 4: _t->viewpointChangedSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_actionPrevious_Viewpoint_triggered(); break;
        case 6: _t->on_actionNext_Viewpoint_triggered(); break;
        case 7: _t->on_actionReturn_to_Viewpoint_triggered(); break;
        case 8: _t->on_actionCreate_Viewpoint_triggered(); break;
        case 9: _t->on_actionRemove_Current_Viewpoint_triggered(); break;
        case 10: _t->on_actionBind_Parameters_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SceneWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SceneWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SceneWindow,
      qt_meta_data_SceneWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SceneWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SceneWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SceneWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneWindow))
        return static_cast<void*>(const_cast< SceneWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SceneWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SceneWindow::closed(SceneWindow * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SceneWindow::warningMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
