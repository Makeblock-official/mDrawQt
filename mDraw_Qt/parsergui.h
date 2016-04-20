#ifndef PARSERGUI_H
#define PARSERGUI_H

#include <QWidget>

namespace Ui {
class ParserGUI;
}

class ParserGUI : public QWidget
{
    Q_OBJECT

public:
    explicit ParserGUI(QWidget *parent = 0);
    ~ParserGUI();

private:
    Ui::ParserGUI *ui;
};

#endif // PARSERGUI_H
