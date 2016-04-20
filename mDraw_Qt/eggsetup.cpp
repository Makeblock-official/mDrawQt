#include "eggsetup.h"
#include "ui_eggsetup.h"

EggSetup::EggSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EggSetup)
{
    ui->setupUi(this);
}

EggSetup::~EggSetup()
{
    delete ui;
}
