#include "mycheckboxheader.h"

MyCheckboxHeader::MyCheckboxHeader(Qt::Orientation orientation, QWidget * parent)
    : QHeaderView(orientation, parent),
      isOn(false)
{

}

#if 1
MyCheckboxHeader::~MyCheckboxHeader()
{

}
#endif

void MyCheckboxHeader::cancelSelectAll()
{
    isOn = false;
    emit signalStateTrange(isOn);
    this->update();
}

void MyCheckboxHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if (logicalIndex == 0)
    {
        QStyleOptionButton option;
        option.rect = QRect(10, 10, 10, 10);
        if (isOn)
            option.state = QStyle::State_On;
        else
            option.state = QStyle::State_Off;
        QCheckBox checkBox;
        option.iconSize = QSize(20, 20);
        option.rect = rect;


        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter, &checkBox);
        //this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
    }
}

void MyCheckboxHeader::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int index = logicalIndexAt(event->pos());
        if (index == 0)
        {
            if (isOn)
                isOn = false;
            else
                isOn = true;
        }
        emit signalStateTrange(isOn);
    }

    this->update();
    QHeaderView::mousePressEvent(event);
}
