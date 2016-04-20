#include "robotscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGLWidget>
#include <qgl.h>

#include <QDebug>

robotScene::robotScene(QObject *parent,newmdRAW* pp) :
    QGraphicsScene(parent)
{
    pMain = pp;
    pModel = new GModel();
    pDrawModel = new GModel();
    panTarget = QVector3D(0,0,0);
    pan = QVector3D(0,0,0);//set pan to center of build area.

    pDrawTimer = new QTimer();
    connect(pDrawTimer, SIGNAL(timeout()), this, SLOT(UpdateTick()));
    pDrawTimer->start(16.66);//aim for 60fps.

    pDrawGcode = new QTimer();
    connect(pDrawGcode, SIGNAL(timeout()), this, SLOT(Slot_RenderChange()));

    currentIsland = 0;
    currentLine = 0;
    bAnimate = false;

}
robotScene:: ~robotScene()
{

}
//void robotScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{

//}
//void robotScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{

//}
//void robotScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
//{
//    //    QPointF pos = event->scenePos();
//    //    emit Sig_pos(pos);
//}
void robotScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    mouseLastPos = event->scenePos();
    const QPointF delta = event->scenePos() - event->lastScenePos();
    mouseDeltaPos.setX(delta.x());
    mouseDeltaPos.setY(delta.y());

    panTarget += QVector3D(mouseDeltaPos.x()/5.0,mouseDeltaPos.y()/5.0,0);
    event->accept();
    QGraphicsScene::mouseMoveEvent(event);
}

void robotScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRectF m = rect;
    qDebug()<<m.height();
    if (painter->paintEngine()->type()!= QPaintEngine::OpenGL2)
    {
        qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }
    initialGL();
    paintGL();

}
void robotScene::initialGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.9531, 0.9531, 0.9531, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glLineWidth(0.5);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glEnable (GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


    //    glDisable(GL_MULTISAMPLE);
    glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void robotScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    double nearClip;
    //perpective/ortho/xray stuff!
    glMatrixMode(GL_PROJECTION);
    glDisable(GL_LIGHTING);
    glLoadIdentity();//restores default matrix.
    nearClip = 1;
    gluPerspective(30,double(width())/height(),nearClip,5500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //    pan = pan + (panTarget - pan)/2.0;
    glTranslatef(0.0, 0.0, -350);//step back amount
    glTranslatef(pan.x(),-pan.y(),0);

    glRotatef(180, 1.0, 0.0, 0.0);
    //    glRotatef(180, 0.0, 0.0, 1.0);
    if(bAnimate)
    {
        DrawAGcode();
    }
    else
    {
        DrawGcode();
    }

}

void robotScene::DrawAGcode()
{
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.1f,0.43f,0.93f);
    glLineWidth(1);
    if(pDrawModel->m_parts.size()==0)
    {
        glBegin(GL_LINE_STRIP);
        for(int i = 0;i<pIsland.island.size()-1;i++)
        {
            QVector3D sm = (pIsland.island.at(i)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
            glVertex3f(sm.x(),sm.y(),sm.z());
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        QVector3D s1 = (pIsland.island.at(pIsland.island.size()-2)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
        glVertex3f(s1.x(),s1.y(),s1.z());
        glVertex3f(s1.x()+0.1,s1.y()+0.1,s1.z()+0.1);
        glEnd();
    }
    else
    {
        for(int j = 0;j<pDrawModel->m_parts.size();j++)
        {
            partIsland rends = pDrawModel->m_parts.at(j);

//            if(rends.island.size()>2)
            {
                 glBegin(GL_LINE_STRIP);
                for(int i = 0;i<rends.island.size()-1;i++)
                {
                    QVector3D s = (rends.island.at(i)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
                    glVertex3f(s.x(),s.y(),s.z());
                }
                glEnd();
                glBegin(GL_LINE_STRIP);
                QVector3D s1 = (rends.island.at(0)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
                QVector3D s2 = (rends.island.at(rends.island.size()-2)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
                glVertex3f(s1.x(),s1.y(),s1.z());
                glVertex3f(s2.x(),s2.y(),s2.z());
                glEnd();
            }
        }

        glBegin(GL_LINE_STRIP);
        for(int n = 0;n<pIsland.island.size()-1;n++)
        {
            QVector3D sx = (pIsland.island.at(n)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
            glVertex3f(sx.x(),sx.y(),sx.z());
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        QVector3D sd = (pIsland.island.at(pIsland.island.size()-2)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
        glVertex3f(sd.x(),sd.y(),sd.z());
        glVertex3f(sd.x()+0.1,sd.y()+0.1,sd.z()+0.1);
        glEnd();
    }

    glPopMatrix();
}

void robotScene::DrawGcode()
{
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.1f,0.43f,0.93f);
    glLineWidth(1);

    for(int j = 0;j<pModel->m_parts.size();j++)
    {
        glBegin(GL_LINE_STRIP);
        partIsland rends = pModel->m_parts.at(j);
        for(int i = 0;i<rends.island.size();i++)
        {
            QVector3D s = (rends.island.at(i)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
            glVertex3f(s.x(),s.y(),s.z());
        }
        glEnd();
        glBegin(GL_LINE_STRIP);
        QVector3D s1 = (rends.island.at(0)-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
        QVector3D s2 = (rends.island.last()-(pModel->outMin+pModel->bounds*0.5))*(pModel->scale);
        glVertex3f(s1.x(),s1.y(),s1.z());
        glVertex3f(s2.x(),s2.y(),s2.z());
        glEnd();
    }
    DrawAxis();
    glPopMatrix();
}
//void robotScene::DrawLine(QPoint a,QPoint b)
//{
//     glBegin(GL_LINE_STRIP);
//     glVertex3f(a.x(),a.y(),0);
//     glVertex3f(b.x(),b.y(),0);
//     glEnd();
//}
void robotScene::DrawAxis()
{
    //    glBegin(GL_LINE_STRIP);
    //    glVertex3f(0,-10,0);
    //    glVertex3f(180,-10,0);
    //    glEnd();
    //    for(int i=0;i<180;i++)
    //    {
    //        if(i/5==0)
    //        {
    //            glBegin(GL_LINE_STRIP);
    //            glVertex3f(i,10,0);
    //            glVertex3f(i,-10,0);
    //            glEnd();
    //        }
    //    }
}
void robotScene::UpdateTick()
{
    pan = pan + (panTarget - pan)/2.0;
    update();
}
//animate the gcode
void robotScene::Slot_RenderChange()
{
    currentLine++;
    pIsland.island.append(pModel->m_parts.at(currentIsland).island.at(currentLine));
    if(currentLine>=pModel->m_parts.at(currentIsland).island.size())
    {
        currentIsland++;
        partIsland po = pIsland;
        pDrawModel->m_parts.append(po);
        pIsland.island.clear();
        if(currentIsland>=pModel->m_parts.size())
        {
            currentLine = 0;
            currentIsland = 0;
            pDrawGcode->stop();
            pDrawModel->m_parts.clear();
            bAnimate = false;
            emit Sig_DrawFinish();
        }
        else
        {
            currentLine = 0;
        }
    }
    qDebug()<<tr("current index = %1").arg(pDrawModel->m_parts.size());
    update();
}
void robotScene::StartDraw()
{
    bAnimate = true;
    pDrawGcode->start(20);
}
void robotScene::StopDraw()
{
    pDrawGcode->stop();
}
void robotScene::CancleDraw()
{
    bAnimate = false;
    pDrawGcode->stop();
    currentIsland = 0;
    currentLine = 0;
    pDrawModel->m_parts.clear();
}
