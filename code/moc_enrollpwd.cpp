/****************************************************************************
** Meta object code from reading C++ file 'enrollpwd.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/enrollpwd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'enrollpwd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EnrollPWD[] = {

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
      19,   11,   10,   10, 0x0a,
      58,   53,   10,   10, 0x0a,
      89,   78,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EnrollPWD[] = {
    "EnrollPWD\0\0from,to\0OnFocusChanged(QWidget*,QWidget*)\0"
    "szID\0OnIDChange(QString)\0szPassword\0"
    "OnPasswordChange(QString)\0"
};

void EnrollPWD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EnrollPWD *_t = static_cast<EnrollPWD *>(_o);
        switch (_id) {
        case 0: _t->OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: _t->OnIDChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->OnPasswordChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EnrollPWD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EnrollPWD::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EnrollPWD,
      qt_meta_data_EnrollPWD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EnrollPWD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EnrollPWD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EnrollPWD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EnrollPWD))
        return static_cast<void*>(const_cast< EnrollPWD*>(this));
    return QDialog::qt_metacast(_clname);
}

int EnrollPWD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
