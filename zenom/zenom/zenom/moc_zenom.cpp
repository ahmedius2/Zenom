/****************************************************************************
** Meta object code from reading C++ file 'zenom.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "zenom.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zenom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Zenom[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      41,    6,    6,    6, 0x08,
      75,    6,    6,    6, 0x08,
     103,    6,    6,    6, 0x08,
     120,    6,    6,    6, 0x08,
     146,    6,    6,    6, 0x08,
     173,    6,    6,    6, 0x08,
     199,    6,    6,    6, 0x08,
     226,    6,    6,    6, 0x08,
     251,    6,    6,    6, 0x08,
     275,    6,    6,    6, 0x08,
     306,    6,    6,    6, 0x08,
     336,    6,    6,    6, 0x08,
     352,  345,    6,    6, 0x08,
     400,    6,    6,    6, 0x08,
     437,    6,    6,    6, 0x08,
     473,    6,    6,    6, 0x08,
     507,    6,    6,    6, 0x08,
     545,    6,    6,    6, 0x08,
     593,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Zenom[] = {
    "Zenom\0\0on_actionOpen_Project_triggered()\0"
    "on_actionSave_Project_triggered()\0"
    "on_actionReload_triggered()\0"
    "openRecentFile()\0on_actionExit_triggered()\0"
    "on_actionWatch_triggered()\0"
    "on_actionPlot_triggered()\0"
    "on_actionScene_triggered()\0"
    "on_startButton_clicked()\0"
    "on_stopButton_clicked()\0"
    "on_frequency_editingFinished()\0"
    "on_duration_editingFinished()\0doloop()\0"
    "pError\0controlBaseProcessError(QProcess::ProcessError)\0"
    "controlBaseReadyReadStandardOutput()\0"
    "controlBaseReadyReadStandardError()\0"
    "on_action_About_zenom_triggered()\0"
    "on_actionExport_as_Matlab_triggered()\0"
    "on_actionClear_Recent_Projects_Menu_triggered()\0"
    "on_actionCamera_triggered()\0"
};

void Zenom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Zenom *_t = static_cast<Zenom *>(_o);
        switch (_id) {
        case 0: _t->on_actionOpen_Project_triggered(); break;
        case 1: _t->on_actionSave_Project_triggered(); break;
        case 2: _t->on_actionReload_triggered(); break;
        case 3: _t->openRecentFile(); break;
        case 4: _t->on_actionExit_triggered(); break;
        case 5: _t->on_actionWatch_triggered(); break;
        case 6: _t->on_actionPlot_triggered(); break;
        case 7: _t->on_actionScene_triggered(); break;
        case 8: _t->on_startButton_clicked(); break;
        case 9: _t->on_stopButton_clicked(); break;
        case 10: _t->on_frequency_editingFinished(); break;
        case 11: _t->on_duration_editingFinished(); break;
        case 12: _t->doloop(); break;
        case 13: _t->controlBaseProcessError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 14: _t->controlBaseReadyReadStandardOutput(); break;
        case 15: _t->controlBaseReadyReadStandardError(); break;
        case 16: _t->on_action_About_zenom_triggered(); break;
        case 17: _t->on_actionExport_as_Matlab_triggered(); break;
        case 18: _t->on_actionClear_Recent_Projects_Menu_triggered(); break;
        case 19: _t->on_actionCamera_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Zenom::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Zenom::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Zenom,
      qt_meta_data_Zenom, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Zenom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Zenom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Zenom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Zenom))
        return static_cast<void*>(const_cast< Zenom*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Zenom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
