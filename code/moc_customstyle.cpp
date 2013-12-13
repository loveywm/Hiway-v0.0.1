/****************************************************************************
** Meta object code from reading C++ file 'customstyle.h'
**
** Created: Mon Dec 2 17:00:24 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/customstyle.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customstyle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomStyle[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CustomStyle[] = {
    "CustomStyle\0"
};

const QMetaObject CustomStyle::staticMetaObject = {
    { &QWindowsStyle::staticMetaObject, qt_meta_stringdata_CustomStyle,
      qt_meta_data_CustomStyle, 0 }
};

const QMetaObject *CustomStyle::metaObject() const
{
    return &staticMetaObject;
}

void *CustomStyle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomStyle))
        return static_cast<void*>(const_cast< CustomStyle*>(this));
    return QWindowsStyle::qt_metacast(_clname);
}

int CustomStyle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWindowsStyle::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
