#ifndef EGGSETUP_H
#define EGGSETUP_H

#include <QWidget>

namespace Ui {
class EggSetup;
}

class EggSetup : public QWidget
{
    Q_OBJECT

public:
    explicit EggSetup(QWidget *parent = 0);
    ~EggSetup();

private:
    Ui::EggSetup *ui;
};

#endif // EGGSETUP_H
