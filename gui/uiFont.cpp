#include"uiFont.h"
#include <QStringList>

////Menu Structure/////////////////////////////////////////////////////////////
#define uistr_MENU_MAINMENU         QObject::tr("1.MainMenu")
#define uistr_MENU_ENROLLNEWFP      QObject::tr("1.EnrallFP")
#define uistr_MENU_ENROLLNEWPWD      QObject::tr("1.EnrallPWD")
#define uistr_MENU_USERDATAVIEW     QObject::tr("1.UserDataView")
#define uistr_MENU_SETTIME          QObject::tr("1.SetTime")
#define uistr_MENU_USBMANAGER       QObject::tr("1.USBManager")
#define uistr_MENU_OTHERINFO        QObject::tr("1.OtherInfo")

////UISTR_MENU_USBMANAGE///////////////////////////
#define uistr_ONEGLOGLOAD           QObject::tr("2.OneGlogLoad")
#define uistr_ALLGLOGLOAD           QObject::tr("2.AllGlogLoad")
#define uistr_ALLMANAGERGLOGLODA    QObject::tr("2.AllManagerGlogLoad")
#define uistr_ONEUSERINFODOWN       QObject::tr("2.OneUserInfoDown")
#define uistr_ALLUSERINFODOWN       QObject::tr("2.AllUserInfoDown")
#define uistr_USERINFOUP            QObject::tr("2.UserInfoUp")

////UISTR_MENU_OTHERINFO////////////////////////
#define uistr_USERGLOGINFO          QObject::tr("2.UserGlogInfo")
#define uistr_DEVICEINFO            QObject::tr("2.DeviceInfo")

////UISTR_MENU_USERGLOGINFO////////////////////
#define uistr_USERENROLLCOUNT       QObject::tr("3.USERENROLLCOUNT")
#define uistr_FPENROLLCOUNT         QObject::tr("3.FPENROLLCOUNT")
#define uistr_PWDENROLLCOUNT        QObject::tr("3.PWDENROLLCOUNT")
#define uistr_GLOGCOUNT             QObject::tr("3.GLOGCOUNT")
#define uistr_MLOGCOUNT             QObject::tr("3.MLOGCOUNT")






#define uistr_MENU_USERMANAGE       QObject::tr("USERMANAGE")
#define uistr_MENU_ENROLLBACKUP     QObject::tr("ENROLLBACKUP")
#define uistr_USER_NEW              QObject::tr("USER_NEW")
#define uistr_USER_NAME             QObject::tr("USER_NAME")
#define uistr_USER_ID               QObject::tr("USER_ID")
#define uistr_USER_ENROLL_PWD       QObject::tr("ENROLL_PWD")
#define uistr_ENTER_USER_PWD       QObject::tr("ENTER_PWD")



static QStringList *__STRINGTABLE = NULL;
void FONTDATABASE_INIT()
{
    if (!__STRINGTABLE)
        __STRINGTABLE = new QStringList;
    else
        __STRINGTABLE->clear();

    ////Menu Structure//////////////////////////
    __STRINGTABLE->append(uistr_MENU_MAINMENU);
    __STRINGTABLE->append(uistr_MENU_ENROLLNEWFP);
    __STRINGTABLE->append(uistr_MENU_ENROLLNEWPWD);
    __STRINGTABLE->append(uistr_MENU_USERDATAVIEW);
    __STRINGTABLE->append(uistr_MENU_SETTIME);
    __STRINGTABLE->append(uistr_MENU_USBMANAGER);
    __STRINGTABLE->append(uistr_MENU_OTHERINFO);

    ////UISTR_MENU_USBMANAGE///////////////////////////
    __STRINGTABLE->append(uistr_ONEGLOGLOAD);
    __STRINGTABLE->append(uistr_ALLGLOGLOAD);
    __STRINGTABLE->append(uistr_ALLMANAGERGLOGLODA);
    __STRINGTABLE->append(uistr_ONEUSERINFODOWN);
    __STRINGTABLE->append(uistr_ALLUSERINFODOWN);
    __STRINGTABLE->append(uistr_USERINFOUP);

    ////UISTR_MENU_OTHERINFO////////////////////////
    __STRINGTABLE->append(uistr_USERGLOGINFO);
    __STRINGTABLE->append(uistr_DEVICEINFO);

    ////UISTR_MENU_USERGLOGINFO////////////////////
    __STRINGTABLE->append(uistr_USERENROLLCOUNT);
    __STRINGTABLE->append(uistr_FPENROLLCOUNT);
    __STRINGTABLE->append(uistr_PWDENROLLCOUNT);
    __STRINGTABLE->append(uistr_GLOGCOUNT);
    __STRINGTABLE->append(uistr_MLOGCOUNT);


    __STRINGTABLE->append(uistr_MENU_USERMANAGE);
    __STRINGTABLE->append(uistr_MENU_ENROLLBACKUP);
    __STRINGTABLE->append(uistr_USER_NEW);
    __STRINGTABLE->append(uistr_USER_NAME);
    __STRINGTABLE->append(uistr_USER_ID);
    __STRINGTABLE->append(uistr_USER_ENROLL_PWD);
    __STRINGTABLE->append(uistr_ENTER_USER_PWD);

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


