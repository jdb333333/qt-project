#ifndef EXDATA_H
#define EXDATA_H

#include <QWidget>
#include <QScopedPointer>

class ExcelBase;

namespace Ui {
class exdata;
}

class exdata : public QWidget
{
    Q_OBJECT

public:
    explicit exdata(QWidget *parent = 0);
    ~exdata();

private:
    Ui::exdata *ui;

    QScopedPointer<ExcelBase> m_xls;
    QList< QList<QVariant> > m_datas;

    char recvbuf[1024];

signals:
    void unconnecthost();
    void connecthost();
    void recvdata(char *buf, int len);
    void senddata(char *buf, int len);
private slots:
    void on_pushButton_2_clicked();
    void on_openfile_clicked();
    void on_pushButton_clicked();

    void recvdataok(int sizelen);
    void tcpstate(int type);
};

#endif // EXDATA_H
