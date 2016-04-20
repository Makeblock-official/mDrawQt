#ifndef XYROBOT_H
#define XYROBOT_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class XYRobot : public QGraphicsItem
{
public:
    XYRobot(QGraphicsScene *scene=0);
    void initRobotCanvas();
    void setTarget(QPointF p);
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);

private:
    int  p_width;
    int p_height;
    float x;
    float y;
    float last_x;
    float last_y;


    QPoint origin ;
    QPoint robotCent;
    QGraphicsScene * scene;
    QGraphicsRectItem*  pRect;
    QVector<QGraphicsTextItem*>txtPtr;
};

#endif // XYROBOT_H
