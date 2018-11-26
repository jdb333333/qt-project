#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

/**
 * ����:feiyangqingyun(QQ:517216493) 2016-11-6
 * 1:�����ÿ��ذ�ť����ʽ Բ�Ǿ���/��Բ��/��Բ��/ͼƬ
 * 2:������ѡ�к�δѡ��ʱ�ı�����ɫ
 * 3:������ѡ�к�δѡ��ʱ�Ļ�����ɫ
 * 4:��������ʾ���ı�
 * 5:�����û����뱳���ļ��
 * 6:������Բ�ǽǶ�
 */

#include <QWidget>

class QTimer;

class SwitchButton: public QWidget
{
    Q_OBJECT
public:
    enum ButtonStyle {
        ButtonStyle_Rect = 0,     //Բ�Ǿ���
        ButtonStyle_CircleIn = 1, //��Բ��
        ButtonStyle_CircleOut = 2,//��Բ��
        ButtonStyle_Image = 3     //ͼƬ
    };

    SwitchButton(QWidget *parent = 0);
    ~SwitchButton();

protected:
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawSlider(QPainter *painter);
    void drawText(QPainter *painter);
    void drawImage(QPainter *painter);

private:
    bool checked;               //�Ƿ�ѡ��
    ButtonStyle buttonStyle;    //���ذ�ť��ʽ

    QColor bgColorOff;          //�ر�ʱ������ɫ
    QColor bgColorOn;           //��ʱ������ɫ

    QColor sliderColorOff;      //�ر�ʱ������ɫ
    QColor sliderColorOn;       //��ʱ������ɫ

    QColor textColorOff;        //�ر�ʱ�ı���ɫ
    QColor textColorOn;         //��ʱ�ı���ɫ

    QString textOff;            //�ر�ʱ��ʾ������
    QString textOn;             //��ʱ��ʾ������

    QString imageOff;           //�ر�ʱ��ʾ��ͼƬ
    QString imageOn;            //��ʱ��ʾ��ͼƬ

    int space;                  //�����뱳�����
    int rectRadius;             //Բ�ǽǶ�

    int step;                   //ÿ���ƶ��Ĳ���
    int startX;                 //���鿪ʼX������
    int endX;                   //�������X������
    QTimer *timer;              //��ʱ������

private slots:
    void updateValue();

public:
    bool getChecked()const
    {
        return checked;
    }
    ButtonStyle getButtonStyle()const
    {
        return buttonStyle;
    }

    QColor getBgColorOff()const
    {
        return bgColorOff;
    }
    QColor getBgColorOn()const
    {
        return bgColorOn;
    }

    QColor getSliderColorOff()const
    {
        return sliderColorOff;
    }
    QColor getSliderColorOn()const
    {
        return sliderColorOn;
    }

    QColor getTextColorOff()const
    {
        return textColorOff;
    }
    QColor getTextColorOn()const
    {
        return textColorOn;
    }

    QString getTextOff()const
    {
        return textOff;
    }
    QString getTextOn()const
    {
        return textOn;
    }

    QString getImageOff()const
    {
        return imageOff;
    }
    QString getImageOn()const
    {
        return imageOn;
    }

    int getSpace()const
    {
        return space;
    }
    int getRectRadius()const
    {
        return rectRadius;
    }

public slots:
    //�����Ƿ�ѡ��
    void setChecked(bool checked);
    //���÷����ʽ
    void setButtonStyle(ButtonStyle buttonStyle);

    //���ñ�����ɫ
    void setBgColor(QColor bgColorOff, QColor bgColorOn);
    //���û�����ɫ
    void setSliderColor(QColor sliderColorOff, QColor sliderColorOn);
    //�����ı���ɫ
    void setTextColor(QColor textColorOff, QColor textColorOn);

    //�����ı�
    void setText(QString textOff, QString textOn);

    //���ñ���ͼƬ
    void setImage(QString imageOff, QString imageOn);

    //���ü��
    void setSpace(int space);
    //����Բ�ǽǶ�
    void setRectRadius(int rectRadius);

signals:
    void checkedChanged(bool checked);
};

#endif // SWITCHBUTTON_H
