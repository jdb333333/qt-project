#include "formwidget.h"
#include "ui_formwidget.h"

#include <QFile>
#include <QFont>
#include <QDebug>

#include <QModelIndex>

Formwidget::Formwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formwidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | windowType());

    this->setAttribute(Qt::WA_ShowModal, true);

    ui->tableWidget->setStyleSheet(getQssContent());

    //�����˵���
    pop_menu = new QMenu();

    ui->tableWidget->installEventFilter(this);

    connect(ui->actionFIXED, SIGNAL(toggled(bool)), this, SLOT(fixed_slot(bool)));
}

Formwidget::~Formwidget()
{
    delete pop_menu;
    delete ui;
}

void Formwidget::fixed_slot(bool flag)
{
    if(flag == true)
    {
        qDebug() << "checked";
    }
    else
    {
        qDebug() << "unchecked";
    }
}

QString Formwidget::getQssContent()
{
    QFile styleSheet("./tablewidgetstyle.txt");

    if(!styleSheet.open(QIODevice::ReadOnly))
    {
        qDebug("Can't open the style sheet file.");
        return "";
    }

    return styleSheet.readAll();
}

void Formwidget::disc_win(void)
{
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setRowCount(4);

    win_type = DISC_WIN;

    QStringList header;

    header << "Indx" << "Name" << "Type" << "Options" << "FixDisc" << "MaxValue";

    ui->tableWidget->setHorizontalHeaderLabels(header);

    //���ñ�ͷ����Ӵ�
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //���ó�������

}

void Formwidget::clerk_win(void)
{
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(5);

    win_type = CLERK_WIN;

    QStringList header;

    header << "Indx" << "Name" << "Options" << "Password";

    ui->tableWidget->setHorizontalHeaderLabels(header);

    //���ñ�ͷ����Ӵ�
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //���ó�������

}

bool Formwidget::eventFilter(QObject *target, QEvent *event)
{
#if 0
    if(event->type() == QEvent::MouseButtonPress)
    {
        qDebug() << "event->button()";
    }
    if(event->type() == QEvent::KeyRelease)
    {
        qDebug() << "event->key";
    }
    if(target == ui->tableWidget)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            qDebug() << "event->button()";
            QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);

            if(mouse_event->button() == Qt::LeftButton)
            {
                qDebug() << "event->button() == Qt::LeftButton";
            }
            return true;
        }
    }
#endif

    //���������������¼��򽻸����ദ��
    return QWidget::eventFilter(target, event);
}

#if 0
void Formwidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "event->button() == Qt::LeftButton";
        QPoint point = event->pos(); //�õ���������
        QTableWidgetItem *item = ui->tableWidget->itemAt(point);

        pop_menu->clear(); //���ԭ�в˵�
        if(item != NULL)
        {
            pop_menu->addAction(ui->actionFIXED);

            //�˵����ֵ�λ��Ϊ��ǰ����λ��
            pop_menu->exec(QCursor::pos());

            event->accept();
        }
    }
}
#endif

void Formwidget::on_tableWidget_clicked(const QModelIndex &index)
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();

    int column = index.column();
    int row =  index.row();

    qDebug() << "column = " << column << "row = " << row;

    pop_menu->clear(); //���ԭ�в˵�

    if(win_type == CLERK_WIN)
    {
        if(column == 2)
        {
            //QString str = item->text();
            pop_menu->addAction(ui->clerk_actionVoid);
            pop_menu->addAction(ui->clerk_actionCorrect);
            pop_menu->addAction(ui->clerk_actionCancle);
            pop_menu->addAction(ui->clerk_actionReturn);
            pop_menu->addAction(ui->clerk_actionDisc);
            pop_menu->addAction(ui->clerk_actionAdd);
            pop_menu->addAction(ui->clerk_actionAmountdisc);
            pop_menu->addAction(ui->clerk_actionTrain);
        }
        else if(column != 0)
        {

        }
    }
    else if(win_type == DISC_WIN)
    {
        pop_menu->addAction(ui->actionFIXED);
        pop_menu->addAction(ui->actionFLOAT);
        pop_menu->addAction(ui->actionFIXED_FLOAT);
    }

    //�˵����ֵ�λ��Ϊ��ǰ����λ��
    pop_menu->exec(QCursor::pos());
}
