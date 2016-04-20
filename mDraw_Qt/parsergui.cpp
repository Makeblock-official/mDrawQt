#include "parsergui.h"
#include "ui_parsergui.h"

ParserGUI::ParserGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParserGUI)
{
    ui->setupUi(this);
}

ParserGUI::~ParserGUI()
{
    delete ui;
}
