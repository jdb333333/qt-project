#include "flowbill.h"

#include "./ejdb/ejdb.h"

#include "../comm.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QCoreApplication>

EJData ejdata;

flowbill::flowbill(QObject *parent) : QObject(parent)
{
    MyEJ = new ejdb(this);

    memset(&ejdata, 0, sizeof(ejdata));

    ejlog = false;
}

flowbill::~flowbill()
{
    delete MyEJ;
}

int flowbill::EjDataTrans(char *data, int len, char *buf)
{
    int datalen, strlen;
    BYTE id;

    datalen = 0;
    strlen = 0;

    while(datalen < len)
    {
        FlowBuff = (union  FLOWREC	 *)(data + datalen);
        id = FlowBuff->CDC_dpt.FunN & 0x1f;

        if(id == REGISLOG)
        {
            qDebug() << "--->REGISLOG"; //一张票据开始
            qDebug() << "FlowBuff->CDC_regis.EcrNumber = " << FlowBuff->CDC_regis.EcrNumber;
            qDebug("FlowBuff->CDC_regis.OperNo = %02x", FlowBuff->CDC_regis.OperNo);
            qDebug("FlowBuff->CDC_regis.FYear = %02x", FlowBuff->CDC_regis.FYear);
            qDebug("FlowBuff->CDC_regis.FMonth = %02x", FlowBuff->CDC_regis.FMonth);
            qDebug("FlowBuff->CDC_regis.FDay = %02x", FlowBuff->CDC_regis.FDay);
            qDebug("FlowBuff->CDC_regis.FHour = %02x", FlowBuff->CDC_regis.FHour);
            qDebug("FlowBuff->CDC_regis.FMinute = %02x", FlowBuff->CDC_regis.FMinute);
            qDebug("FlowBuff->CDC_regis.FSecond = %02x", FlowBuff->CDC_regis.FSecond);

            comm::ChToStr(buf + strlen, '-', FLOWTXTLEN);
            strlen += FLOWTXTLEN;

            datalen += sizeof(FlowBuff->CDC_regis);
        }

        if(id == RESERVERLOG)
        {
            qDebug() << "--->RESERVERLOG";
        }

        if(id == DEPTLOG)
        {
            qDebug() << "--->DEPTLOG";
            datalen += sizeof(FlowBuff->CDC_dpt);
        }

        if(id == PLULOG)
        {
            qDebug() << "--->PLULOG";
            datalen += sizeof(FlowBuff->CDC_art);
        }

        if(id == ENDLOG)
        {
            qDebug() << "--->ENDLOG";
            datalen += sizeof(FlowBuff->CDC_end);
        }

        if(id == NOADDLOG)
        {
            qDebug() << "--->NOADDLOG";
            datalen += sizeof(FlowBuff->CDC_noadd);
        }

        if(id == OPERLOG)
        {
            qDebug() << "--->OPERLOG";
            datalen += sizeof(FlowBuff->CDC_oper);
        }

        if(id == TENDLOG)
        {
            qDebug() << "--->TENDLOG"; //一张票据结束，写入数据库
            datalen += sizeof(FlowBuff->CDC_given);
        }

        if(id == LOCKLOG)
        {
            qDebug() << "--->LOCKLOG";
            datalen += sizeof(FlowBuff->CDC_lock);
        }

        if(id == DISCADDLOG)
        {
            qDebug() << "--->DISCADDLOG";
            datalen += sizeof(FlowBuff->CDC_discadd);
        }

        if(id == SUBDISCADDLOG)
        {
            qDebug() << "--->SUBDISCADDLOG";
            datalen += sizeof(FlowBuff->CDC_subdiscadd);
        }

        if(id == DIRECTLOG)
        {
            qDebug() << "--->DIRECTLOG";
            datalen += sizeof(FlowBuff->CDC_direct);
        }

        if(id == SUBDIRECTLOG)
        {
            qDebug() << "--->SUBDIRECTLOG";
            datalen += sizeof(FlowBuff->CDC_subdirect);
        }

        if(id == SUBTOTALLOG)
        {
            qDebug() << "--->SUBTOTALLOG";
            datalen += sizeof(FlowBuff->CDC_subtotal);
        }

        if(id == SLIPENDLOG)
        {
            qDebug() << "--->SLIPENDLOG";
            datalen += sizeof(FlowBuff->CDC_slipend);
        }

        if(id == INSERTICLOG)
        {
            qDebug() << "--->INSERTICLOG";
            datalen += sizeof(FlowBuff->CDC_enteric);
        }

        if(id == REFRESHICLOG)
        {
            qDebug() << "--->REFRESHICLOG";
            datalen += sizeof(FlowBuff->CDC_refreshic);
        }

        if(id == PRICELISTLOG)
        {
            qDebug() << "--->PRICELISTLOG";
            datalen += sizeof(FlowBuff->CDC_pricelist);
        }

        if(id == ECRNOLOG)
        {
            qDebug() << "--->ECRNOLOG";
            datalen += sizeof(FlowBuff->CDC_EcrNum);
        }

        if(id == TVOIDLOG)
        {
            qDebug() << "--->TVOIDLOG";
            datalen += sizeof(FlowBuff->CDC_Void);
        }

        if(id == PBCLOSELOG)
        {
            qDebug() << "--->PBCLOSELOG";
            datalen += sizeof(FlowBuff->CDC_PbClose);
        }

        if(id == PBOPENLOG)
        {
            qDebug() << "--->PBOPENLOG";
            datalen += sizeof(FlowBuff->CDC_PbOpen);
        }

        if(id == TRTABLELOG)
        {
            qDebug() << "--->TRTABLELOG";
            datalen += sizeof(FlowBuff->CDC_PbTt);
        }

        if(id == PORALOG)
        {
            qDebug() << "--->PORALOG";
            datalen += sizeof(FlowBuff->CDC_PoRa);
        }

        if(id == NETIDLOG)
        {
            qDebug() << "--->NETIDLOG";
            datalen += sizeof(FlowBuff->CDC_NetID);
        }

        if(id == TAXLOG)
        {
            qDebug() << "--->TAXLOG";
            datalen += sizeof(FlowBuff->CDC_Tax);
        }
    }

    return strlen;
}

int flowbill::EjDataTrans(char *data, int len, QStandardItemModel *reportModel)
{
    int datalen, strlen;
    BYTE id;
    int rows_display;
    EJData *ej_data = (EJData *)data;
    char *ej_data_blob = ej_data->blobbuf;

    datalen = 0;
    strlen = 0;

    while(datalen < len)
    {
        FlowBuff = (union  FLOWREC	 *)(ej_data_blob + datalen);
        id = FlowBuff->CDC_dpt.FunN & 0x1f;

        if(id == REGISLOG)
        {
            qDebug() << "--->REGISLOG"; //一张票据开始
            qDebug() << "FlowBuff->CDC_regis.EcrNumber = " << FlowBuff->CDC_regis.EcrNumber;
            qDebug("FlowBuff->CDC_regis.OperNo = %02x", FlowBuff->CDC_regis.OperNo);
            qDebug("FlowBuff->CDC_regis.FYear = %02x", FlowBuff->CDC_regis.FYear);
            qDebug("FlowBuff->CDC_regis.FMonth = %02x", FlowBuff->CDC_regis.FMonth);
            qDebug("FlowBuff->CDC_regis.FDay = %02x", FlowBuff->CDC_regis.FDay);
            qDebug("FlowBuff->CDC_regis.FHour = %02x", FlowBuff->CDC_regis.FHour);
            qDebug("FlowBuff->CDC_regis.FMinute = %02x", FlowBuff->CDC_regis.FMinute);
            qDebug("FlowBuff->CDC_regis.FSecond = %02x", FlowBuff->CDC_regis.FSecond);

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            reportModel->setData(reportModel->index(rows_display, 0), QString("--------------------"));
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0xff, 0xff, 0xff)));

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Indx;
            Indx.sprintf("#%06d", ej_data->Indx);
            reportModel->setData(reportModel->index(rows_display, 0), Indx);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0, 0, 0)));

            QString Oper;
            Oper.sprintf("Operator:%s", FlowBuff->CDC_regis.Name);
            reportModel->setData(reportModel->index(rows_display, 2), Oper);
            reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(0, 0, 0)));

            int year, month, day, hour, min, sec;
            year = 2000 + comm::OneBCDToInt(FlowBuff->CDC_regis.FYear);
            month = comm::OneBCDToInt(FlowBuff->CDC_regis.FMonth);
            day = comm::OneBCDToInt(FlowBuff->CDC_regis.FDay);
            hour = comm::OneBCDToInt(FlowBuff->CDC_regis.FHour);
            min = comm::OneBCDToInt(FlowBuff->CDC_regis.FMinute);
            sec = comm::OneBCDToInt(FlowBuff->CDC_regis.FSecond);
            QString DateTime = QString("%1-%2-%3 %4:%5:%6").arg(year).arg(month).arg(day)
                    .arg(hour).arg(min).arg(sec);
            reportModel->setData(reportModel->index(rows_display, 4), DateTime);
            reportModel->item(rows_display, 4)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 4)->setForeground(QBrush(QColor(0, 0, 0)));

            datalen += sizeof(FlowBuff->CDC_regis);
        }

        if(id == RESERVERLOG)
        {
            qDebug() << "--->RESERVERLOG";
        }

        if(id == DEPTLOG)
        {
            qDebug() << "--->DEPTLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Name;
            Name.sprintf("%s", FlowBuff->CDC_dpt.Name);
            reportModel->setData(reportModel->index(rows_display, 0), Name);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            if(FlowBuff->CDC_dpt.FunN & 0x40)
            {
                QString Cancel("Cancel");
                reportModel->setData(reportModel->index(rows_display, 1), Cancel);
                reportModel->item(rows_display, 1)->setTextAlignment(Qt::AlignCenter);
                reportModel->item(rows_display, 1)->setForeground(QBrush(QColor(0xff, 0x0, 0x0)));
            }
            else if(FlowBuff->CDC_dpt.FunN & 0x80)
            {
                QString Return("Return");
                reportModel->setData(reportModel->index(rows_display, 1), Return);
                reportModel->item(rows_display, 1)->setTextAlignment(Qt::AlignCenter);
                reportModel->item(rows_display, 1)->setForeground(QBrush(QColor(0xff, 0x0, 0x0)));
            }

            QString Qty;
            if(FlowBuff->CDC_dpt.FunN & 0x40 || FlowBuff->CDC_dpt.FunN & 0x80)
            {
                Qty.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_dpt.FQty, 4, 3));
            }
            else
            {
                Qty.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_dpt.FQty, 4, 3));
            }
            reportModel->setData(reportModel->index(rows_display, 2), Qty);
            reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_dpt.FunN & 0x40 || FlowBuff->CDC_dpt.FunN & 0x80)
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_dpt.FAmt, 5, 2));
            }
            else
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_dpt.FAmt, 5, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_dpt);
        }

        if(id == PLULOG)
        {
            qDebug() << "--->PLULOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Name;
            Name.sprintf("%s", FlowBuff->CDC_art.Name);
            reportModel->setData(reportModel->index(rows_display, 0), Name);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            if(FlowBuff->CDC_art.FunN & 0x40)
            {
                QString Cancel("Cancel");
                reportModel->setData(reportModel->index(rows_display, 1), Cancel);
                reportModel->item(rows_display, 1)->setTextAlignment(Qt::AlignCenter);
                reportModel->item(rows_display, 1)->setForeground(QBrush(QColor(0xff, 0x0, 0x0)));
            }
            else if(FlowBuff->CDC_art.FunN & 0x80)
            {
                QString Return("Return");
                reportModel->setData(reportModel->index(rows_display, 1), Return);
                reportModel->item(rows_display, 1)->setTextAlignment(Qt::AlignCenter);
                reportModel->item(rows_display, 1)->setForeground(QBrush(QColor(0xff, 0x0, 0x0)));
            }

            QString Qty;
            if(FlowBuff->CDC_art.FunN & 0x40 || FlowBuff->CDC_art.FunN & 0x80)
            {
                Qty.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_art.FQty, 4, 3));
            }
            else
            {
                Qty.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_art.FQty, 4, 3));
            }
            reportModel->setData(reportModel->index(rows_display, 2), Qty);
            reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_art.FunN & 0x40 || FlowBuff->CDC_art.FunN & 0x80)
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_art.FAmt, 5, 2));
            }
            else
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_art.FAmt, 5, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_art);
        }

        if(id == ENDLOG)
        {
            qDebug() << "--->ENDLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString YingFu("Pay Must");
            reportModel->setData(reportModel->index(rows_display, 0), YingFu);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_end.FunN & 0x40 || FlowBuff->CDC_end.FunN & 0x80)
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_end.FAmt, 6, 2));
            }
            else
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_end.FAmt, 6, 2));
            }
            //Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_end.FAmt, 6, 2));
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            int year, month, day, hour, min;
            year = 2000 + comm::OneBCDToInt(FlowBuff->CDC_end.FYear);
            month = comm::OneBCDToInt(FlowBuff->CDC_end.FMonth);
            day = comm::OneBCDToInt(FlowBuff->CDC_end.FDay);
            hour = comm::OneBCDToInt(FlowBuff->CDC_end.FHour);
            min = comm::OneBCDToInt(FlowBuff->CDC_end.FMinute);
            QString DateTime = QString("%1-%2-%3 %4:%5").arg(year).arg(month).arg(day)
                    .arg(hour).arg(min);
            reportModel->setData(reportModel->index(rows_display, 4), DateTime);
            reportModel->item(rows_display, 4)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 4)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_end);
        }

        if(id == NOADDLOG)
        {
            qDebug() << "--->NOADDLOG";
            datalen += sizeof(FlowBuff->CDC_noadd);
        }

        if(id == OPERLOG)
        {
            qDebug() << "--->OPERLOG";
            datalen += sizeof(FlowBuff->CDC_oper);
        }

        if(id == TENDLOG)
        {
            qDebug() << "--->TENDLOG"; //一张票据结束，写入数据库

            for(int i = 0; i < FlowBuff->CDC_given.Counter; i++)
            {
                rows_display = reportModel->rowCount();
                reportModel->insertRow(rows_display);

                QString Cash("Cash");
                reportModel->setData(reportModel->index(rows_display, 0), Cash);
                reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
                reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

                QString Amt;
                if(FlowBuff->CDC_given.FunN & 0x40 || FlowBuff->CDC_given.FunN & 0x80)
                {
                    Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_given.GivenData[i].FAmt, 5, 2));
                }
                else
                {
                    Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_given.GivenData[i].FAmt, 5, 2));
                }
                //Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_given.GivenData[i].FAmt, 5, 2));
                reportModel->setData(reportModel->index(rows_display, 3), Amt);
                reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
                reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));
            }

            datalen += sizeof(FlowBuff->CDC_given);
        }

        if(id == LOCKLOG)
        {
            qDebug() << "--->LOCKLOG";
            datalen += sizeof(FlowBuff->CDC_lock);
        }

        if(id == DISCADDLOG)
        {
            qDebug() << "--->DISCADDLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Discount;
            if(FlowBuff->CDC_discadd.FunN & 0x80)
            {
                Discount = QString("Discount");
            }
            else
            {
                Discount = QString("Increase");
            }
            //QString Discount("Discount");
            reportModel->setData(reportModel->index(rows_display, 0), Discount);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Qty;
            if(FlowBuff->CDC_discadd.FunN & 0x80)
            {
                Qty.sprintf("-%.02f%%", comm::BcdToFloat((char *)FlowBuff->CDC_discadd.Percent, 2, 2));
            }
            else
            {
                Qty.sprintf("+%.02f%%", comm::BcdToFloat((char *)FlowBuff->CDC_discadd.Percent, 2, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 2), Qty);
            reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_discadd.FunN & 0x80)
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_discadd.FAmt, 5, 2));
            }
            else
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_discadd.FAmt, 5, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_discadd);
        }

        if(id == SUBDISCADDLOG)
        {
            qDebug() << "--->SUBDISCADDLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Discount;
            if(FlowBuff->CDC_subdiscadd.FunN & 0x80)
            {
                Discount = QString("Subtotal%Discount");
            }
            else
            {
                Discount = QString("Subtotal%Increase");
            }
            //QString Discount("Subtotal%Discount");
            reportModel->setData(reportModel->index(rows_display, 0), Discount);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Qty;
            if(FlowBuff->CDC_subdiscadd.FunN & 0x80)
            {
                Qty.sprintf("-%.02f%%", comm::BcdToFloat((char *)FlowBuff->CDC_subdiscadd.Percent, 2, 2));
            }
            else
            {
                Qty.sprintf("+%.02f%%", comm::BcdToFloat((char *)FlowBuff->CDC_subdiscadd.Percent, 2, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 2), Qty);
            reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_subdiscadd.FunN & 0x80)
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_subdiscadd.FAmt, 5, 2));
            }
            else
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_subdiscadd.FAmt, 5, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_subdiscadd);
        }

        if(id == DIRECTLOG)
        {
            qDebug() << "--->DIRECTLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Discount;
            if(FlowBuff->CDC_direct.FunN & 0x80)
            {
                Discount = QString("Net Discount");
            }
            else
            {
                Discount = QString("Net Increase");
            }
            reportModel->setData(reportModel->index(rows_display, 0), Discount);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_direct.FunN & 0x80)
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_direct.FAmt, 5, 2));
            }
            else
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_direct.FAmt, 5, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_direct);
        }

        if(id == SUBDIRECTLOG)
        {
            qDebug() << "--->SUBDIRECTLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Discount;
            if(FlowBuff->CDC_subdirect.FunN & 0x80)
            {
                Discount = QString("Subtotal Net Discount");
            }
            else
            {
                Discount = QString("Subtotal Net Increase");
            }
            reportModel->setData(reportModel->index(rows_display, 0), Discount);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_subdirect.FunN & 0x80)
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_subdirect.FAmt, 5, 2));
            }
            else
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_subdirect.FAmt, 5, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_subdirect);
        }

        if(id == SUBTOTALLOG)
        {
            qDebug() << "--->SUBTOTALLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Subtotal("Subtotal");
            reportModel->setData(reportModel->index(rows_display, 0), Subtotal);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_subtotal.FunN & 0x80)
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_subtotal.FAmt, 5, 2));
            }
            else
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_subtotal.FAmt, 5, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            int year, month, day, hour, min;
            year = 2000 + comm::OneBCDToInt(FlowBuff->CDC_subtotal.FYear);
            month = comm::OneBCDToInt(FlowBuff->CDC_subtotal.FMonth);
            day = comm::OneBCDToInt(FlowBuff->CDC_subtotal.FDay);
            hour = comm::OneBCDToInt(FlowBuff->CDC_subtotal.FHour);
            min = comm::OneBCDToInt(FlowBuff->CDC_subtotal.FMinute);
            QString DateTime = QString("%1-%2-%3 %4:%5").arg(year).arg(month).arg(day)
                    .arg(hour).arg(min);
            reportModel->setData(reportModel->index(rows_display, 4), DateTime);
            reportModel->item(rows_display, 4)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 4)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_subtotal);
        }

        if(id == SLIPENDLOG)
        {
            qDebug() << "--->SLIPENDLOG";
            datalen += sizeof(FlowBuff->CDC_slipend);
        }

        if(id == INSERTICLOG)
        {
            qDebug() << "--->INSERTICLOG";
            datalen += sizeof(FlowBuff->CDC_enteric);
        }

        if(id == REFRESHICLOG)
        {
            qDebug() << "--->REFRESHICLOG";
            datalen += sizeof(FlowBuff->CDC_refreshic);
        }

        if(id == PRICELISTLOG)
        {
            qDebug() << "--->PRICELISTLOG";
            datalen += sizeof(FlowBuff->CDC_pricelist);
        }

        if(id == ECRNOLOG)
        {
            qDebug() << "--->ECRNOLOG";
            datalen += sizeof(FlowBuff->CDC_EcrNum);
        }

        if(id == TVOIDLOG)
        {
            qDebug() << "--->TVOIDLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString Cancel("Cancel");
            reportModel->setData(reportModel->index(rows_display, 0), Cancel);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString Amt;
            if(FlowBuff->CDC_Void.FunN & 0x40 || FlowBuff->CDC_Void.FunN & 0x80)
            {
                Amt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_Void.FAmt, 5, 2));
            }
            else
            {
                Amt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_Void.FAmt, 5, 2));
            }
            reportModel->setData(reportModel->index(rows_display, 3), Amt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            int year, month, day, hour, min;
            year = 2000 + comm::OneBCDToInt(FlowBuff->CDC_Void.FYear);
            month = comm::OneBCDToInt(FlowBuff->CDC_Void.FMonth);
            day = comm::OneBCDToInt(FlowBuff->CDC_Void.FDay);
            hour = comm::OneBCDToInt(FlowBuff->CDC_Void.FHour);
            min = comm::OneBCDToInt(FlowBuff->CDC_Void.FMinute);
            QString DateTime = QString("%1-%2-%3 %4:%5").arg(year).arg(month).arg(day)
                    .arg(hour).arg(min);
            reportModel->setData(reportModel->index(rows_display, 4), DateTime);
            reportModel->item(rows_display, 4)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 4)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_Void);
        }

        if(id == PBCLOSELOG)
        {
            qDebug() << "--->PBCLOSELOG";
            datalen += sizeof(FlowBuff->CDC_PbClose);
        }

        if(id == PBOPENLOG)
        {
            qDebug() << "--->PBOPENLOG";
            datalen += sizeof(FlowBuff->CDC_PbOpen);
        }

        if(id == TRTABLELOG)
        {
            qDebug() << "--->TRTABLELOG";
            datalen += sizeof(FlowBuff->CDC_PbTt);
        }

        if(id == PORALOG)
        {
            qDebug() << "--->PORALOG";
            datalen += sizeof(FlowBuff->CDC_PoRa);
        }

        if(id == NETIDLOG)
        {
            qDebug() << "--->NETIDLOG";
            datalen += sizeof(FlowBuff->CDC_NetID);
        }

        if(id == TAXLOG)
        {
            qDebug() << "--->TAXLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString TaxName;
            TaxName.sprintf("%s-%.02f%%", FlowBuff->CDC_Tax.Name, comm::BcdToFloat((char *)FlowBuff->CDC_Tax.FRate, 3, 2));
            reportModel->setData(reportModel->index(rows_display, 0), TaxName);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString NetAmt;
            NetAmt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_Tax.FAmt, 5, 2));
            reportModel->setData(reportModel->index(rows_display, 2), NetAmt);
            reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString TaxAmt;
            TaxAmt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_Tax.FTax, 5, 2));
            reportModel->setData(reportModel->index(rows_display, 3), TaxAmt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_Tax);
        }

        if(id == VATLOG)
        {
            qDebug() << "--->VATLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString TaxName("VAT EXEMPT");
            reportModel->setData(reportModel->index(rows_display, 0), TaxName);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString NetAmt;
            NetAmt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_Vat.FAmt, 5, 2));
            reportModel->setData(reportModel->index(rows_display, 2), NetAmt);
            reportModel->item(rows_display, 2)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 2)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString TaxAmt;
            TaxAmt.sprintf("-%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_Vat.FTax, 5, 2));
            reportModel->setData(reportModel->index(rows_display, 3), TaxAmt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_Vat);
        }

        if(id == ZEROLOG)
        {
            qDebug() << "--->ZEROLOG";

            rows_display = reportModel->rowCount();
            reportModel->insertRow(rows_display);

            QString TaxName("ZERO RATED SALES");
            reportModel->setData(reportModel->index(rows_display, 0), TaxName);
            reportModel->item(rows_display, 0)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 0)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            QString NetAmt;
            NetAmt.sprintf("%.02f", comm::BcdToFloat((char *)FlowBuff->CDC_Zero.FAmt, 5, 2));
            reportModel->setData(reportModel->index(rows_display, 3), NetAmt);
            reportModel->item(rows_display, 3)->setTextAlignment(Qt::AlignCenter);
            reportModel->item(rows_display, 3)->setForeground(QBrush(QColor(0x57, 0xfa, 0xff)));

            datalen += sizeof(FlowBuff->CDC_Zero);
        }
    }

    return strlen;
}

void receipttotxtbuf(char *txtbuf, char *PrBuffer2, int datasize)
{
    int i, k, datalen;

    int j, m, n;
    unsigned char numchar;

    unsigned char flag;
    unsigned char pribuf[64];

    unsigned char databuf[64];
    unsigned char tmpdata1, tmpdata2;

    datalen = datasize;

    qDebug() << "receipttotxtbuf--->datalen = " << datalen;

    k = 0;
    flag = PrBuffer2[0];
    for(i = 1; i < datalen; i++)
    {
        if(PrBuffer2[i] != '\n')
        {
            databuf[k++] = PrBuffer2[i];
        }
        else
        {
            databuf[k] = '\0';
            m = strlen((char *)databuf);
            j = 0;
            for(n = 0; n < m; n++)
            {
                tmpdata1 = databuf[n] & 0xff;
                tmpdata2 = databuf[n + 1] & 0xff;
                //qDebug("tmpdata1 = %02x, tmpdata2 = %02x", tmpdata1, tmpdata2);
                //if(tmpdata1 == 0xf8 && tmpdata2 == 0xd0)//进纸
                if(tmpdata1 == 0x38 && tmpdata2 == 0xd8)//进纸
                {
                    //pribuf[j++] = databuf[n];
                    //pribuf[j++] = databuf[n + 1];
                    //pribuf[j++] = '\n';
                    //break;
                    qDebug() << "to skip";
                    goto skip;
                }
                else if(databuf[n] & 0x80)
                {
                    numchar = databuf[n] & 0x7f;
                    while(numchar)
                    {
                        pribuf[j++] = databuf[n - 1];
                        numchar = (numchar - 1) & 0xff;
                    }
                }
                else
                {
                    pribuf[j++] = databuf[n];
                }
            }
            pribuf[j] = '\0';

            strcpy(txtbuf + strlen(txtbuf), (char *)pribuf);

            skip:
            txtbuf[strlen(txtbuf)] = '\n';
            //qDebug("%s", pribuf);

            k = 0;
            i++;//跳过回车符
            flag = PrBuffer2[i];
        }
    }
}

void flowbill::DataCreate(char *buf, QStandardItemModel *reportModel, QDateTime ejTimeFrom, QDateTime ejTimeTo)
{
    int ret;
    int strlen;
    char txtdatabuf[1024 * 100];
    memset(&ejdata, 0, sizeof(ejdata));
    ejdata.Indx = 1;
    strcpy(ejdata.IP, IPStr.toLocal8Bit().data());

    strlen = 0;
    MyEJ->setejTimeFrom(ejTimeFrom);
    MyEJ->setejTimeTo(ejTimeTo);
    while(1)
    {
        ret = MyEJ->selecttable(QString("EJ"), &ejdata, ejTimeFrom, ejTimeTo);
        if(ret < 0)
        {
            break;
        }

        if(ret > 0)
        {
            //strlen = EjDataTrans(ejdata.blobbuf, ejdata.datalen, buf + strlen);
#ifndef ReceiptLOG
            strlen = EjDataTrans((char *)&ejdata, ejdata.datalen, reportModel);
#else
            memset(txtdatabuf, 0, sizeof(txtdatabuf));
            receipttotxtbuf(txtdatabuf, ejdata.blobbuf + 3, ejdata.datalen - 3);
            emit ejdataok(txtdatabuf);
#endif
            QCoreApplication::processEvents();
        }

        ejdata.Indx++;
    }

//    qDebug("buf---->\n%s", buf);
}

void debugreceipt(char *PrBuffer2)
{
    int i, k, datalen;

    int j, m, n;
    unsigned char numchar;

    unsigned char flag;
    unsigned char pribuf[64];

    unsigned char databuf[64];

    datalen = strlen(PrBuffer2);

    qDebug() << "debugreceipt--->datalen = " << datalen;

    k = 0;
    flag = PrBuffer2[0];
    for(i = 1; i < datalen; i++)
    {
        if(PrBuffer2[i] != '\n')
        {
            databuf[k++] = PrBuffer2[i];
        }
        else
        {
            databuf[k] = '\0';
            m = strlen((char *)databuf);
            j = 0;
            for(n = 0; n < m; n++)
            {
                if(databuf[n] == 0xf8 && databuf[n + 1] == 0xd0)//进纸
                {
                    //pribuf[j++] = databuf[n];
                    //pribuf[j++] = databuf[n + 1];
                    pribuf[j++] = '\n';
                    break;
                }
                else if(databuf[n] & 0x80)
                {
                    numchar = databuf[n] & 0x7f;
                    while(numchar)
                    {
                        pribuf[j++] = databuf[n - 1];
                        numchar = (numchar - 1) & 0xff;
                    }
                }
                else
                {
                    pribuf[j++] = databuf[n];
                }
            }
            pribuf[j] = '\0';

            qDebug("%s", pribuf);

            k = 0;
            i++;//跳过回车符
            flag = PrBuffer2[i];
        }
    }
}

void flowbill::DataParse(char *buf)
{
    BYTE id;
    char tmpbuf[2048];
    FlowBuff = (union  FLOWREC *)buf;

    id = FlowBuff->CDC_dpt.FunN & 0x1f;

    if(id == REGISLOG)
    {
        qDebug() << "--->REGISLOG"; //一张票据开始
        qDebug() << "FlowBuff->CDC_regis.EcrNumber = " << FlowBuff->CDC_regis.EcrNumber;
        qDebug("FlowBuff->CDC_regis.OperNo = %02x", FlowBuff->CDC_regis.OperNo);
        qDebug("FlowBuff->CDC_regis.FYear = %02x", FlowBuff->CDC_regis.FYear);
        qDebug("FlowBuff->CDC_regis.FMonth = %02x", FlowBuff->CDC_regis.FMonth);
        qDebug("FlowBuff->CDC_regis.FDay = %02x", FlowBuff->CDC_regis.FDay);
        qDebug("FlowBuff->CDC_regis.FHour = %02x", FlowBuff->CDC_regis.FHour);
        qDebug("FlowBuff->CDC_regis.FMinute = %02x", FlowBuff->CDC_regis.FMinute);
        qDebug("FlowBuff->CDC_regis.FSecond = %02x", FlowBuff->CDC_regis.FSecond);

        memset(&ejdata, 0, sizeof(ejdata));

        int year, month, day, hour, min, sec;
        year = 2000 + comm::OneBCDToInt(FlowBuff->CDC_regis.FYear);
        month = comm::OneBCDToInt(FlowBuff->CDC_regis.FMonth);
        day = comm::OneBCDToInt(FlowBuff->CDC_regis.FDay);
        hour = comm::OneBCDToInt(FlowBuff->CDC_regis.FHour);
        min = comm::OneBCDToInt(FlowBuff->CDC_regis.FMinute);
        sec = comm::OneBCDToInt(FlowBuff->CDC_regis.FSecond);
#if 0
        QString DateTime = QString("%1-%2-%3 %5:%6:%7").arg(year).arg(month).arg(day)
                .arg(hour).arg(min).arg(sec);
#else
        QString DateTime;
        DateTime.sprintf("%d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, min, sec);
#endif

        qDebug() << "--->DateTime = " << DateTime;

        MyEJ->setejtime(DateTime);

        strcpy(ejdata.IP, IPStr.toLocal8Bit().data());

#ifndef ReceiptLOG
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_regis, sizeof(FlowBuff->CDC_regis));
        ejdata.datalen += sizeof(FlowBuff->CDC_regis);
#endif

        ejlog = true;
    }

    if(ejlog == false) //没有接收到REGISLOG
    {
        return;
    }

    if(id == RESERVERLOG)
    {
        qDebug() << "--->RESERVERLOG";
    }

    if(id == DEPTLOG)
    {
        qDebug() << "--->DEPTLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_dpt, sizeof(FlowBuff->CDC_dpt));
        ejdata.datalen += sizeof(FlowBuff->CDC_dpt);
    }

    if(id == PLULOG)
    {
        qDebug() << "--->PLULOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_art, sizeof(FlowBuff->CDC_art));
        ejdata.datalen += sizeof(FlowBuff->CDC_art);
    }

    if(id == ENDLOG)
    {
        qDebug() << "--->ENDLOG";
        ejdata.Indx = comm::BCDToInt(FlowBuff->CDC_end.ReceiptNum, RECEIPTLEN);

        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_end, sizeof(FlowBuff->CDC_end));
        ejdata.datalen += sizeof(FlowBuff->CDC_end);
    }

    if(id == NOADDLOG)
    {
        qDebug() << "--->NOADDLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_noadd, sizeof(FlowBuff->CDC_noadd));
        ejdata.datalen += sizeof(FlowBuff->CDC_noadd);
    }

    if(id == OPERLOG)
    {
        qDebug() << "--->OPERLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_oper, sizeof(FlowBuff->CDC_oper));
        ejdata.datalen += sizeof(FlowBuff->CDC_oper);
    }

    if(id == TENDLOG)
    {
        qDebug() << "--->TENDLOG"; //一张票据结束，写入数据库
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_given, sizeof(FlowBuff->CDC_given));
        ejdata.datalen += sizeof(FlowBuff->CDC_given);
        MyEJ->inserttable(QString("EJ"), ejdata);

        ejlog = false;
    }

    if(id == RECEIPTLOG)
    {
        qDebug() << "--->RECEIPTLOG"; //整张票据文本，写入数据库
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_Receipt, 3 + FlowBuff->CDC_Receipt.DataLen);
        ejdata.datalen += (3 + FlowBuff->CDC_Receipt.DataLen);
        MyEJ->inserttable(QString("EJ"), ejdata);

        memcpy(tmpbuf, &FlowBuff->CDC_Receipt, 3 + FlowBuff->CDC_Receipt.DataLen);
        debugreceipt(tmpbuf + 3);

        ejlog = false;
    }

    if(id == LOCKLOG)
    {
        qDebug() << "--->LOCKLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_lock, sizeof(FlowBuff->CDC_lock));
        ejdata.datalen += sizeof(FlowBuff->CDC_lock);
    }

    if(id == DISCADDLOG)
    {
        qDebug() << "--->DISCADDLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_discadd, sizeof(FlowBuff->CDC_discadd));
        ejdata.datalen += sizeof(FlowBuff->CDC_discadd);
    }

    if(id == SUBDISCADDLOG)
    {
        qDebug() << "--->SUBDISCADDLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_subdiscadd, sizeof(FlowBuff->CDC_subdiscadd));
        ejdata.datalen += sizeof(FlowBuff->CDC_subdiscadd);
    }

    if(id == DIRECTLOG)
    {
        qDebug() << "--->DIRECTLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_direct, sizeof(FlowBuff->CDC_direct));
        ejdata.datalen += sizeof(FlowBuff->CDC_direct);
    }

    if(id == SUBDIRECTLOG)
    {
        qDebug() << "--->SUBDIRECTLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_subdirect, sizeof(FlowBuff->CDC_subdirect));
        ejdata.datalen += sizeof(FlowBuff->CDC_subdirect);
    }

    if(id == SUBTOTALLOG)
    {
        qDebug() << "--->SUBTOTALLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_subtotal, sizeof(FlowBuff->CDC_subtotal));
        ejdata.datalen += sizeof(FlowBuff->CDC_subtotal);
    }

    if(id == SLIPENDLOG)
    {
        qDebug() << "--->SLIPENDLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_slipend, sizeof(FlowBuff->CDC_slipend));
        ejdata.datalen += sizeof(FlowBuff->CDC_slipend);
    }

    if(id == INSERTICLOG)
    {
        qDebug() << "--->INSERTICLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_enteric, sizeof(FlowBuff->CDC_enteric));
        ejdata.datalen += sizeof(FlowBuff->CDC_enteric);
    }

    if(id == REFRESHICLOG)
    {
        qDebug() << "--->REFRESHICLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_refreshic, sizeof(FlowBuff->CDC_refreshic));
        ejdata.datalen += sizeof(FlowBuff->CDC_refreshic);
    }

    if(id == PRICELISTLOG)
    {
        qDebug() << "--->PRICELISTLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_pricelist, sizeof(FlowBuff->CDC_pricelist));
        ejdata.datalen += sizeof(FlowBuff->CDC_pricelist);
    }

    if(id == ECRNOLOG)
    {
        qDebug() << "--->ECRNOLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_EcrNum, sizeof(FlowBuff->CDC_EcrNum));
        ejdata.datalen += sizeof(FlowBuff->CDC_EcrNum);
    }

    if(id == TVOIDLOG)
    {
        qDebug() << "--->TVOIDLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_Void, sizeof(FlowBuff->CDC_Void));
        ejdata.datalen += sizeof(FlowBuff->CDC_Void);
    }

    if(id == PBCLOSELOG)
    {
        qDebug() << "--->PBCLOSELOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_PbClose, sizeof(FlowBuff->CDC_PbClose));
        ejdata.datalen += sizeof(FlowBuff->CDC_PbClose);
    }

    if(id == PBOPENLOG)
    {
        qDebug() << "--->PBOPENLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_PbOpen, sizeof(FlowBuff->CDC_PbOpen));
        ejdata.datalen += sizeof(FlowBuff->CDC_PbOpen);
    }

    if(id == TRTABLELOG)
    {
        qDebug() << "--->TRTABLELOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_PbTt, sizeof(FlowBuff->CDC_PbTt));
        ejdata.datalen += sizeof(FlowBuff->CDC_PbTt);
    }

    if(id == PORALOG)
    {
        qDebug() << "--->PORALOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_PoRa, sizeof(FlowBuff->CDC_PoRa));
        ejdata.datalen += sizeof(FlowBuff->CDC_PoRa);
    }

    if(id == NETIDLOG)
    {
        qDebug() << "--->NETIDLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_NetID, sizeof(FlowBuff->CDC_NetID));
        ejdata.datalen += sizeof(FlowBuff->CDC_NetID);
    }

    if(id == TAXLOG)
    {
        qDebug() << "--->TAXLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_Tax, sizeof(FlowBuff->CDC_Tax));
        ejdata.datalen += sizeof(FlowBuff->CDC_Tax);
    }

    if(id == VATLOG)
    {
        qDebug() << "--->VATLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_Vat, sizeof(FlowBuff->CDC_Vat));
        ejdata.datalen += sizeof(FlowBuff->CDC_Vat);
    }

    if(id == ZEROLOG)
    {
        qDebug() << "--->ZEROLOG";
        memcpy(ejdata.blobbuf + ejdata.datalen, &FlowBuff->CDC_Zero, sizeof(FlowBuff->CDC_Zero));
        ejdata.datalen += sizeof(FlowBuff->CDC_Zero);
    }
}
