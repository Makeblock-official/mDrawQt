#include "wiregui.h"
#include "ui_wiregui.h"

WireGui::WireGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WireGui)
{
    ui->setupUi(this);
}

WireGui::~WireGui()
{
    delete ui;
}
