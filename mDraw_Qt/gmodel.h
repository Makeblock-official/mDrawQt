#ifndef GMODEL_H
#define GMODEL_H

#include <QString>
#include <QVector>
#include <QVector3D>
#include <math.h>


#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

class partIsland
{
public:
    QVector<QVector3D>island;

};


class GModel
{
public:
    GModel();
    void loadFile(QString filePath);
    void resetData();
    void render();
    QVector3D bounds;
    qreal scale;
    QVector3D outMin;

    QString fileName() const { return m_fileName; }
    QVector<QVector3D> m_points;
    QVector<partIsland>m_parts;
private:
    QString m_fileName;
};

#endif // GMODEL_H
