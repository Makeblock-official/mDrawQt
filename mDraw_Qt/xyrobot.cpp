#include "xyrobot.h"

XYRobot::XYRobot(QGraphicsScene *p)
{
    scene = p;
    p_width = 380;
    p_height = 310;
    robotCent = QPoint(scene->width()/2,scene->height()/2+120);
    x=10;
    y=-10;
    last_x=0;
    last_y=0;

}

void XYRobot::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(option);  //标明该参数没有使用
    Q_UNUSED(widget);
    painter->setBrush(Qt::darkGray);
    painter->setRenderHint(QPainter::Antialiasing);
    float p_x = x+origin.x()-robotCent.x();
    float p_y = y+origin.y()-robotCent.y()+p_height;

    QPen pen = QPen(QColor(124,124,124));
    painter->setBrush(Qt::darkGray);
    painter->setPen(pen);
    painter->drawLine(p_x,origin.y()-robotCent.y(),p_x,origin.y()-robotCent.y()+p_height);
    painter->drawLine(origin.x()-robotCent.x(),p_y,origin.x()-robotCent.x()+p_width,p_y);
    QPen pen1 =QPen (QColor(0,169,231));
    painter->setBrush(QColor(0,169,231));
    painter->setPen(pen1);
    painter->drawEllipse(-5+p_x,-5+p_y,10,10);
    if((x!=last_x)||y!=last_y)
    {
        last_x = x;
        last_y=y;
    }

}

QRectF XYRobot::boundingRect() const
{
    return  QRectF(0,0,200,200);
}

void XYRobot::initRobotCanvas()
{
    origin = QPoint((scene->width()-p_width)/2,(scene->height()-p_height)/2);
    //check item needed
    if(pRect!=NULL)
    {
        //scene->removeItem(pRect);

    }
    QPen pen(QColor(124,124,124));
    pRect = scene->addRect(origin.x(),origin.y(),p_width,p_height,pen);
    QGraphicsTextItem* pTxt =  scene->addText("0");
    QPoint cent((origin.x()-10),origin.y()+p_height);
    pTxt->setPos(cent);
    pTxt->setDefaultTextColor(QColor(124,124,124));
    txtPtr.append(pTxt);

    QGraphicsTextItem* pTxt1 =  scene->addText("Y");
    cent = QPoint(origin.x()-10,origin.y()-10);
    pTxt1->setPos(cent);
    pTxt1->setDefaultTextColor(QColor(124,124,124));
    txtPtr.append(pTxt1);

    QGraphicsTextItem* pTxt2 =  scene->addText("X");
    cent = QPoint(origin.x()+p_width,origin.y()+p_height);
    pTxt2->setPos(cent);
    pTxt2->setDefaultTextColor(QColor(124,124,124));
    txtPtr.append(pTxt1);
}
void XYRobot::setTarget(QPointF p)
{
    x = p.x()+190;
    y=p.y()-155;
    this->update();}
