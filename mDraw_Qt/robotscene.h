#ifndef ROBOTSCENE_H
#define ROBOTSCENE_H

//#ifdef Q_OS_LINUX
//    #include <GL/gl.h>
//    #include <GL/glu.h>
//#endif
//#ifdef Q_OS_MACX
//    #include <OpenGL/gl.h>
//    #include <OpenGL/glu.h>
//#endif
//#ifdef Q_OS_WIN
//    #include <GL/gl.h>
//    #include <GL/glu.h>
//#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <QGraphicsScene>
#include <QDebug>
#include <QVector2D>
#include <QTimer>
#include "newmdraw.h"
#include "gmodel.h"

class newmdRAW;
class GModel;

class robotScene : public QGraphicsScene
{
    Q_OBJECT
public:
    robotScene(QObject *parent = 0,newmdRAW* pp=0);
    ~robotScene();
    QTimer* pDrawTimer; //refreshes the 3d scene
    QTimer * pDrawGcode;
    GModel* pModel;
    GModel* pDrawModel;
    partIsland pIsland;
    bool bAnimate;
    void StartDraw();
    void StopDraw();
    void CancleDraw();
protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


    void drawBackground(QPainter *painter, const QRectF &rect);
public slots:
    void UpdateTick();//called every 1/60th of a second by update timer. also refreshes the openGL Screen
    void Slot_RenderChange();

signals:
    void Sig_pos(QPointF);
    void Sig_DrawFinish();

private:
    void initialGL();
    void paintGL();
    void DrawGcode();
    void DrawAGcode();
    void DrawAxis();


    QVector3D pan;
    QVector3D panTarget;
    QVector2D mouseDeltaPos;
    QPointF mouseLastPos;

    //anitmate
    int currentIsland;
    int currentLine;



    newmdRAW* pMain;


};

#endif // ROBOTSCENE_H
