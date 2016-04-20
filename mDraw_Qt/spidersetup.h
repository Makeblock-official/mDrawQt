#ifndef SPIDERSETUP_H
#define SPIDERSETUP_H

#include <QWidget>

namespace Ui {
class SpiderSetup;
}

class SpiderSetup : public QWidget
{
    Q_OBJECT

public:
    explicit SpiderSetup(QWidget *parent = 0);
    ~SpiderSetup();

private:
    Ui::SpiderSetup *ui;
};

#endif // SPIDERSETUP_H
