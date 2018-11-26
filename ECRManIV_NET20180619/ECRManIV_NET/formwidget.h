#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QMouseEvent>

#define CLERK_WIN 0x01
#define DISC_WIN 0x02

class QModelIndex;

namespace Ui {
class Formwidget;
}

class Formwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Formwidget(QWidget *parent = 0);
    ~Formwidget();

private:
    Ui::Formwidget *ui;

public:
    void disc_win(void);
    void clerk_win(void);

private:
    char win_type;
    QMenu *pop_menu;

    QString getQssContent();

protected:
    bool eventFilter(QObject *target, QEvent *event);
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);

    void fixed_slot(bool flag);
};

#endif // FORMWIDGET_H
