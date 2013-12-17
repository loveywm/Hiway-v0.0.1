#ifndef DEFINE_H
#define DEFINE_H
#include <QPainter>
#include <QtGui/QLabel>


#include "customstyle.h"
#include "uiFont.h"

//////////////////////////////////////////////////////////////////////////
typedef int                                 HFILE;
typedef char                              CHAR;
typedef short                             SHORT;
typedef int                                 INT;
typedef unsigned char               BYTE;
typedef unsigned char               BOOL;
typedef unsigned short              WORD;
typedef unsigned int                  DWORD;
typedef long                              LONG;
typedef unsigned long long		  UINT64;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#ifndef NULL
#define NULL					(0)
#endif /*NULL*/
#ifndef TRUE
#define TRUE					(1)
#endif /*TRUE*/
#ifndef FALSE
#define FALSE					(0)
#endif /*FALSE*/
//////////////////////////////////////////////////////////////////////////

#define LCD_SIZE_X	320
#define LCD_SIZE_Y	240

#define TITLECOLOR		QColor(255,0,10)
#define FOREGROUND_COLOR0       QColor(255,255,255)
#define FOREGROUND_COLOR1        QColor(0,20,0)

#define BACKGROUND_IMAGE		":/images/res/bg-main2.png" //g_bgImageFilename
//#define INPUTBOX_IMAGE			g_inputboxImageFilename
#define TITLE_IMAGE			":/images/res/title-2.png" //g_titleImageFilename

#define GUI_DLG_IMPL(_MAX_)		{if (_MAX_) setGeometry(0, 0, LCD_SIZE_X, LCD_SIZE_Y);}
#define ITEM_CNT(_x_)			(sizeof((_x_)) / sizeof((_x_)[0]))
#define GUI_DLG_SET_FORE_COLOR(_pal_, _col_) {(_pal_)->setColor(QPalette::All, QPalette::WindowText, (_col_)); \
                                                (_pal_)->setColor(QPalette::All, QPalette::Text, (_col_)); \
                                            }

#define GUI_DLG_SET_THEME()		\
{ \
    ui->lblBackground->setPixmap(QPixmap(BACKGROUND_IMAGE)); \
    ui->lblTitleBackground->setPixmap(QPixmap(TITLE_IMAGE)); \
    SET_DLG_ITEM_COLOR(this,1); \
}
////////////////////////////
#define DIALOGBOX(_class_)({_class_ *__OBJ = new _class_; if (__OBJ) { __OBJ->show(); __OBJ->DoProcess(); delete __OBJ;}})
#define POST_EVENTS()			{QApplication::processEvents();}

////////////////////////////
//ziti
#define SB_FONT(_name_, _size_)	(QFont((_name_), (_size_)))
//#define SB_FONT_0()				(SB_FONT("wenquanyi", 50))
#define SB_FONT_16()				(SB_FONT("wenquanyi", 160))
#define SB_FONT_15()				(SB_FONT("wenquanyi", 150))
#define SB_FONT_13()				(SB_FONT("wenquanyi", 130))
#define SB_FONT_12()				(SB_FONT("wenquanyi", 120))
//#define TiltleFont				SB_FONT_2()

///////////////////////////////

void uiLcdSetLabelText(QLabel *pLabel, QString str, QColor color,QColor edge_color = QColor(),QString strName = QString(""));
void uiLcdDrawText(QPainter *painter, int x, int y, int w, int h, int align, QString str, QColor color, QColor edge_color = QColor());


int GetMainTickCount(void);
void uiTimeSetLastActionTime(void);
BOOL uiTimeIsTimeout(DWORD dwTimeout);

void SET_DLG_ITEM_COLOR(QWidget *w,int colorFlag = 0);



////////////////////////

#endif // DEFINE_H
