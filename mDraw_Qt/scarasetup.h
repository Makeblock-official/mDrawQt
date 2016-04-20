#ifndef SCARASETUP_H
#define SCARASETUP_H

#include <QWidget>

namespace Ui {
class ScaraSetup;
}

class ScaraSetup : public QWidget
{
    Q_OBJECT

public:
    explicit ScaraSetup(QWidget *parent = 0);
    ~ScaraSetup();

private:
    Ui::ScaraSetup *ui;
};

#endif // SCARASETUP_H
