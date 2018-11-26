#ifndef CLERK_H
#define CLERK_H

#include <QObject>

class clerk : public QObject
{
    Q_OBJECT
public:
    explicit clerk(QObject *parent = 0);
    ~clerk();

signals:

public slots:
};

#endif // CLERK_H
