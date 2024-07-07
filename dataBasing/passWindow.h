#ifndef PASSWINDOW_H
#define PASSWINDOW_H
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include<checker.h>
//окно с вводом логина и пароля
class PassWindow:public QDialog{
    Q_OBJECT
private:
    QLineEdit* line1,*line2;
    QPushButton *signIn,*signUp;
private slots:
    void siIn();
    void siUp();
signals:
    void is_direction();//передаю права mainwindow с помщью этого метода
    void send_login(const QString&);//передаю логин mainwindow с помщью этого метода
public:
    PassWindow(QWidget* pwgt = 0);
    ~PassWindow();
};
#endif // PASSWINDOW_H
