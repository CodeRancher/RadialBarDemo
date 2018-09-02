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

#include <cmath>
#include <algorithm>
#include <QPainter>

#include "radialbarmax.h"

int RadialBarMax::ShadowOffsetX = 3;
int RadialBarMax::ShadowOffsetY = 3;

RadialBarMax::RadialBarMax(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_Size(200),
      m_StartAngle(40),
      m_SpanAngle(280),
      m_MinValue(0),
      m_MaxValue(100),
      m_Value(50),
      m_Format("%f"),
      m_DialWidth(15),
      m_BackgroundColor(Qt::transparent),
      m_DialColor(QColor(80,80,80)),
      m_ProgressMinColor(QColor(135,26,5)),
      m_ProgressMidColor(QColor(135,26,5)),
      m_ProgressMidColorSet(false),
      m_ProgressMaxColor(QColor(135,26,5)),
      m_ProgressMaxColorSet(false),
      m_TextVertOffset(0),
      m_TextColor(QColor(0, 0, 0)),
      m_TextShadowColor(QColor(100, 100, 100)),
      //m_SuffixText(""),
      m_ShowText(true),
      m_PenStyle(Qt::FlatCap),
      m_DialType(DialType::MinToMax),
      m_FillType(FillType::Solid)
{
    setWidth(200);
    setHeight(200);
    setSmooth(true);
    setAntialiasing(true);
}

void RadialBarMax::paint(QPainter *painter)
{
    double startAngle;
    double spanAngle;
    qreal size = qMin(this->width(), this->height());
    setWidth(size);
    setHeight(size);
    QRectF rect = this->boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(m_PenStyle);

    startAngle = -90 - m_StartAngle;
    if(FullDial != m_DialType) {
        spanAngle = 0 - m_SpanAngle;
    }
    else {
        spanAngle = -360;
    }

    //Draw outer dial
    painter->save();
    pen.setWidth(m_DialWidth);
    pen.setColor(m_DialColor);
    painter->setPen(pen);
    qreal offset = m_DialWidth / 2;

    switch(m_DialType) {
        case MinToMax:
            painter->drawArc(rect.adjusted(offset, offset, -offset, -offset), startAngle * 16, spanAngle * 16);
            break;
        case MaxToMin:
            painter->drawArc(rect.adjusted(offset, offset, -offset, -offset), startAngle * 16, spanAngle * 16);
            break;
        case FullDial:
            painter->drawArc(rect.adjusted(offset, offset, -offset, -offset), -90 * 16, -360 * 16);
            break;
        case NoDial:
            break;
    }
    painter->restore();

    //Draw background
    painter->save();
    painter->setBrush(m_BackgroundColor);
    painter->setPen(m_BackgroundColor);
    qreal inner = offset * 2;
    painter->drawEllipse(rect.adjusted(inner, inner, -inner, -inner));
    painter->restore();

    //Draw progress text
    //painter->save();
    //painter->setFont(m_TextFont);
    //pen.setColor(m_TextColor);
    //painter->setPen(pen);
    if(m_ShowText)
    {
        QString text;
        if (m_Format.compare("%TIME%") == 0) {
            text = getTimeText(std::nearbyint(m_Value - m_MinValue));
        } else if (m_Format.compare("%ETIME%") == 0) {
            text = getTimeText(std::nearbyint(m_MaxValue - m_Value));
        } else {
            text.sprintf(m_Format.toStdString().c_str(), m_Value);
        }
        drawText(painter, rect.adjusted(offset, offset + m_TextVertOffset, -offset, -offset + m_TextVertOffset), text);
        //painter->drawText(rect.adjusted(offset, offset + m_TextVertOffset, -offset, -offset + m_TextVertOffset), Qt::AlignCenter, text);
    }
    painter->restore();

    //Draw progress bar
    painter->save();
    pen.setWidth(m_DialWidth);
    //pen.setColor(m_ProgressColor);
    qreal value = std::min(std::max(m_MinValue, m_Value), m_MaxValue);
    qreal valueAngle;

    switch(m_DialType) {
        case MinToMax:
        case FullDial:
        case NoDial:
            valueAngle = ((value - m_MinValue)/(m_MaxValue - m_MinValue)) * spanAngle;  //Map value to angle range
            //qInfo() << "MinToMax: " << valueAngle;
            break;
        case MaxToMin:
            valueAngle = ((m_MaxValue - value)/(m_MaxValue - m_MinValue)) * spanAngle;  //Map value to angle range
            //qInfo() << "MaxToMin: " << valueAngle;
            break;
    }

    switch(m_FillType) {
        case Solid:
            pen.setBrush(QBrush(m_ProgressMidColor));
            break;
        case Point:
        case RotateGradient:
        case Gradient:
            int gradientRotation = -90;
            if (m_FillType == FillType::RotateGradient) {
                gradientRotation += valueAngle - 90;
            }
            QConicalGradient gradient(QPointF(this->width() / 2.0, this->height() / 2.0), gradientRotation);
            gradient.setColorAt(0.00, m_DialType == DialType::MinToMax ? m_ProgressMaxColor : m_ProgressMinColor);
            gradient.setColorAt(0.16, m_DialType == DialType::MinToMax ? m_ProgressMaxColor : m_ProgressMinColor);
            gradient.setColorAt(0.50, m_ProgressMidColor);
            gradient.setColorAt(0.84, m_DialType == DialType::MinToMax ? m_ProgressMinColor : m_ProgressMaxColor);
            gradient.setColorAt(1.00, m_DialType == DialType::MinToMax ? m_ProgressMinColor : m_ProgressMaxColor);

            pen.setBrush(QBrush(gradient));
            break;
    }

    painter->setPen(pen);
    qInfo() << "valueAngle: " << m_MinValue << ":" <<  m_MaxValue << ":" << valueAngle;
    if (m_FillType == FillType::Point) {
        painter->drawArc(rect.adjusted(offset, offset, -offset, -offset), (startAngle + valueAngle) * 16, 16);
    }
    else {
        painter->drawArc(rect.adjusted(offset, offset, -offset, -offset), startAngle * 16, valueAngle * 16);
    }
    painter->restore();
}

void RadialBarMax::drawText(QPainter *painter, QRectF rect, QString text)
{
    painter->save();
    painter->setFont(m_TextFont);
    QPen pen = painter->pen();
    pen.setColor(m_TextShadowColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(ShadowOffsetX, ShadowOffsetY, ShadowOffsetX, ShadowOffsetY), Qt::AlignCenter, text);

    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect, Qt::AlignCenter, text);

}

QString RadialBarMax::getTimeText(int sec)
{
    QString text;
    unsigned int seconds = std::abs(sec % 60);
    unsigned int minutes = std::abs((sec / 60) % 60);
    unsigned int hours = std::abs(sec / (60 * 60));
    if (sec < 0) {
        text.sprintf("-%d:%02d:%02d", hours, minutes, seconds);
    } else {
        text.sprintf("%d:%02d:%02d", hours, minutes, seconds);
    }
    return text;
}

void RadialBarMax::setSize(qreal size)
{
    if(m_Size == size)
        return;
    m_Size = size;
    emit sizeChanged();
}

void RadialBarMax::setStartAngle(qreal angle)
{
    if(m_StartAngle == angle)
        return;
    m_StartAngle = angle;
    emit startAngleChanged();
}

void RadialBarMax::setSpanAngle(qreal angle)
{
    if(m_SpanAngle == angle)
        return;
    m_SpanAngle = angle;
    emit spanAngleChanged();
}

void RadialBarMax::setMinValue(qreal value)
{
    if(m_MinValue == value)
        return;
    m_MinValue = value;
    emit minValueChanged();
}

void RadialBarMax::setMaxValue(qreal value)
{
    if(m_MaxValue == value)
        return;
    m_MaxValue = value;
    emit maxValueChanged();
}

void RadialBarMax::setValue(qreal value)
{
    if(m_Value == value)
        return;
    m_Value = value;
    update();   //update the radialbarmax
    emit valueChanged();
}

void RadialBarMax::setFormat(QString text)
{
    if(m_Format == text)
        return;
    m_Format = text;
    emit formatChanged();
}

void RadialBarMax::setDialWidth(qreal width)
{
    if(m_DialWidth == width)
        return;
    m_DialWidth = std::nearbyint(width);
    emit dialWidthChanged();
}

void RadialBarMax::setBackgroundColor(QColor color)
{
    if(m_BackgroundColor == color)
        return;
    m_BackgroundColor = color;
    emit backgroundColorChanged();
}

void RadialBarMax::setForegroundColor(QColor color)
{
    if(m_DialColor == color)
        return;
    m_DialColor = color;
    emit foregroundColorChanged();
}

void RadialBarMax::setProgressMinColor(QColor color)
{
    if(m_ProgressMinColor == color)
        return;
    m_ProgressMinColor = color;
    emit progressMinColorChanged();

    if (!m_ProgressMidColorSet)
        setProgressMidColor(color, false);
    if (!m_ProgressMaxColorSet)
        setProgressMaxColor(color, false);
}

void RadialBarMax::setProgressMidColor(QColor color, bool colorSet)
{
    m_ProgressMidColorSet = m_ProgressMidColorSet || colorSet;
    if(m_ProgressMidColor == color)
        return;
    m_ProgressMidColor = color;
    emit progressMidColorChanged();
}

void RadialBarMax::setProgressMaxColor(QColor color, bool colorSet)
{
    m_ProgressMaxColorSet = m_ProgressMaxColorSet || colorSet;
    if(m_ProgressMaxColor == color)
        return;
    m_ProgressMaxColor = color;
    emit progressMaxColorChanged();
}

void RadialBarMax::setTextVertOffset(qreal value)
{
    if(m_TextVertOffset == std::round(value))
        return;
    m_TextVertOffset = std::nearbyint(value);
    update();   //update the radialbarmax
    emit textVertOffsetChanged();
}

void RadialBarMax::setTextColor(QColor color)
{
    if(m_TextColor == color)
        return;
    m_TextColor = color;
    emit textColorChanged();
}

void RadialBarMax::setTextShadowColor(QColor color)
{
    if(m_TextShadowColor == color)
        return;
    m_TextShadowColor = color;
    emit textShadowColorChanged();
}

void RadialBarMax::setShowText(bool show)
{
    if(m_ShowText == show)
        return;
    m_ShowText = show;
}

void RadialBarMax::setPenStyle(Qt::PenCapStyle style)
{
    if(m_PenStyle == style)
        return;
    m_PenStyle = style;
    emit penStyleChanged();
}

void RadialBarMax::setDialType(RadialBarMax::DialType type)
{
    if(m_DialType == type)
        return;
    m_DialType = type;
    emit dialTypeChanged();
}

void RadialBarMax::setFillType(RadialBarMax::FillType type)
{
    if(m_FillType == type)
        return;
    m_FillType = type;
    emit fillTypeChanged();
}

void RadialBarMax::setTextFont(QFont font)
{
    if(m_TextFont == font)
        return;
    m_TextFont = font;
    emit textFontChanged();
}


