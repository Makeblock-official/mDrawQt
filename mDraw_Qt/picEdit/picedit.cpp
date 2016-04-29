#include "picedit.h"
#include "ui_picedit.h"

#include <QRgb>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

const int Bs = 255;
const int Ns = 0;
const int Step1[5][5]={
    {Bs,Bs,Bs,Bs,Bs},
    {Bs,Bs,Bs,Bs,Bs},
    {Bs,Bs,Ns,Bs,Bs},
    {Bs,Bs,Bs,Bs,Bs},
    {Bs,Bs,Bs,Bs,Bs},
};
const int Step2[5][5]={
    {Bs,Bs,Bs,Bs,Bs},
    {Bs,Bs,Ns,Bs,Bs},
    {Bs,Ns,Ns,Ns,Bs},
    {Bs,Bs,Ns,Bs,Bs},
    {Bs,Bs,Bs,Bs,Bs},
};
const int Step3[5][5]={
    {Bs,Bs,Ns,Bs,Bs},
    {Bs,Ns,Ns,Ns,Bs},
    {Ns,Ns,Ns,Ns,Ns},
    {Bs,Ns,Ns,Ns,Bs},
    {Bs,Bs,Ns,Bs,Bs},
};
const int Step4[5][5]={
    {Bs,Ns,Ns,Ns,Bs},
    {Ns,Ns,Ns,Ns,Ns},
    {Ns,Ns,Ns,Ns,Ns},
    {Ns,Ns,Ns,Ns,Ns},
    {Bs,Ns,Ns,Ns,Bs},
};

PicEdit::PicEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicEdit)
{
    ui->setupUi(this);
    preOn = false;
    this->setWindowTitle(tr("GrayScale"));
}

PicEdit::~PicEdit()
{
    delete ui;
}
void PicEdit::GrayScalePicture(int grayscale)
{
    QImage tempImg;  //用于缩放
    tempImg = QImage("temp.png");
    QImage pos_1 = tempImg;                         //拷贝
    QImage show;
    if(tempImg.format()>3)
    {
        qDebug()<<tr("format = %1").arg(tempImg.format());
        QRgb *pixels = (QRgb *)tempImg.scanLine(0);
        QRgb *grays = (QRgb *)pos_1.scanLine(0);
        QRgb thread = qRgb(grayscale,grayscale,grayscale);
        QRgb threadw = qRgb(255,255,255);
        QRgb threadb = qRgb(0,0,0);

        for(int y =0;y<tempImg.height();y++)
        {
            for(int x=0;x<tempImg.width();x++)
            {
                if(pixels[x+y*(tempImg.width())]>thread)
                    grays[x+y*(tempImg.width())] = threadw;
                else
                    grays[x+y*(tempImg.width())] = threadb;
            }
        }
        show = pos_1;
    }
    else
    {
        show = tempImg;
    }

    //    ui->pixValue->setText(tr("图片大小:%1x%2").arg(pos.width()).arg(pos.height()));
    //    show.save("temp.png","PNG",100);       //变换了灰度值的图
    gray_image = show;
    ui->label->setPixmap(QPixmap::fromImage(show));
}
//begin print
void PicEdit::on_startPrint_clicked()
{
    gray_image.save("print.png","PNG",100);       //变换了灰度值的图
    emit Sig_Print();
}
//slider value change
void PicEdit::on_horizontalSlider_valueChanged(int value)
{
    GrayScalePicture(value);
    ui->label_3->setText(QString::number(value));
}
//load a picture
void PicEdit::LoadPicture(QString file)
{
    QImage image(file);
    image.save("temp.png");
    ui->label->setPixmap(QPixmap::fromImage(image));
}
QImage PicEdit::Image2GrayScale(QImage src)
{
    QImage image = src;

    int depth =4;
    int media = 0;
    int h = image.height();
    int w = image.width();
    QRgb* rgbpixel = (QRgb *)image.scanLine(0);
    for (int ii = 0; ii < image.height()/5; ii++)
    {
        for (int jj = 0; jj < image.width()/5; jj++)
        {
            media = 0;
            for(int n=0;n<5;n++)
            {
                for(int m=0;m<5;m++)
                {
                    QRgb a = rgbpixel[(ii*5+n)*w+(jj*5+m)];
                    int gray = qGray(a);
                    media+=gray;
                }
            }
            media = media/25;
            for(int y=0;y<5;y++)
            {
                for(int x=0;x<5;x++)
                {
                    if((media>250)&&(media<255))
                    {
                        QRgb a = QColor(255, 255, 255).rgba();
                        rgbpixel[(ii*5+y)*w+(jj*5+x)] = a;
                    }
                    else if((media>=190)&&(media<250))
                    {
                        QRgb a = QColor(Step1[y][x], Step1[y][x], Step1[y][x]).rgba();
                        rgbpixel[(ii*5+y)*w+(jj*5+x)] = a;
                    }
                    else if((media>=130)&&(media<190))
                    {
                        QRgb a = QColor(Step2[y][x], Step2[y][x], Step2[y][x]).rgba();
                        rgbpixel[(ii*5+y)*w+(jj*5+x)] = a;
                    }
                    else if((media>=70)&&(media<130))
                    {
                        QRgb a = QColor(Step3[y][x], Step3[y][x], Step3[y][x]).rgba();
                        rgbpixel[(ii*5+y)*w+(jj*5+x)] = a;
                    }
                    else if((media>=10)&&(media<70))
                    {
                        QRgb a = QColor(Step4[y][x], Step4[y][x], Step4[y][x]).rgba();
                        rgbpixel[(ii*5+y)*w+(jj*5+x)] = a;
                    }
                    else if((media>=0)&&(media<10))
                    {
                        QRgb a = QColor(0, 0, 0).rgba();
                        rgbpixel[(ii*5+y)*w+(jj*5+x)] = a;
                    }

                }
            }

        }


    }
    image.save("hi.png","PNG",100);
    return image;
}
void PicEdit::ExportGrayPix(QImage src)
{
    QFile file("out.gcode");
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, tr("提示"), tr("无法创建文件"));
        return ;
    }
    QTextStream out(&file);
    QImage image = src;
    double scale=0.1;
    out<<"G0 X1 Y1 F6000 \n";
    out<<"M4 P0 \n";
    for (int ii = 0; ii < image.height(); ii++)
    {
        uchar* scan = image.scanLine(ii);
        QString p1;
        QString p2;
        if(ii%2==0)
        {
            int depth =4;
            for (int jj = 0; jj < image.width(); jj++)
            {

                QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
                int gray = qGray(*rgbpixel);

                //power off
                if(gray>240)
                {
                    if(preOn)
                    {
                        p1 = "M4 P0 \n";
                        p2 = tr("G0 X%1 Y%2 F6000 \n").arg(jj*scale).arg(ii*scale);
                        out<<p1<<p2;
                        preOn = false; //关闭
                    }
                    else
                    {
                        p2 = tr("G0 X%1 Y%2 \n").arg(jj*scale).arg(ii*scale);
                        out<<p2;
                    }

                }
                else
                {
                    if(!preOn)
                    {
                        p1 = tr("M4 P%1 \n").arg(255-gray);
                        p2 = tr("G1 X%1 Y%2 F4000 \n").arg(jj*scale).arg(ii*scale);
                        preOn = true;
                        out<<p1<<p2;
                    }
                    else
                    {
                        p2 = tr("G1 X%1 Y%2 \n").arg(jj*scale).arg(ii*scale);
                        out<<p2;
                    }


                }


            }
        }
        else
        {
            int depth =4;
            for (int jj = image.width(); jj >0; jj--)
            {

                QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
                int gray = qGray(*rgbpixel);

                //power off
                if(gray>=240)
                {
                    if(preOn)
                    {
                        p1 = "M4 P0 \n";
                        p2 = tr("G0 X%1 Y%2 F6000 \n").arg(jj*scale).arg(ii*scale);
                        out<<p1<<p2;
                        preOn = false; //关闭
                    }
                    else
                    {
                        p2 = tr("G0 X%1 Y%2 \n").arg(jj*scale).arg(ii*scale);
                        out<<p2;
                    }

                }
                else
                {
                    if(!preOn)
                    {
                        p1 = tr("M4 P%1 \n").arg(255-gray);
                        p2 = tr("G1 X%1 Y%2 F4000 \n").arg(jj*scale).arg(ii*scale);
                        preOn = true;
                        out<<p1<<p2;
                    }
                    else
                    {
                        p2 = tr("G1 X%1 Y%2 \n").arg(jj*scale).arg(ii*scale);
                        out<<p2;
                    }


                }


            }
        }

    }
    qDebug()<<"export finish!!";
    file.close();

}


void PicEdit::on_btngray_clicked()
{
    QImage image("temp.png");
//    Image2GrayScale(image);
    ExportGrayPix(Image2GrayScale(image));
    QImage image2("hi.png");
    ui->label->setPixmap(QPixmap::fromImage(image2));
    this->close();
    emit Sig_ShowImage();
}
