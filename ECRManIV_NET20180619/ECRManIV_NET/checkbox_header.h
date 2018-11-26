#ifndef CHECKBOX_HEADER_H
#define CHECKBOX_HEADER_H

#include <QObject>

class checkbox_header : public QObject
{
    Q_OBJECT
public:
    explicit checkbox_header(QObject *parent = 0);
    ~checkbox_header();

signals:

public slots:
};

#endif // CHECKBOX_HEADER_H
