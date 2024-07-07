#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    room=new Room();
    gridLayout=new QGridLayout();
    gamelayout=new QWidget();
    gridLayout->addWidget(room,0,0);
    gamelayout->setLayout(gridLayout);
    setCentralWidget(gamelayout);
}
//задаю так, чтобы у виджета были видимая граница у окна
MainWindow::~MainWindow() {}
