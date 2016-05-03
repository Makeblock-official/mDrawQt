#ifndef SVGPATH_H
#define SVGPATH_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include "svg2gcode.h"

class closeIsland
{
public:
    QVector<QVector3D>island;
};
class svgPath : public QObject
{
    Q_OBJECT
public:
    explicit svgPath(QObject *parent = 0);
    //function
    void fillPathVector(QString file,bool besize,bool exportFile);
    void setLaster(QString pon);
    void setHeader(QString pheader);
    void setPrintPicWidth(int i);

signals:

public slots:

private:
    QVector<closeIsland>fullPath;


};

#endif // SVGPATH_H
