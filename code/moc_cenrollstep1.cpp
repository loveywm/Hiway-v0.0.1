/****************************************************************************
** Meta object code from reading C++ file 'cenrollstep1.h'
**
** Created: Mon Dec 2 16:50:02 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/cenrollstep1.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cenrollstep1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CEnrollStep1[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      22,   14,   13,   13, 0x0a,
      61,   13,   56,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnrollStep1[] = {
    "CEnrollStep1\0\0from,to\0"
    "OnFocusChanged(QWidget*,QWidget*)\0"
    "BOOL\0OnBtnESC()\0"
};

const QMetaObject CEnrollStep1::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEnrollStep1,
      qt_meta_data_CEnrollStep1, 0 }
};

const QMetaObject *CEnrollStep1::metaObject() const
{
    return &staticMetaObject;
}

void *CEnrollStep1::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnrollStep1))
        return static_cast<void*>(const_cast< CEnrollStep1*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEnrollStep1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: { BOOL _r = OnBtnESC();
            if (_a[0]) *reinterpret_cast< BOOL*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
