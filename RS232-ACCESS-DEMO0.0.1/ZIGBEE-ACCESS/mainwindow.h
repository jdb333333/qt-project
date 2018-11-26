#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ui_init(void);
    MyThread threadA;



private slots:
    void displayRxData();

    void on_pushButton_8_clicked();

    void on_pushButton_cmopen_clicked();

    void on_pushButton_comclose_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_send_clicked();

    void on_radioButton_01_clicked();

    void on_radioButton_31_clicked();

    void on_radioButton_07_clicked();

    void on_radioButton_19_clicked();

    void on_radioButton_1F_clicked();

    void on_radioButton_0D_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_02_clicked();

    void on_textEdit_rx_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
