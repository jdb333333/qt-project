#include <QtDebug>
#include <QKeyEvent>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->textEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << "Ate key press " << keyEvent->key();
            QString info;
            QTextStream(&info) << "Ate key press " << keyEvent->key();
            ui->textEdit_3->append(info);
            return true;
        } else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}

void MainWindow::closeEvent(QCloseEvent * event) {
    int ret = QMessageBox::warning(0, tr("MainWindow"), tr("Do you really want to exit?"), QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        event->accept(); //确认关闭
    } else {
        event->ignore(); //不关闭
    }
}

void MainWindow::mouseMoveEvent ( QMouseEvent * e )//鼠标移动事件响应
{
    //1.获取局部鼠标位置
    QString info;
    QTextStream(&info) << "Move (" << QString::number(e->x()) << "," << QString::number(e->y()) << ")";
    ui->textEdit_3->append(info);

    //2.获取全局鼠标位置

    /*QPoint coursePoint;
    coursePoint = QCursor::pos();//获取当前光标的位置
    QTextStream(&info) << "Move (" << QString::number(coursePoint.x()) << "," << QString::number(coursePoint.y()) << ")";
    ui->textEdit_3->append(info);*/

}

void MainWindow::mousePressEvent ( QMouseEvent * e )//鼠标单击事件响应
{
    qDebug() << "Has mouse tracking: " << this->hasMouseTracking();
    QString str="("+QString::number(e->x())+","+QString::number(e->y())+")";
    QString info;
    if(e->button()==Qt::LeftButton)
    {
        QTextStream(&info) << tr("Mouse Left Button Pressed:")+str;
        ui->textEdit_3->append(info);

        statusBar()->showMessage (tr("Mouse Left Button Pressed:")+str);//显示临时信息
    }
    else if(e->button()==Qt::RightButton)
    {
        QTextStream(&info) << tr("Mouse Right Button Pressed:")+str;
        ui->textEdit_3->append(info);

        statusBar()->showMessage (tr("Mouse Right Button Pressed:")+str);
    }
    else if(e->button()==Qt::MidButton)
    {
        QTextStream(&info) << tr("Mouse Middle Button Pressed:")+str;
        ui->textEdit_3->append(info);

        statusBar()->showMessage (tr("Mouse Middle Button Pressed:")+str);
    }
}

void MainWindow::mouseDoubleClickEvent( QMouseEvent * e )//鼠标双击事件响应
{
    QString str="("+QString::number(e->x())+","+QString::number(e->y())+")";
    QString info;
    if(e->button()==Qt::LeftButton)
    {
        QTextStream(&info) << tr("Mouse Left Button Double Clicked:")+str;
        ui->textEdit_3->append(info);
        statusBar()->showMessage (tr("Mouse Left Button Double Clicked:")+str);
    }
    else if(e->button()==Qt::RightButton)
    {
        QTextStream(&info) << tr("Mouse Right Button Double Clicked:")+str;
        ui->textEdit_3->append(info);
        statusBar()->showMessage (tr("Mouse Right Button Double Clicked:")+str);
    }
    else if(e->button()==Qt::MidButton)
    {
        QTextStream(&info) << tr("Mouse Middle Button Double Clicked:")+str;
        ui->textEdit_3->append(info);
        statusBar()->showMessage (tr("Mouse Middle Button Double Clicked:")+str);
    }
}

void MainWindow::mouseReleaseEvent ( QMouseEvent * e )//鼠标松开事件响应
{
    QString str="("+QString::number(e->x())+","+QString::number(e->y())+")";
    QString info;
    QTextStream(&info) << tr("Mouser Released:")+str;
    ui->textEdit_3->append(info);
    statusBar()->showMessage (tr("Mouser Released:")+str,3000);
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    //自动跟踪鼠标（默认情况下，mouseMoveEvent响应你按下鼠标的某个键的鼠标移动。）
    centralWidget()->setMouseTracking(checked);
}
