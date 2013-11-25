#ifndef UIFONT_H
#define UIFONT_H

enum
{
    ////////////////Menu Structure/////////////////////
    UISTR_MENU_MAINMENU,
    UISTR_MENU_USERMANAGE,
    UISTR_MENU_SYSTEMSETTING,
    UISTR_MENU_USBMANAGE,
    UISTR_MENU_SYSINFOVIEW,
    UISTR_MENU_DATAVIEW,
    UISTR_MENU_ALARMREMOVE

};

class QString;

void FONTDATABASE_INIT();
QString UISTR(int nIndex);


#endif // UIFONT_H
