#ifndef ADDFLOWER_H
#define ADDFLOWER_H

#include <QDialog>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include<QButtonGroup>
#include <QDialog>
#include"checker.h"
namespace Ui {
class addflower;
}

class addflower : public QDialog
{
    Q_OBJECT

public:
    explicit addflower(QWidget *parent = nullptr);
    ~addflower();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addflower *ui;
};

#endif // ADDFLOWER_H
