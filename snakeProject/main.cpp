#include "mainwindow.h"
//Гапоненко Ярослав Александрович
#include <QApplication>
//Итоговый проект "Змейка"
//изначально я пытался реализовать игру с помощью .ui файла через label, но у меня возникли с этим неполадки, поэтому я пошел этим путем
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
