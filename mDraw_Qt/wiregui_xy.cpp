#include "wiregui_xy.h"
#include "ui_wiregui_xy.h"

WireGui_XY::WireGui_XY(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WireGui_XY)
{
    ui->setupUi(this);
}

WireGui_XY::~WireGui_XY()
{
    delete ui;
}
