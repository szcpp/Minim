/****************************************************************************
** Meta object code from reading C++ file 'MetaAlgorithm.hpp'
**
** Created: Sun Jan 13 12:29:26 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inc/MetaAlgorithm.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MetaAlgorithm.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MetaAlgorithm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      27,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   14,   14,   14, 0x0a,
      52,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MetaAlgorithm[] = {
    "MetaAlgorithm\0\0replotMAG()\0replotAG()\0"
    "replotSigAG()\0StopAlgorithm()\0"
};

void MetaAlgorithm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MetaAlgorithm *_t = static_cast<MetaAlgorithm *>(_o);
        switch (_id) {
        case 0: _t->replotMAG(); break;
        case 1: _t->replotAG(); break;
        case 2: _t->replotSigAG(); break;
        case 3: _t->StopAlgorithm(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MetaAlgorithm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MetaAlgorithm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MetaAlgorithm,
      qt_meta_data_MetaAlgorithm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MetaAlgorithm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MetaAlgorithm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MetaAlgorithm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MetaAlgorithm))
        return static_cast<void*>(const_cast< MetaAlgorithm*>(this));
    return QObject::qt_metacast(_clname);
}

int MetaAlgorithm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MetaAlgorithm::replotMAG()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MetaAlgorithm::replotAG()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
