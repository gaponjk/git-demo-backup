
#include "paintwindow.h"

#include <QApplication>
//Гапоненко Ярослав Александрович 5 группа
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintWindow w;
    w.show();
    return a.exec();
}
