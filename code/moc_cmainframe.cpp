/****************************************************************************
** Meta object code from reading C++ file 'cmainframe.h'
**
** Created: Fri Nov 29 10:35:55 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui/cmainframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmainframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CMainFrame[] = {

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

static const char qt_meta_stringdata_CMainFrame[] = {
    "CMainFrame\0"
};

const QMetaObject CMainFrame::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CMainFrame,
      qt_meta_data_CMainFrame, 0 }
};

const QMetaObject *CMainFrame::metaObject() const
{
    return &staticMetaObject;
}

void *CMainFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMainFrame))
        return static_cast<void*>(const_cast< CMainFrame*>(this));
    return QDialog::qt_metacast(_clname);
}

int CMainFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
