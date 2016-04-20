#include "spidersetup.h"
#include "ui_spidersetup.h"

SpiderSetup::SpiderSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpiderSetup)
{
    ui->setupUi(this);
}

SpiderSetup::~SpiderSetup()
{
    delete ui;
}
