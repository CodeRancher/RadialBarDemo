/*************************************************************************************
** The MIT License (MIT)
**
** RadialBarMax is a free Qt and QML based component.
** Copyright (c) 2017 Arun PK
** Email: mailztopk@gmail.com
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
************************************************************************************/

#ifndef RADIALBARMAX_H
#define RADIALBARMAX_H

#include <QQuickPaintedItem>

class RadialBarMax : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(qreal size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal spanAngle READ getSpanAngle WRITE setSpanAngle NOTIFY spanAngleChanged)
    Q_PROPERTY(qreal minValue READ getMinValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(qreal maxValue READ getMaxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(qreal value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString format READ getFormat WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(int dialWidth READ getDialWidth WRITE setDialWidth NOTIFY dialWidthChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor foregroundColor READ getForegroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
    Q_PROPERTY(QColor progressMinColor READ getProgressMinColor WRITE setProgressMinColor NOTIFY progressMinColorChanged)
    Q_PROPERTY(QColor progressMidColor READ getProgressMidColor WRITE setProgressMidColor NOTIFY progressMidColorChanged)
    Q_PROPERTY(QColor progressMaxColor READ getProgressMaxColor WRITE setProgressMaxColor NOTIFY progressMaxColorChanged)
    Q_PROPERTY(int textVertOffset READ getTextVertOffset WRITE setTextVertOffset NOTIFY textVertOffsetChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor textShadowColor READ getTextShadowColor WRITE setTextShadowColor NOTIFY textShadowColorChanged)
    Q_PROPERTY(bool showText READ isShowText WRITE setShowText)
    Q_PROPERTY(Qt::PenCapStyle penStyle READ getPenStyle WRITE setPenStyle NOTIFY penStyleChanged)
    Q_PROPERTY(DialType dialType READ getDialType WRITE setDialType NOTIFY dialTypeChanged)
    Q_PROPERTY(FillType fillType READ getFillType WRITE setFillType NOTIFY fillTypeChanged)
    Q_PROPERTY(QFont textFont READ getTextFont WRITE setTextFont NOTIFY textFontChanged)

public:
    RadialBarMax(QQuickItem *parent = nullptr);
    void paint(QPainter *painter);

    enum DialType {
        FullDial,
        MinToMax,
        MaxToMin,
        NoDial
    };
    Q_ENUM(DialType)

    enum FillType {
        Solid,
        Gradient,
        RotateGradient,
        Point
    };
    Q_ENUM(FillType)

    qreal getSize() {return m_Size;}
    qreal getStartAngle() {return m_StartAngle;}
    qreal getSpanAngle() {return m_SpanAngle;}
    qreal getMinValue() {return m_MinValue;}
    qreal getMaxValue() {return m_MaxValue;}
    qreal getValue() {return m_Value;}
    QString getFormat() {return m_Format;}
    int getDialWidth() {return m_DialWidth;}
    QColor getBackgroundColor() {return m_BackgroundColor;}
    QColor getForegroundColor() {return m_DialColor;}
    QColor getProgressMinColor() {return m_ProgressMinColor;}
    QColor getProgressMidColor() {return m_ProgressMidColor;}
    QColor getProgressMaxColor() {return m_ProgressMaxColor;}

    int getTextVertOffset() {return m_TextVertOffset;}
    QColor getTextColor() {return m_TextColor;}
    QColor getTextShadowColor() {return m_TextShadowColor;}
    //QString getSuffixText() {return m_SuffixText;}
    bool isShowText() {return m_ShowText;}
    Qt::PenCapStyle getPenStyle() {return m_PenStyle;}
    DialType getDialType() {return m_DialType;}
    FillType getFillType() {return m_FillType;}
    QFont getTextFont() {return m_TextFont;}

    void setSize(qreal size);
    void setStartAngle(qreal angle);
    void setSpanAngle(qreal angle);
    void setMinValue(qreal value);
    void setMaxValue(qreal value);
    void setValue(qreal value);
    void setFormat(QString text);
    void setDialWidth(qreal width);
    void setBackgroundColor(QColor color);
    void setForegroundColor(QColor color);
    void setProgressMinColor(QColor color);
    void setProgressMidColor(QColor color, bool colorSet = true);
    void setProgressMaxColor(QColor color, bool colorSet = true);
    void setTextVertOffset(qreal value);
    void setTextColor(QColor color);
    void setTextShadowColor(QColor color);
    void setShowText(bool show);
    void setPenStyle(Qt::PenCapStyle style);
    void setDialType(DialType type);
    void setFillType(FillType type);
    void setTextFont(QFont font);

signals:
    void sizeChanged();
    void startAngleChanged();
    void spanAngleChanged();
    void minValueChanged();
    void maxValueChanged();
    void valueChanged();
    void formatChanged();
    void dialWidthChanged();
    void backgroundColorChanged();
    void foregroundColorChanged();
    void progressMinColorChanged();
    void progressMidColorChanged();
    void progressMaxColorChanged();
    void textVertOffsetChanged();
    void textColorChanged();
    void textShadowColorChanged();
    void penStyleChanged();
    void dialTypeChanged();
    void fillTypeChanged();
    void textFontChanged();

private:
    qreal m_Size;
    qreal m_StartAngle;
    qreal m_SpanAngle;
    qreal m_MinValue;
    qreal m_MaxValue;
    qreal m_Value;
    QString m_Format;
    int m_DialWidth;
    QColor m_BackgroundColor;
    QColor m_DialColor;
    QColor m_ProgressMinColor;
    QColor m_ProgressMidColor;
    bool m_ProgressMidColorSet;
    QColor m_ProgressMaxColor;
    bool m_ProgressMaxColorSet;
    int m_TextVertOffset;
    QColor m_TextColor;
    QColor m_TextShadowColor;
    bool m_ShowText;
    Qt::PenCapStyle m_PenStyle;
    DialType m_DialType;
    FillType m_FillType;
    QFont m_TextFont;

    static int ShadowOffsetX;
    static int ShadowOffsetY;

    void drawText(QPainter *painter, QRectF rect, QString text);
    QString getTimeText(int sec);
};

#endif // RADIALBARMAX_H
