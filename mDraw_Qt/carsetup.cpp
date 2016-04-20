#include "carsetup.h"
#include "ui_carsetup.h"

CarSetup::CarSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarSetup)
{
    ui->setupUi(this);
}

CarSetup::~CarSetup()
{
    delete ui;
}
