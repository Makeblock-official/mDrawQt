#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>

namespace Ui {
class TextEdit;
}

class TextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TextEdit(QWidget *parent = 0);
    ~TextEdit();

private slots:
    void on_btnExport_clicked();

private:
    Ui::TextEdit *ui;
signals:
    void Sig_ShowImage();
};

#endif // TEXTEDIT_H
