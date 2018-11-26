#ifndef UPDATEAPP_H
#define UPDATEAPP_H

#include <QObject>

#define SOH		0x01
#define ACK		0x06
#define NAK     0x15
#define CAN		0x18

class updateapp : public QObject
{
    Q_OBJECT
public:
    explicit updateapp(QObject *parent = 0);
    ~updateapp();

    void openfile();
signals:

public slots:
};

#endif // UPDATEAPP_H
