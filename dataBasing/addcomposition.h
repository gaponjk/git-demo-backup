#ifndef ADDCOMPOSITION_H
#define ADDCOMPOSITION_H

#include <QDialog>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include<QButtonGroup>
#include <QDialog>
namespace Ui {
class addcomposition;
}

class addcomposition : public QDialog
{
    Q_OBJECT

public:
    explicit addcomposition(QWidget *parent = nullptr);
    ~addcomposition();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addcomposition *ui;
};

#endif // ADDCOMPOSITION_H
