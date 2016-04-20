#ifndef WIREGUI_H
#define WIREGUI_H

#include <QWidget>

namespace Ui {
class WireGui;
}

class WireGui : public QWidget
{
    Q_OBJECT

public:
    explicit WireGui(QWidget *parent = 0);
    ~WireGui();

private:
    Ui::WireGui *ui;
};

#endif // WIREGUI_H
