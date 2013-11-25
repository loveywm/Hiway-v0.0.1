#ifndef CUSTOMSTYLE_H
#define CUSTOMSTYLE_H
/*
#include <QWindowsStyle>

class CustomStyle : public QWindowsStyle
{
public:
    CustomStyle();
};
*/
#include <QWindowsStyle>
#include <QPalette>

class QPainterPath;

// class CustomStyle : public QWindowsStyle
class CustomStyle : public QWindowsStyle
{
    Q_OBJECT

public:
     CustomStyle() {}
     void polish(QPalette &palette);
     void polish(QWidget *widget);
     void unpolish(QWidget *widget);
     int pixelMetric(PixelMetric metric, const QStyleOption *option,
                     const QWidget *widget) const;
     int styleHint(StyleHint hint, const QStyleOption *option,
                   const QWidget *widget, QStyleHintReturn *returnData) const;
     void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                        QPainter *painter, const QWidget *widget) const;
     void drawControl(ControlElement control, const QStyleOption *option,
                      QPainter *painter, const QWidget *widget) const;
     void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option,
                           QPainter *painter, const QWidget *widget) const;
     QRect subControlRect(ComplexControl control, const QStyleOptionComplex *option,
        SubControl subControl, const QWidget *widget) const;
     void drawHoverRect(QPainter *painter, const QRect &r) const;

     static QPainterPath roundRectPath(const QRect &rect);
private:
     static void setTexture(QPalette &palette, QPalette::ColorRole role,
                            const QPixmap &pixmap);
 };

#endif // CUSTOMSTYLE_H
