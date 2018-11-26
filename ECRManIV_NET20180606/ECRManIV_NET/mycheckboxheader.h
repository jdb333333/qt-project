#ifndef MYCHECKBOXHEADER_H
#define MYCHECKBOXHEADER_H

#include <QtGui>
#include <QObject>

class MyCheckboxHeader : public QHeaderView
{
    Q_OBJECT

public:
    MyCheckboxHeader(Qt::Orientation orientation, QWidget * parent = 0);
    ~MyCheckboxHeader();

    void cancelSelectAll();

signals:
    void signalStateTrange(int);
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *event);
private:
    bool isOn;
};

#endif // MYCHECKBOXHEADER_H
