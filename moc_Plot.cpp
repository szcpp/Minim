/****************************************************************************
** Meta object code from reading C++ file 'Plot.hpp'
**
** Created: Sun Jan 13 12:33:44 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inc/Plot.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Plot.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Plot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,    5,    5,    5, 0x0a,
      31,    5,    5,    5, 0x0a,
      41,    5,    5,    5, 0x0a,
      55,    5,    5,    5, 0x0a,
      75,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Plot[] = {
    "Plot\0\0StopAlgorithm()\0Launch()\0Preview()\0"
    "ChangePlots()\0ChangePlotPreview()\0"
    "Stop()\0"
};

void Plot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Plot *_t = static_cast<Plot *>(_o);
        switch (_id) {
        case 0: _t->StopAlgorithm(); break;
        case 1: _t->Launch(); break;
        case 2: _t->Preview(); break;
        case 3: _t->ChangePlots(); break;
        case 4: _t->ChangePlotPreview(); break;
        case 5: _t->Stop(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Plot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Plot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Plot,
      qt_meta_data_Plot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Plot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Plot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Plot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Plot))
        return static_cast<void*>(const_cast< Plot*>(this));
    return QWidget::qt_metacast(_clname);
}

int Plot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Plot::StopAlgorithm()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
