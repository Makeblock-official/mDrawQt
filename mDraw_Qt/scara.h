#ifndef SCARA_H
#define SCARA_H

#include <QGraphicsItem>
#include<QGraphicsScene>
#include<QPainter>

class Scara : public QGraphicsItem
{
public:
    Scara(QGraphicsScene* p=0);
    void initRobotCanvas();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
private:
    float L1;
    float L2;
    int motorADir;
    int motorBDir;
    int speed;
    int lastx;
    int lasty;
    QGraphicsEllipseItem* pEllipse0;
    QGraphicsEllipseItem* pEllipse1;
    QGraphicsScene* scene;

    QPoint robotCent;
    QPointF pos;

    //function
    QPointF scaraInverseKinect(QPointF p);
    QVector<QPointF> sceraDirectKinect(QPointF th);
};

#endif // SCARA_H
