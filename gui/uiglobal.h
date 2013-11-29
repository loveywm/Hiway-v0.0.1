#ifndef XXX_H
#define XXX_H

#include <QLabel>
#include <QColor>
#include "Define.h"
typedef unsigned char               BOOL;
typedef unsigned short              WORD;
typedef unsigned int                  DWORD;


void uiLcdSetLabelText(QLabel *pLabel, QString str, QColor color,QColor edge_color = QColor(),QString strName = QString(""));
void uiLcdDrawText(QPainter *painter, int x, int y, int w, int h, int align, QString str, QColor color, QColor edge_color = QColor());


int GetMainTickCount(void);

BOOL uiTimeIsTimeout(DWORD dwTimeout);

void SET_DLG_ITEM_COLOR(QWidget *w,int colorFlag = 0);



#endif // XXX_H
