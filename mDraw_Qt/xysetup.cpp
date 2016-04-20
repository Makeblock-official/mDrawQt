#include "xysetup.h"
#include "ui_xysetup.h"

XYsetup::XYsetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XYsetup)
{
    ui->setupUi(this);
}

XYsetup::~XYsetup()
{
    delete ui;
}
