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

class PassWindow:public QDialog{
    Q_OBJECT
private:
    QLineEdit* line1,*line2;
    QPushButton *signIn,*signUp;
private slots:
    void siIn();
    void siUp();
signals:
    void is_direction();
    void send_login(const QString&);
public:
    PassWindow(QWidget* pwgt = 0);
    ~PassWindow();
};
#endif // PASSWINDOW_H
