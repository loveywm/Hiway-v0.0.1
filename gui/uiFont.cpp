#include"uiFont.h"
#include <QStringList>

////////////////Menu Structure/////////////////////
#define uistr_MENU_MAINMENU             QObject::tr("1.MainMenu")
#define uistr_MENU_USERMANAGE		QObject::tr("2.UserManage")
#define uistr_MENU_SYSTEMSETTING	QObject::tr("3.Setting")
#define uistr_MENU_USBMANAGE		QObject::tr("4.U-DiskManage")
#define uistr_MENU_SYSINFOVIEW		QObject::tr("5.SysInfoView")
#define uistr_MENU_DATAVIEW		QObject::tr("6.DataView")
#define uistr_MENU_ALARMREMOVE		QObject::tr("7.AlarmRemove")

static QStringList *__STRINGTABLE = NULL;
void FONTDATABASE_INIT()
{
    if (!__STRINGTABLE)
        __STRINGTABLE = new QStringList;
    else
        __STRINGTABLE->clear();

    ////////////////Menu Structure//////////////////////////
    __STRINGTABLE->append(uistr_MENU_MAINMENU);
    __STRINGTABLE->append(uistr_MENU_USERMANAGE);
    __STRINGTABLE->append(uistr_MENU_SYSTEMSETTING);
    __STRINGTABLE->append(uistr_MENU_USBMANAGE);
    __STRINGTABLE->append(uistr_MENU_SYSINFOVIEW);
    __STRINGTABLE->append(uistr_MENU_DATAVIEW);
    __STRINGTABLE->append(uistr_MENU_ALARMREMOVE);

}

//////////////////////////////////////////////////////////////////////////
QString UISTR(int nIndex)
{
    if (nIndex < 0)
        return QString("");
    if (!__STRINGTABLE)
        FONTDATABASE_INIT();
    if (__STRINGTABLE->size() <= nIndex)
        return QString("No Text");
    return __STRINGTABLE->at(nIndex);
};


