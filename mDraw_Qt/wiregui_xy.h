#ifndef WIREGUI_XY_H
#define WIREGUI_XY_H

#include <QWidget>

namespace Ui {
class WireGui_XY;
}

class WireGui_XY : public QWidget
{
    Q_OBJECT

public:
    explicit WireGui_XY(QWidget *parent = 0);
    ~WireGui_XY();

private:
    Ui::WireGui_XY *ui;
};

#endif // WIREGUI_XY_H
