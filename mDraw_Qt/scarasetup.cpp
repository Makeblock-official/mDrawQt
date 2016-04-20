#include "scarasetup.h"
#include "ui_scarasetup.h"

ScaraSetup::ScaraSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScaraSetup)
{
    ui->setupUi(this);
}

ScaraSetup::~ScaraSetup()
{
    delete ui;
}
