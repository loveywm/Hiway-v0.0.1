#include"uiFont.h"
#include <QStringList>

////////////////Menu Structure/////////////////////
#define uistr_MENU_MAINMENU             QObject::tr("1.MainMenu")
#define uistr_MENU_USERMANAGE		QObject::tr("2.UserManage")
#define uistr_MENU_SYSTEMSETTING	QObject::tr("3.Setting")
#define uistr_MENU_USBMANAGE		QObject::tr("4.U-DiskManage")
#define uistr_MENU_SYSINFOVIEW		QObject::tr("5.SysInfoView")
#define uistr_MENU_DATAVIEW		QObject::tr("6.DataView")
//#define uistr_MENU_ALARMREMOVE		QObject::tr("7.AlarmRemove")

//>>uistr_MENU_USERMANAGE-----------------------------------------------------<<		1
#define uistr_MENU_ENROLLNEW			QObject::tr("2.1.Enroll")
//#define uistr_MENU_ENROLLBACKUP			QObject::tr("1.2.Backup")
//#define uistr_MENU_ENROLLDELETE			QObject::tr("1.3.Delete")
#define uistr_MENU_ENROLLEDIT			QObject::tr("2.2.Edit")
#define uistr_MENU_ENROLLDEL 			QObject::tr("2.3.Del")
//#define uistr_MENU_MESSINFO			QObject::tr("MENU_MESSINFO")

//>>uistr_MENU_SYSINFOVIEW----------------------------------------------------<<		4
#define uistr_MENU_USERENROLLCOUNT		QObject::tr("5.1.EnrollCount")
#define uistr_MENU_FPENROLLCOUNT		QObject::tr("5.2.FP Count")
//#define uistr_MENU_PWDENROLLCOUNT		QObject::tr("MENU_PWDENROLLCOUNT")
//#define uistr_MENU_CARDENROLLCOUNT		QObject::tr("MENU_CARDENROLLCOUNT")
//#define uistr_MENU_GLOGCOUNT			QObject::tr("4.3.GLog Count")
//#define uistr_MENU_MLOGCOUNT			QObject::tr("4.4.MLog Count")
//#define uistr_MENU_USEDMEMORY			QObject::tr("4.5.UsedMemory")
//#define uistr_MENU_FREESPACES			QObject::tr("4.6.FreeSpaces")
#define uistr_MENU_DEVICEINFO			QObject::tr("5.7.DeviceInfo")
//#define uistr_MENU_USEDSPACES			QObject::tr("4.8.UsedSpaces")




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
    //__STRINGTABLE->append(uistr_MENU_ALARMREMOVE);

    //>>uistr_MENU_USERMANAGE-----------------------------------------------------<<		1
    __STRINGTABLE->append(uistr_MENU_ENROLLNEW);
    //__STRINGTABLE->append(uistr_MENU_ENROLLBACKUP);
    //__STRINGTABLE->append(uistr_MENU_ENROLLDELETE);
    __STRINGTABLE->append(uistr_MENU_ENROLLEDIT);
    __STRINGTABLE->append(uistr_MENU_ENROLLDEL);
    //__STRINGTABLE->append(uistr_MENU_MESSINFO);

    //>>uistr_MENU_SYSINFOVIEW----------------------------------------------------<<		4
    __STRINGTABLE->append(uistr_MENU_USERENROLLCOUNT);
    __STRINGTABLE->append(uistr_MENU_FPENROLLCOUNT);
    //__STRINGTABLE->append(uistr_MENU_PWDENROLLCOUNT);
    //__STRINGTABLE->append(uistr_MENU_CARDENROLLCOUNT);
    //__STRINGTABLE->append(uistr_MENU_GLOGCOUNT);
    //__STRINGTABLE->append(uistr_MENU_MLOGCOUNT);
    //__STRINGTABLE->append(uistr_MENU_USEDMEMORY);
    //__STRINGTABLE->append(uistr_MENU_FREESPACES);
    __STRINGTABLE->append(uistr_MENU_DEVICEINFO);
    //__STRINGTABLE->append(uistr_MENU_USEDSPACES);

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


