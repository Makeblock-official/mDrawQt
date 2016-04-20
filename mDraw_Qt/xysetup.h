#ifndef XYSETUP_H
#define XYSETUP_H

#include <QWidget>

namespace Ui {
class XYsetup;
}

class XYsetup : public QWidget
{
    Q_OBJECT

public:
    explicit XYsetup(QWidget *parent = 0);
    ~XYsetup();

private:
    Ui::XYsetup *ui;
};

#endif // XYSETUP_H
