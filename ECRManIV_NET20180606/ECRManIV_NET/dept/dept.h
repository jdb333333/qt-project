#ifndef DEPT_H
#define DEPT_H

#include <QObject>

class dept : public QObject
{
    Q_OBJECT
public:
    explicit dept(QObject *parent = 0);
    ~dept();

signals:

public slots:
};

#endif // DEPT_H
