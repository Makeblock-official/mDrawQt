#ifndef NEWMDRAW_H
#define NEWMDRAW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGraphicsSvgItem>

//UI header
#include "carsetup.h"
#include "eggsetup.h"
#include "scarasetup.h"
#include "spidersetup.h"
#include "xysetup.h"
#include "wiregui.h"
#include "wiregui_xy.h"

//robot header
#include "scara.h"
#include "xyrobot.h"
#include "robotscene.h"

//gcode reader header
#include "readgcode.h"
#include "svgpath.h"

class robotScene;

class Scara;
namespace Ui {
class newmdRAW;
}

class newmdRAW : public QMainWindow
{
    Q_OBJECT

public:
    explicit newmdRAW(QWidget *parent = 0);
    ~newmdRAW();
public slots:
    void Slot_MouseDoubleClick(QPointF);
    void Slot_ResponseUart();
    void Slot_DrawFinish();
private slots:
    void on_btnSetRobot_clicked();
    void on_robotCombo_currentTextChanged(const QString &arg1);

    void on_btnLoadPic_clicked();

    void on_btnClearPic_clicked();

    void on_updateUart_clicked();

    void on_btnConnect_clicked();

    void on_btnPrintPic_clicked();

    void on_btnStop_clicked();

    void on_btnHome_clicked();

    void on_btnSaveLaser_clicked();

    void on_slideLaserPower_valueChanged(int value);


    void on_slideLaserDelay_valueChanged(int value);

    void on_btnSend_clicked();

protected:
    void initDrawer();
private:
    Ui::newmdRAW *ui;
    CarSetup* mCar;
    EggSetup* mEgg;
    ScaraSetup* mScara;
    XYsetup* mXY;
    SpiderSetup* mSpider;
    WireGui* mWire;
    WireGui_XY* mWire_XY;

    QPoint cent;
    Scara* scaraRobot;
    XYRobot* xyRobot;

     svgPath* svgs;

    //USRT
    robotScene* gScene;
    QSerialPort *mySerialport;
    QStringList comList;
    bool bConnect;
    bool isStop;

    //FILE
    QString lastDir;
    bool bLoaded;
    bool bPrinting;

    //PRINT
    readGcode* gcode;
    QString toSend;

    //funcation
    void ChangeTypeIcon(QString pic);
    void SendToArduino(QString);
    void CancleNow();
    void AddToSender();
};

#endif // NEWMDRAW_H
