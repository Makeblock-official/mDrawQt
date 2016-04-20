#include "newmdraw.h"
#include <QApplication>

//#ifdef __cplusplus
//extern "C" {
//#endif
//extern int svgToGcode();

//#ifdef __cplusplus
//}
//#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    newmdRAW w;
    w.show();
//    svgToGcode();
    return a.exec();
}
