#include "newmdraw.h"
#include "ui_newmdraw.h"
#include <QDebug>
#include <QFileDialog>
#include <QGLWidget>
#include <QMessageBox>
#include <QSettings>


newmdRAW::newmdRAW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newmdRAW)
{
    bConnect = false;
    bLoaded = false;
    bPrinting = false;
    isStop = true;
    lastDir = ".";
    gcode = new readGcode();
    mySerialport = new QSerialPort();
    ui->setupUi(this);
    initDrawer();
    on_robotCombo_currentTextChanged("XY");
}
newmdRAW::~newmdRAW()
{
    delete ui;
}
void newmdRAW::initDrawer()
{
    mScara = new ScaraSetup();
    mSpider = new SpiderSetup();
    mCar = new CarSetup();
    mXY = new XYsetup();
    mEgg = new EggSetup();

    //    QRect rectF = ui->graphicsView->rect();
    gScene = new robotScene(0,this);
    //    gScene->setSceneRect(rectF);
    //    QObject::connect(gScene,SIGNAL(Sig_pos(QPointF)),this,SLOT(Slot_MouseDoubleClick(QPointF)));
    svgs = new svgPath();
    connect(gScene,SIGNAL(Sig_DrawFinish()),SLOT(Slot_DrawFinish()));
    ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->graphicsView->setScene(gScene);

    QSettings* psetting = new QSettings("Config.ini",QSettings::IniFormat);
    psetting->beginGroup("laser");
    int sliderPower = psetting->value("laserPower").toInt();
    int sliderSpeed = psetting->value("laserSpeed").toInt();
    ui->slideLaserPower->setValue(sliderPower);
    ui->slideLaserDelay->setValue(sliderSpeed);
    psetting->endGroup();

    //init serial and show it in the UI combo
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            qDebug()<<info.portName()<<info.description()<<info.manufacturer();
            comList.append(info.portName());
            serial.close();
        }
    }
    ui->portCombo->addItems(comList);
}


//update usrt
void newmdRAW::on_updateUart_clicked()
{
    ui->portCombo->clear();
    comList.clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            qDebug()<<info.portName()<<info.description()<<info.manufacturer();
            comList.append(info.portName());
            serial.close();
        }
    }
    ui->portCombo->addItems(comList);
}
// connect to usrt
void newmdRAW::on_btnConnect_clicked()
{
    if(!bConnect)
    {
        QString comName = ui->portCombo->currentText();
        mySerialport->setPortName(comName);
        mySerialport->setBaudRate(115200);
        mySerialport->setDataBits(QSerialPort::Data8);
        mySerialport->setParity(QSerialPort::NoParity);
        mySerialport->setStopBits(QSerialPort::OneStop);
        mySerialport->setFlowControl(QSerialPort::NoFlowControl);
        if(mySerialport->open(QIODevice::ReadWrite))
        {
            connect(mySerialport,SIGNAL(readyRead()),this,SLOT(Slot_ResponseUart()));
            ui->btnConnect->setText(tr("Disconnect"));
            bConnect = true;
            //QMessageBox::information(this,tr("Notice"),tr("Serial open successful."));
        }
        else
        {
            QMessageBox::information(this,tr("Notice"),tr("Serial open failed."));
        }

    }
    else
    {
        bConnect = false;
        ui->btnConnect->setText(tr("Connect"));
        mySerialport->close();

    }
}

// send to Arduino
void newmdRAW::SendToArduino(QString t)
{
    if(bConnect)
    {
        mySerialport->write(t.toLatin1());
    }
}

//add to sender
void newmdRAW::AddToSender()
{
    if(bLoaded)
    {
        while(1)
        {
            toSend = gcode->readOneLine();
            if(toSend.startsWith(";"))
            {

            }
            else
            {
                 break;
            }

        }
        if(toSend == "end")
        {
           CancleNow();
        }
        if(toSend.startsWith("G1"))
        {
            gScene->Slot_RenderChange();
        }
        qDebug()<<"send:"<<toSend;
    }
}

//slot of UART
void newmdRAW::Slot_ResponseUart()
{
    QByteArray ba = mySerialport->readAll();
    if(!ba.isEmpty())
    {
        QString le = ba;
        qDebug()<<le;
        if(le.startsWith("start"))
        {
            QMessageBox::information(this,tr("Notice"),tr("Serial conected!"));
        }
        else if(le.startsWith("oMG"))
        {
            if(!isStop)
            {
                AddToSender();
                SendToArduino(toSend);
                // updae the progress
            }
        }
        else
        {
            SendToArduino(toSend);
        }
    }
}

//choose robot
void newmdRAW::on_btnSetRobot_clicked()
{
    QString robo_type = ui->robotCombo->currentText();
    if(robo_type=="mScara")
    {
        mScara->show();

    }
    else if(robo_type=="mSpider")
    {
        mSpider->show();
    }
    else if(robo_type=="mEggBot")
    {
        mEgg->show();
    }
    else if(robo_type=="mCar")
    {
        mCar->show();
    }
    else if(robo_type=="XY")
    {
        mXY->show();
    }
}

//roboCombox changed
void newmdRAW::on_robotCombo_currentTextChanged(const QString &arg1)
{
    QString robo_type = arg1;
    if(robo_type=="mScara")
    {
        //        ChangeTypeIcon("scara");
        //        cent = QPoint(gScene->width()/2,gScene->height()/2+120);
        //        scaraRobot = new Scara(gScene);
        //        scaraRobot->initRobotCanvas();
        //        gScene->addItem(scaraRobot);
        //        scaraRobot->setPos(cent);
        //        ui->graphicsView->update();
    }
    else if(robo_type=="mSpider")
    {
        ChangeTypeIcon("spider");
    }
    else if(robo_type=="mEggBot")
    {
        ChangeTypeIcon("egg");
    }
    else if(robo_type=="mCar")
    {
        ChangeTypeIcon("car");
    }
    else if(robo_type=="XY")
    {
        //        ChangeTypeIcon("xy");
        //        cent = QPoint(gScene->width()/2,gScene->height()/2+120);
        //        xyRobot = new XYRobot(gScene);
        //        xyRobot->initRobotCanvas();
        //        gScene->addItem(xyRobot);
        //        xyRobot->setPos(cent);
    }
}
void newmdRAW::ChangeTypeIcon(QString pic)
{
    ui->labelModel->setStyleSheet(tr("background-color: rgb(247, 247, 247);border-image: url(:/images/%1.png);").arg(pic));
}
void newmdRAW::Slot_MouseDoubleClick(QPointF p)
{
    xyRobot->setTarget(p);
    ui->graphicsView->update();
}

//draw finished
void newmdRAW::Slot_DrawFinish()
{
    //on_btnPrintPic_clicked();
    ui->btnPrintPic->setStyleSheet(tr("QPushButton{border-image:url(:/images/scara-UI-Start-normal.png) 0;}QPushButton:hover {border-image: url(:/images/scara-UI-Start-hover.png) 0;}QPushButton:pressed{border-image: url(:/images/scara-UI-Start-click.png) 0;}"));
    bPrinting = false;
    SendToArduino("G28 X Y\n");
    isStop = true;
    gScene->bAnimate = false;
    toSend = "";
    SendToArduino("M4 P0\n");

}
//open a svg file
void newmdRAW::on_btnLoadPic_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("打开文件"),lastDir,tr("Images  (*.svg)"));
    lastDir = filename;
    QGraphicsSvgItem* p_svg = new QGraphicsSvgItem(filename);
    p_svg->setFlag(QGraphicsItem::ItemIsSelectable,true);
    p_svg->setFlag(QGraphicsItem::ItemIsMovable,true);
    //    gScene->addItem(p_svg);

    svgs->fillPathVector(filename,true,false);

    gScene->pModel->resetData();
    gScene->update();
    bLoaded = false;
    //process out.gcode
    gScene->pModel->loadFile("out.gcode");
    gScene->update();
    bLoaded = true;
    gcode->setTargetFile("out.gcode");
}

//delete file
void newmdRAW::on_btnClearPic_clicked()
{
    gScene->pModel->resetData();
    gScene->CancleDraw();
    gScene->update();
    bLoaded = false;
}

//begin to print
void newmdRAW::on_btnPrintPic_clicked()
{
    if(!bPrinting)
    {
        if(bConnect)
        {
            //begin send gcode  to arduino
            if(bLoaded)
            {
                //auto play and send to arduino
                SendToArduino("G28 X Y\n");
                bPrinting = true;
                isStop = false;
                ui->btnPrintPic->setStyleSheet(tr("QPushButton{border-image:url(:/images/scara-UI-Suspendend-normal.png) 0;}QPushButton:hover {border-image: url(:/images/scara-UI-Suspendend-hover.png) 0;}QPushButton:pressed{border-image: url(:/images/scara-UI-Suspendend-click.png) 0;}"));
                gScene->bAnimate = true;
            }
            else
            {
                QMessageBox::warning(this,tr("Warning"),tr("Not load any file!"));
            }

        }
        //ifconnect printer
        else
        {
            if(bLoaded)
            {
                //auto play,but not send to arduino
                gScene->StartDraw();
                bPrinting = true;
                ui->btnPrintPic->setStyleSheet(tr("QPushButton{border-image:url(:/images/scara-UI-Suspendend-normal.png) 0;}QPushButton:hover {border-image: url(:/images/scara-UI-Suspendend-hover.png) 0;}QPushButton:pressed{border-image: url(:/images/scara-UI-Suspendend-click.png) 0;}"));
            }
            else
            {
                QMessageBox::warning(this,tr("Warning"),tr("Not load any file!"));
            }
        }
    }
    else    //stop
    {
        isStop = true;
        bPrinting = false;
        ui->btnPrintPic->setStyleSheet(tr("QPushButton{border-image:url(:/images/scara-UI-Start-normal.png) 0;}QPushButton:hover {border-image: url(:/images/scara-UI-Start-hover.png) 0;}QPushButton:pressed{border-image: url(:/images/scara-UI-Start-click.png) 0;}"));
        gScene->StopDraw();
    }
}

//cancle print
void newmdRAW::CancleNow()
{
    bLoaded = false;
    isStop = true;
    gcode->reset();
    gScene->CancleDraw();
    SendToArduino("M4 P0\n");
    SendToArduino("G28  X Y\n");
}
void newmdRAW::on_btnStop_clicked()
{
    SendToArduino("M4 P0\n");
    isStop = true;
}

//homing and cancle
void newmdRAW::on_btnHome_clicked()
{
    SendToArduino("M4 P0\n");
    SendToArduino("G28 X Y\n");
}


//save the setting of the laser
void newmdRAW::on_btnSaveLaser_clicked()
{
    int slidervalue = ui->slideLaserPower->value();
    int laserspeed = ui->slideLaserDelay->value();
    QSettings* psetting = new QSettings("Config.ini",QSettings::IniFormat);
    psetting->beginGroup("laser");
    psetting->setValue("laserSpeed",QVariant(laserspeed));
    psetting->setValue("laserPower",QVariant(slidervalue));
    psetting->endGroup();
    QString power = "M4 P"+QString::number(slidervalue)+"\n";
    svgs->setLaster(power);
//    QString speed = "G21\nG90\nG92\nM4  P0\nM220 S"+QString::number(laserspeed)+"\n";
     QString speed = "G21\nG90\nG92\nM4 P0\n";
    svgs->setHeader(speed);
}
//power value change
void newmdRAW::on_slideLaserPower_valueChanged(int value)
{
    ui->labelLaserPower->setText(QString::number(value));
}
//speed value change
void newmdRAW::on_slideLaserDelay_valueChanged(int value)
{
    ui->labelLaserDelay->setText(QString::number(value));
}

//send command line
void newmdRAW::on_btnSend_clicked()
{
    QString cmd = ui->lineSend->text()+"\n";
    SendToArduino(cmd);
}
