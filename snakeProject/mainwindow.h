#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include"game.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Room* room;
    QGridLayout *gridLayout;
    QWidget *gamelayout;
};
#endif // MAINWINDOW_H
