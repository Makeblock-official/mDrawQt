#include "textedit.h"
#include "ui_textedit.h"
#include <QDebug>
#include <QWebFrame>
#include <QFile>
#include <QMessageBox>

TextEdit::TextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("qrc:/textEdit/index.html"));
    this->setWindowTitle(tr("FontEdit"));
}

TextEdit::~TextEdit()
{
    delete ui;
}

void TextEdit::on_btnExport_clicked()
{
    QVariant po = ui->webView->page()->mainFrame()->evaluateJavaScript("outSVG();");
    QString outs = po.toString();
    QFile file("out.svg");
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, tr("提示"), tr("无法创建文件"));
        return ;
    }
    QTextStream out(&file);
    out<<outs;
    file.close();
    emit Sig_ShowImage();
    this->close();
}
