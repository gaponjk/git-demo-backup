#include "mainwindow.h"
//Гапоненко Яросав Александрович 5 группа
#include <QApplication>
//Исопльзование базы данных с Qt
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
