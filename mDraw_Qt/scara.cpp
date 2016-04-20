#include "scara.h"
#include <qmath.h>
#include <QDebug>

#define pi 3.1415926
QPointF getDegree(QPointF theta)
{
    QPointF ang(theta.x()/pi*180,theta.y()/pi*180);
    return ang;
}

Scara::Scara(QGraphicsScene* p)
{
    L1=168.0;
    L2=206.0;
    speed=50;
    motorADir=0;
    motorBDir=0;
    scene = p;
    pos = QPointF(-(L1+L2),0.0);

    robotCent = QPoint(scene->width()/2,scene->height()/2+120);
    initRobotCanvas();
}
void Scara::initRobotCanvas()
{
    //    if(pEllipse0!=NULL)
    //    {
    //        scene->removeItem(pEllipse0);
    //        scene->removeItem(pEllipse1);
    //    }
    QPen pen(QColor(124,124,124));
    pen.setStyle(Qt::DashDotLine);
    pEllipse0 = scene->addEllipse(robotCent.x()-L1,robotCent.y()-L1,L1*2,L1*2,pen);
    pen.setStyle(Qt::SolidLine);
    pEllipse1 = scene->addEllipse(robotCent.x()-L1-L2,robotCent.y()-L1-L2,(L1+L2)*2,(L1+L2)*2,pen);
    scene->addText("0");

}

void Scara::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option);  //标明该参数没有使用
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    QVector<QPointF> m = sceraDirectKinect(scaraInverseKinect(pos));

    float x1 = m.at(0).x();
    float x2 = m.at(1).x();
    float y1 = -m.at(0).y();
    float y2 = -m.at(1).y();
    QPointF ang = getDegree(scaraInverseKinect(pos));
    qDebug()<<"askjdf"<<x2<<","<<y2;
    QPen pen(QColor(124,124,124));
    painter->setBrush(Qt::darkGray);
    painter->setPen(pen);

    QLine line0(0,0,x1,y1);
    painter->drawLine(line0);

    QLine line1(x1,y1,x2,y2);
    painter->drawLine(line1);

    painter->drawEllipse(x1-5,y1-5,10,10);
    painter->drawEllipse(x2-5,y2-5,10,10);

    QPen pen_center(QColor(0,169,231));
    painter->setBrush(QColor(0,169,231));
    painter->setPen(pen_center);
    painter->drawEllipse(-5,-5,10,10);

    if((x2!=lastx)||(y2!=lasty))
    {
        lastx = x2;
        lasty = y2;
    }

}
QRectF Scara::boundingRect() const
{
    return  QRectF(0,0,100,100);
}
QPointF Scara::scaraInverseKinect(QPointF p)
{
    float x = p.x();
    float y = p.y();

    float thx = 2*atan((2*L1*y + sqrt(- L1*L1*L1*L1 + 2*L1*L1*L2*L2 + 2*L1*L1*x*x + 2*L1*L1*y*y - L2*L2*L2*L2 + 2*L2*L2*x*x + 2*L2*L2*y*y - x*x*x*x - 2*x*x*y*y - y*y*y*y))/(L1*L1 - 2*L1*x - L2*L2 + x*x + y*y));
    float thy = 2*atan(sqrt((- L1*L1 + 2*L1*L2 - L2*L2 + x*x + y*y)*(L1*L1 + 2*L1*L2 + L2*L2 - x*x - y*y))/(L1*L1 + 2*L1*L2 + L2*L2 - x*x - y*y));
    QPointF th(thx,thy);
    return th;
}
QVector<QPointF> Scara::sceraDirectKinect(QPointF th)
{
    float th1 = th.x();
    float th2 = th.y();

    float x1 = -L1*cos(th1);
    float y1 = L1*sin(th1);
    float x2 = -L1*cos(th1)-L2*cos(th1+th2-pi);
    float y2 = L1*sin(th1)+L2*sin(th1+th2-pi);
    QVector<QPointF> m;
    qDebug()<<th1<<"d"<<th2;
    m.append(QPointF(x1,y1));
    m.append(QPointF(x2,y2));
    return m;
}
