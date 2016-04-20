#ifndef CARSETUP_H
#define CARSETUP_H

#include <QWidget>

namespace Ui {
class CarSetup;
}

class CarSetup : public QWidget
{
    Q_OBJECT

public:
    explicit CarSetup(QWidget *parent = 0);
    ~CarSetup();

private:
    Ui::CarSetup *ui;
};

#endif // CARSETUP_H
