#include <QtGui>
#include "customstyle.h"

static const char * const qt_scrollbar_button_arrow_left[] = {
   "4 7 2 1",
       "   c None",
       "*  c #064CA4",
       "   *",
       "  **",
       " ***",
       "****",
       " ***",
       "  **",
       "   *"};

static const char * const qt_scrollbar_button_arrow_right[] = {
   "4 7 2 1",
       "   c None",
       "*  c #064CA4",
       "*   ",
       "**  ",
       "*** ",
       "****",
       "*** ",
       "**  ",
       "*   "};



static QColor mergedColors(const QColor &colorA, const QColor &colorB, int factor = 50)
{
   const int maxFactor = 100;
   QColor tmp = colorA;
   tmp.setRed((tmp.red() * factor) / maxFactor + (colorB.red() * (maxFactor - factor)) / maxFactor);
   tmp.setGreen((tmp.green() * factor) / maxFactor + (colorB.green() * (maxFactor - factor)) / maxFactor);
   tmp.setBlue((tmp.blue() * factor) / maxFactor + (colorB.blue() * (maxFactor - factor)) / maxFactor);
   return tmp;
}

void CustomStyle::polish(QPalette &palette)
{
    QColor brown(Qt::white);
    QColor beige(Qt::transparent);
    QColor slightlyOpaqueBlack(0, 0, 0, 63);

//      QPainter painter;
//      painter.begin(&midImage);
//      painter.setPen(Qt::NoPen);
//      painter.fillRect(midImage.rect(), slightlyOpaqueBlack);
//      painter.end();

    palette = QPalette(brown);

    palette.setBrush(QPalette::BrightText, Qt::white);
    palette.setBrush(QPalette::Base, beige);
    palette.setBrush(QPalette::Highlight, Qt::darkGreen);
    palette.setBrush(QPalette::Button, beige);
    palette.setBrush(QPalette::ButtonText, Qt::white);
    palette.setBrush(QPalette::Mid, beige);
//	 palette.setBrush(QPalette::Window, QColor(158, 202, 243));
    palette.setBrush(QPalette::Window, beige);

    QBrush brush = palette.background();
    brush.setColor(brush.color().dark());

    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, Qt::gray);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);
}

void CustomStyle::polish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}

void CustomStyle::unpolish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}

int CustomStyle::pixelMetric(PixelMetric metric,
                                    const QStyleOption *option,
                                    const QWidget *widget) const
{
    switch (metric) {
    case PM_ScrollBarExtent:
        return QWindowsStyle::pixelMetric(metric, option, widget) + 4;
    default:
        return QWindowsStyle::pixelMetric(metric, option, widget);
    }
}

int CustomStyle::styleHint(StyleHint hint, const QStyleOption *option,
                                  const QWidget *widget,
                                  QStyleHintReturn *returnData) const
{
   int ret = 0;
    switch (hint) {
   case SH_FocusFrame_Mask:
       ret = 1;
       if (widget) {
           if(QStyleHintReturnMask *mask = qstyleoption_cast<QStyleHintReturnMask*>(returnData)) {
               mask->region = widget->rect();
               int vmargin = QCommonStyle::pixelMetric(QStyle::PM_FocusFrameVMargin),
                   hmargin = QCommonStyle::pixelMetric(QStyle::PM_FocusFrameHMargin);
               mask->region -= QRect(widget->rect().adjusted(hmargin, vmargin, -hmargin, -vmargin));
           }
       }
       return ret;
    case SH_DitherDisabledText:
        return int(false);
    case SH_EtchDisabledText:
        return int(true);
    default:
        return QWindowsStyle::styleHint(hint, option, widget, returnData);
    }
}

void CustomStyle::drawPrimitive(PrimitiveElement element,
                                       const QStyleOption *option,
                                       QPainter *painter,
                                       const QWidget *widget) const
{
//	QColor borderColor = option->palette.background().color().dark(178);
//        QColor alphaCornerColor;
       QColor backgroundColor;
       QPen oldPen(2);
       QPainterPath path;

       int x1, x2, y1, y2;

    switch (element) {
   case PE_Frame:
       if (widget && widget->parent()) {
           painter->save();
           backgroundColor = option->palette.color(widget->parentWidget()->backgroundRole());
           oldPen = painter->pen();
           painter->setPen(Qt::black);
           backgroundColor = mergedColors(QColor(0x06, 0x4C, 0xA4), QColor(0xd6, 0xd6, 0xd6));
           oldPen.setColor(backgroundColor);
           painter->setPen(oldPen);

           option->rect.getCoords(&x1, &y1, &x2, &y2);
/*            painter->drawPoint(option->rect.topLeft());
           painter->drawPoint(option->rect.topRight());
           painter->drawPoint(option->rect.bottomLeft());
           painter->drawPoint(option->rect.bottomRight());*/
           path.moveTo(x1, y1);
           path.lineTo(x2, y1);
           path.lineTo(x2, y2);
           path.lineTo(x1, y2);
           path.lineTo(x1, y1);
           painter->drawPath(path);
           painter->restore();
//            painter->setPen(oldPen);
//            alphaCornerColor = mergedColors(backgroundColor, borderColor);
       }

       break;

#ifndef QT_NO_LINEEDIT
//    case PE_FrameLineEdit:
//	if (widget) {
//    	    alphaCornerColor = mergedColors(option->palette.color(widget->backgroundRole()), borderColor);
//	} else {
//    	    alphaCornerColor = mergedColors(option->palette.background().color(), borderColor);
//	}
/*        if (widget && widget->parent()) {
           painter->save();
           backgroundColor = option->palette.color(widget->parentWidget()->backgroundRole());
           oldPen = painter->pen();
           painter->setPen(Qt::black);
           backgroundColor = mergedColors(QColor(0x06, 0x4C, 0xA4), QColor(0xd6, 0xd6, 0xd6));
           oldPen.setColor(backgroundColor);
           painter->setPen(oldPen);

           option->rect.getCoords(&x1, &y1, &x2, &y2);*/
/*            painter->drawPoint(option->rect.topLeft());
           painter->drawPoint(option->rect.topRight());
           painter->drawPoint(option->rect.bottomLeft());
           painter->drawPoint(option->rect.bottomRight());*/
/*			path.moveTo(x1, y1);
           path.lineTo(x2, y1);
           path.lineTo(x2, y2);
           path.lineTo(x1, y2);
           path.lineTo(x1, y1);
           painter->drawPath(path);
           painter->restore();
//            painter->setPen(oldPen);
//            alphaCornerColor = mergedColors(backgroundColor, borderColor);
       }
   break;*/
       // fall through
#endif // QT_NO_LINEEDIT

    case PE_FrameFocusRect:
/*        if (const QStyleOptionButton *button = qstyleoption_cast<const QStyleOptionButton *>(option)) {
           bool hover = (button->state & State_Enabled);
           painter->save();
           if (hover)
           drawHoverRect(painter, widget->rect());
           painter->restore();
   }*/
/*        if (const QStyleOptionFocusRect *fropt = qstyleoption_cast<const QStyleOptionFocusRect *>(option)) {
           QColor bg = fropt->backgroundColor;
           QPen oldPen = painter->pen();
           if (bg.isValid()) {
               int h, s, v;
               bg.getHsv(&h, &s, &v);
               if (v >= 128)
                   painter->setPen(Qt::white);
               else
                   painter->setPen(Qt::white);
           } else {
               painter->setPen(option->palette.foreground().color());
           }
           QRect focusRect = option->rect.adjusted(1, 1, -1, -1);
           painter->drawRect(focusRect.adjusted(0, 0, -1, -1)); //draw pen inclusive
           painter->setPen(oldPen);
       }
*/       break;
/*     case PE_PanelButtonCommand:
        {
            int delta = (option->state & State_MouseOver) ? 64 : 0;
            QColor slightlyOpaqueBlack(0, 0, 0, 63);
            QColor semiTransparentWhite(255, 255, 255, 127 + delta);
            QColor semiTransparentBlack(0, 0, 0, 127 - delta);

            int x, y, width, height;
            option->rect.getRect(&x, &y, &width, &height);

            QPainterPath roundRect = roundRectPath(option->rect);
            int radius = qMin(width, height) / 2;

            QBrush brush;
            bool darker;

            const QStyleOptionButton *buttonOption =
                    qstyleoption_cast<const QStyleOptionButton *>(option);
            if (buttonOption
                    && (buttonOption->features & QStyleOptionButton::Flat)) {
                brush = option->palette.background();
                darker = (option->state & (State_Sunken | State_On));
            } else {
                if (option->state & (State_Sunken | State_On)) {
                    brush = option->palette.mid();
                    darker = !(option->state & State_Sunken);
                } else {
                    brush = option->palette.button();
                    darker = false;
                }
            }

            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->fillPath(roundRect, brush); // Draw Image ...
            if (darker)
                painter->fillPath(roundRect, slightlyOpaqueBlack);

            int penWidth;
            if (radius < 10)
                penWidth = 3;
            else if (radius < 20)
                penWidth = 5;
            else
                penWidth = 7;

            QPen topPen(semiTransparentWhite, penWidth);
            QPen bottomPen(semiTransparentBlack, penWidth);

            if (option->state & (State_Sunken | State_On))
                qSwap(topPen, bottomPen);
            int x1 = x;
            int x2 = x + radius;
            int x3 = x + width - radius;
            int x4 = x + width;

            if (option->direction == Qt::RightToLeft) {
                qSwap(x1, x4);
                qSwap(x2, x3);
            }

            QPolygon topHalf;
            topHalf << QPoint(x1, y)
                    << QPoint(x4, y)
                    << QPoint(x3, y + radius)
                    << QPoint(x2, y + height - radius)
                    << QPoint(x1, y + height);

            painter->setClipPath(roundRect);
            painter->setClipRegion(topHalf, Qt::IntersectClip);
            painter->setPen(topPen);
            painter->drawPath(roundRect); // Boader draw ...

            QPolygon bottomHalf = topHalf;
            bottomHalf[0] = QPoint(x4, y + height);

            painter->setClipPath(roundRect);
            painter->setClipRegion(bottomHalf, Qt::IntersectClip);
            painter->setPen(bottomPen);
            painter->drawPath(roundRect);

            painter->setPen(option->palette.foreground().color());
            painter->setClipping(false);
            painter->drawPath(roundRect);

            painter->restore();
        }
        break;
*/
    default:
        QWindowsStyle::drawPrimitive(element, option, painter, widget);
    }
}

void CustomStyle::drawControl(ControlElement element,
                             const QStyleOption *option,
                             QPainter *painter,
                             const QWidget *widget) const
{
   QColor backgroundColor;
   QPen oldPen(2);
   QPainterPath path;
   int x1, x2, y1, y2;

   switch (element)
   {
   case CE_PushButtonBevel:

       if (const QStyleOptionButton *button = qstyleoption_cast<const QStyleOptionButton *>(option))
       {
           bool hover = (button->state & State_HasFocus);
// 			if (hover)
// 				drawHoverRect(painter, widget->rect());

           QColor slightlyOpaqueBlack(0, 0, 0, 63);
           int x, y, width, height;

           option->rect.getRect(&x, &y, &width, &height);

           QPainterPath roundRect = roundRectPath(option->rect);
//			int radius = qMin(width, height) / 2;

           QBrush brush;
           bool darker;

           const QStyleOptionButton *buttonOption = qstyleoption_cast<const QStyleOptionButton *>(option);
           if (buttonOption && (buttonOption->features & QStyleOptionButton::Flat))
           {
               brush = option->palette.mid();
               darker = (option->state & (State_Sunken | State_On));
           }
           else
           {
               if (option->state & (State_Sunken | State_On))
               {
                   brush = option->palette.mid();
                   darker = !(option->state & State_Sunken);
               }
               else
               {
                   brush = option->palette.button();
                   darker = false;
               }
           }

           painter->save();
           painter->setRenderHint(QPainter::Antialiasing, true);
           painter->fillPath(roundRect, brush); // Draw Image ...
           if (darker)
               painter->fillPath(roundRect, slightlyOpaqueBlack);

           QBrush normalBrush(QBrush(QColor(145, 116, 255)));
           painter->fillPath(roundRect, normalBrush);



           if (!hover)
           {
               QBrush highlightBrush(QBrush(QColor(142, 163, 133)));
               painter->fillPath(roundRect, highlightBrush);
           /*	x1 =x;x2 =x+width;y1=y;y2=y+height;
               QLineF line1(x1+2, y1, x2-2, y1);
               QLineF line2(x2-2,y1,x2,y2+2);
               QLineF line3(x2,y2+2,x2,y2-2);
               QLineF line4(x2,y2-2,x2-2,y2);
               QLineF line5(x2-2,y2,x1,y2-2);
               QLineF line6(x1,y2-2,x1,y2-2);
               QLineF line7(x1,y2-2,x1,y1+2);
               QLineF line8(x1,y1+2,x1+2,y1);
               QPen linePen(QPen(QColor(92,135,75)));
               painter->drawLine(line1);
               painter->drawLine(line8);
               painter->drawLine(line7);

               linePen.setColor(QColor(34,63,22));
               painter->drawLine(line8);
               painter->drawLine(line8);
               painter->drawLine(line8);
               painter->drawLine(line8);
               painter->drawLine(line8);*/

           }
       /*	else
           {
               QPen myPen(QPen(QColor(145, 116, 255)));
               painter->setPen(myPen);
               painter->drawRect(option->rect);
               QBrush normalBrush1(QBrush(QColor(145, 116, 255)));
               painter->fillRect(option->rect, normalBrush1);
           }*/
           /*
           int penWidth;
           if (radius < 10)
           penWidth = 1;
           else if (radius < 20)
           penWidth = 1;
           else
           penWidth = 1;

           int delta = (option->state & State_MouseOver) ? 64 : 0;
           QColor semiTransparentWhite(255, 255, 255, 127 + delta);
           QColor semiTransparentBlack(0, 0, 0, 127 - delta);
           QColor semiFocusTop(255, 0, 0, 127 + delta);
           QColor semiFocusDown(200, 0, 100, 127 - delta);
           QPen topPen((hover ? semiFocusTop:semiTransparentWhite), penWidth);
           QPen bottomPen((hover ? semiFocusDown:semiTransparentBlack), penWidth);

           if (option->state & (State_Sunken | State_On))
           qSwap(topPen, bottomPen);
           int x1 = x;
           int x2 = x + radius;
           int x3 = x + width - radius;
           int x4 = x + width;

           if (option->direction == Qt::RightToLeft) {
           qSwap(x1, x4);
           qSwap(x2, x3);
           }

           QPolygon topHalf;
           topHalf << QPoint(x1, y)
           << QPoint(x4, y)
           << QPoint(x3, y + radius)
           << QPoint(x2, y + height - radius)
           << QPoint(x1, y + height);

           painter->setClipPath(roundRect);
           painter->setClipRegion(topHalf, Qt::IntersectClip);
           painter->setPen(topPen);
           painter->drawPath(roundRect); // Border draw ...

           QPolygon bottomHalf = topHalf;
           bottomHalf[0] = QPoint(x4, y + height);

           painter->setClipPath(roundRect);
           painter->setClipRegion(bottomHalf, Qt::IntersectClip);
           painter->setPen(bottomPen);
           painter->drawPath(roundRect);

           painter->setPen(option->palette.foreground().color());
           painter->setClipping(false);
           painter->drawPath(roundRect);
           */
           painter->restore();
       }

       break;
   case CE_PushButtonLabel:
       {
           QStyleOptionButton myButtonOption;
           const QStyleOptionButton *buttonOption =
               qstyleoption_cast<const QStyleOptionButton *>(option);
           if (buttonOption) {
               myButtonOption = *buttonOption;
               if (myButtonOption.palette.currentColorGroup()
                   != QPalette::Disabled) {
                       if (myButtonOption.state & (State_Sunken | State_On)) {
                           myButtonOption.palette.setBrush(QPalette::ButtonText,
                               myButtonOption.palette.brightText());
                       }
               }
           }
           QWindowsStyle::drawControl(element, &myButtonOption, painter, widget);
       }
       break;
#ifndef QT_NO_PROGRESSBAR
   case CE_ProgressBarGroove:
       if (/*const QStyleOptionProgressBar *bar = */qstyleoption_cast<const QStyleOptionProgressBar *>(option)) {
           painter->save();
//          backgroundColor = option->palette.color(widget->parentWidget()->backgroundRole());
           oldPen = painter->pen();
           painter->setPen(Qt::black);
           backgroundColor = mergedColors(QColor(0x06, 0x4C, 0xA4), QColor(0xd6, 0xd6, 0xd6));
           oldPen.setColor(backgroundColor);
           painter->setPen(oldPen);

           option->rect.getCoords(&x1, &y1, &x2, &y2);
           path.moveTo(x1, y1);
           path.lineTo(x2, y1);
           path.lineTo(x2, y2);
           path.lineTo(x1, y2);
           path.lineTo(x1, y1);
           painter->drawPath(path);
           painter->restore();

       }
       break;
#endif
   default:
       QWindowsStyle::drawControl(element, option, painter, widget);
   }
}

void CustomStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex *option,
                                    QPainter *painter, const QWidget *widget) const
{
   QColor borderColor;
   QPen oldPen(2);
   QPainterPath path;
   int x1, x2, y1, y2;

   switch (control) {

#ifndef QT_NO_COMBOBOX
   case CC_ComboBox:
       if (const QStyleOptionComboBox *comboBox = qstyleoption_cast<const QStyleOptionComboBox *>(option)) {

           painter->save();
//            backgroundColor = option->palette.color(widget->parentWidget()->backgroundRole());
           bool isEnabled = (comboBox->state & State_Enabled);
           bool focus = isEnabled && (comboBox->state & State_HasFocus);

           oldPen = painter->pen();
           painter->setPen(Qt::black);
           if(!focus)
               borderColor = mergedColors(QColor(0x06, 0x4C, 0xA4), QColor(0xd6, 0xd6, 0xd6));
           else
               borderColor = QColor(255, 255, 0);
           oldPen.setColor(borderColor);
           painter->setPen(oldPen);
//			painter->setBrush(Qt::transparent);

           painter->fillRect(option->rect, option->palette.brush(QPalette::Base));
           option->rect.getCoords(&x1, &y1, &x2, &y2);
           path.moveTo(x1+0, y1);
           path.lineTo(x2-0, y1);
           path.lineTo(x2, y1+0);
           path.lineTo(x2, y2-0);
           path.lineTo(x2-0, y2);
           path.lineTo(x1+0, y2);
           path.lineTo(x1, y2-0);
           path.lineTo(x1, y1+0);
           path.lineTo(x1+0, y1);
           painter->drawPath(path);

           QRect downArrowRect = subControlRect(CC_ComboBox, comboBox,
               SC_ComboBoxArrow, widget);

           if (comboBox->subControls & SC_ComboBoxArrow) {
               QStyleOptionButton buttonOption;

               buttonOption.QStyleOption::operator=(*comboBox);
               QRect arrowRect(option->rect.right() - downArrowRect.width(),
                   option->rect.top(),
                   downArrowRect.width(),
                   downArrowRect.height());

               buttonOption.rect = arrowRect;
               if(!focus)
                   buttonOption.state = comboBox->state & (State_Enabled | State_MouseOver);
               else
                   buttonOption.state = comboBox->state & (State_Enabled | State_MouseOver | State_HasFocus);
//				drawControl(CE_PushButtonBevel, &buttonOption, painter, widget);

               buttonOption.rect = downArrowRect;
               if(!focus)
                   buttonOption.state = comboBox->state & (State_Enabled | State_MouseOver);
               else
                   buttonOption.state = comboBox->state & (State_Enabled | State_MouseOver | State_HasFocus);
//				drawControl(CE_PushButtonBevel, &buttonOption, painter, widget);

               QImage imgLeftArrow(qt_scrollbar_button_arrow_left);
               QImage imgRightArrow(qt_scrollbar_button_arrow_right);
               //downArrow.setColor(1, comboBox->palette.foreground().color().rgba());
//				int offset = comboBox->direction == Qt::RightToLeft ? -2 : 2;
               if(!focus)
               {
                   imgRightArrow.setColor(1,qRgb(48,255,0));
                   imgLeftArrow.setColor(1,qRgb(48,255,0));
               }
               else
               {
                   imgRightArrow.setColor(1,qRgb(255,255,0));
                   imgLeftArrow.setColor(1,qRgb(255,255,0));
               }
               painter->drawImage(downArrowRect.center().x() - imgLeftArrow.width() / 2,// + offset,
                   downArrowRect.center().y() - imgLeftArrow.height() / 2 + 1, imgLeftArrow);
               painter->drawImage(arrowRect.center().x() - imgRightArrow.width() / 2,// + offset,
                   arrowRect.center().y() - imgRightArrow.height() / 2 + 1, imgRightArrow);


           }

           QRect editFieldRect = subControlRect(CC_ComboBox, comboBox,
               SC_ComboBoxEditField, widget);
           if (comboBox->subControls & SC_ComboBoxEditField) {
// 				QStyleOptionButton buttonOption;
// 				buttonOption.rect = editFieldRect;
// 				if(!focus)
// 					buttonOption.state = comboBox->state & (State_Enabled | State_MouseOver);
// 				else
// 					buttonOption.state = comboBox->state & (State_Enabled | State_MouseOver | State_HasFocus);
// 				drawPrimitive(PE_FrameLineEdit, &buttonOption, painter, widget);

           }
           painter->restore();
       }
       break;
#endif // QT_NO_COMBOBOX
   default:
       QWindowsStyle::drawComplexControl(control, option, painter, widget);
       break;
   }
}

QRect CustomStyle::subControlRect(ComplexControl control, const QStyleOptionComplex *option,
    SubControl subControl, const QWidget */*widget*/) const
{
    QRect rect = option->rect;
    switch (control) {
#ifndef QT_NO_COMBOBOX
    case CC_ComboBox:
        if (const QStyleOptionComboBox *cb = qstyleoption_cast<const QStyleOptionComboBox *>(option))
        {
            int x = cb->rect.x(),
                y = cb->rect.y(),
                wi = cb->rect.width(),
                he = cb->rect.height();
            int xpos = x;
            int margin = cb->frame ? 3 : 0;
            int bmarg = cb->frame ? 2 : 0;
            xpos += wi - bmarg - 16;
            switch (subControl) {
            case SC_ComboBoxFrame:
                rect = cb->rect;
                break;
            case SC_ComboBoxArrow:
                rect.setRect(cb->editable ? xpos : 0, y , wi - xpos, he);
                break;
            case SC_ComboBoxEditField:
                rect.setRect(x + margin + 16, y + margin, wi - 2 * margin - 16 - 16, he - 2 * margin);
                break;
            case SC_ComboBoxListBoxPopup:
                rect = cb->rect;
                break;
            default:
                break;
            }
            rect = visualRect(cb->direction, cb->rect, rect);
            return rect;
        }
#endif // QT_NO_COMBOBOX
            default:
                break;
    }

    return rect;

}

void CustomStyle::setTexture(QPalette &palette, QPalette::ColorRole role,
    const QPixmap &pixmap)
{
    for (int i = 0; i < QPalette::NColorGroups; ++i) {
        QColor color = palette.brush(QPalette::ColorGroup(i), role).color();
        palette.setBrush(QPalette::ColorGroup(i), role, QBrush(color, pixmap));
    }
}

QPainterPath CustomStyle::roundRectPath(const QRect &rect)
{
//      int radius = qMin(rect.width()-2, rect.height()-2) / 2;
//     int diam = 2 * radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);
//     x1+=1;y1+=1;x2-=1;y2-=1;
    QPainterPath path;
//      path.moveTo(x2, y1 + radius);
//      path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
//      path.lineTo(x1 + radius, y1);
//      path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
//      path.lineTo(x1, y2 - radius);
//      path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
//      path.lineTo(x1 + radius, y2);
//      path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);

    path.moveTo(x1+2, y1);
    path.lineTo(x2-2, y1);
    path.lineTo(x2, y1+2);
    path.lineTo(x2, y2-2);
    path.lineTo(x2-2, y2);
    path.lineTo(x1+2, y2);
    path.lineTo(x1, y2-2);
    path.lineTo(x1, y1+2);
    path.lineTo(x1+2, y1);

    path.closeSubpath();
    return path;
}

void CustomStyle::drawHoverRect(QPainter *painter, const QRect &rect) const
{
/*    double h = r.height();
double h2 = r.height() / 2.0;
QPainterPath path;
path.addRect(r.x() + h2, r.y() + 0, r.width() - h2 * 2, r.height());
path.addEllipse(r.x(), r.y(), h, h);
path.addEllipse(r.x() + r.width() - h, r.y(), h, h);
path.setFillRule(Qt::WindingFill);
painter->setPen(Qt::NoPen);
painter->setBrush(QColor(191, 215, 191));
painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPath(path);*/
    int radius = qMin(rect.width(), rect.height()) / 2;
    int diam = 2 * radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);
    QPainterPath path;
    QColor color;
    color = mergedColors(QColor(0x06, 0x4C, 0xA4), QColor(0xd6, 0xd6, 0xd6));
    QPen pen(color, 4);
    painter->setPen(pen);
    path.moveTo(x2, y1 + radius);
    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
    path.lineTo(x1 + radius, y1);
    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
    path.lineTo(x1, y2 - radius);
    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
    path.lineTo(x1 + radius, y2);
    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
    painter->drawPath(path);
}

