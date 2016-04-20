#include "gmodel.h"

#include <QFile>
#include <QTextStream>
#include <QVarLengthArray>

#include <QtOpenGL>
#include <QDebug>
#include <QRegExp>

GModel::GModel()
{
}
void GModel::loadFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    //如下两个变量存放模型的边界
    QVector3D boundsMin( 1e9, 1e9, 1e9);
    QVector3D boundsMax(-1e9,-1e9,-1e9);


    //读取obj格式的文件
    QTextStream in(&file);
    //now begin to read the verters

    QVector3D pi;
    float currentZ = 0.0;
    float currentX = 0.0;
    float currentY = 0.0;
    QRegExp regZ("[\w\d\s]*Z([0-9\.]*[0-9]*)");
    QRegExp regL(";LAYER: *([0-9]*)");
    QRegExp regXY("G1 [\w\d\s]* *X([0-9\.]*[0-9]*) *Y([0-9\.]*[0-9]*)");

    while(!in.atEnd())
    {
        QString current_str = in.readLine();
        partIsland t_island;
        while(!current_str.startsWith("G0"))
        {
            if(current_str.contains(regXY))
            {
                currentX = regXY.cap(1).toFloat();
                currentY = regXY.cap(2).toFloat();
                boundsMin.setX( qMin(boundsMin.x(),currentX));
                boundsMax.setX( qMax(boundsMax.x(), currentX));
                boundsMin.setY(qMin(boundsMin.y(),currentY));
                boundsMax.setY(qMax(boundsMax.y(), currentY));
                boundsMin.setZ(qMin(boundsMin.z(),currentZ));
                boundsMax.setZ(qMax(boundsMax.z(), currentZ));
                qDebug()<< QObject::tr("Xs=%1").arg(currentX);
                pi = QVector3D(currentX,currentY,currentZ);
                m_points.push_back(pi);
                t_island.island.append(pi);
                current_str = in.readLine();
            }
            else
            {
                break;
            }
        }
        if(t_island.island.count()>1)
        {
            m_parts.append(t_island);
        }
    }
    bounds = boundsMax - boundsMin;
    outMin = boundsMin;
    scale = 100 / qMax(bounds.x(), qMax(bounds.y(), bounds.z()));

    for(int j=0;j<m_points.size();j++)
    {
        m_points[j] = (m_points[j] - (boundsMin + bounds * 0.5)) * scale;
        qDebug()<< QObject::tr("X=%1").arg(m_points[j].x());
    }
}
void GModel::resetData()
{
    m_parts.clear();
}
