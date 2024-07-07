
#include "paintwindow.h"
//Кроме осноных условий задания, я также реализовал каранадаш и фон, которые тоже сохраняются
#include <QApplication>
//Гапоненко Ярослав Александрович 5 группа
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintWindow w;
    w.show();
    return a.exec();
}
