#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QDialog>

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include<QButtonGroup>
namespace Ui {
class deletewindow;
}

class deletewindow : public QDialog
{
    Q_OBJECT

public:
    explicit deletewindow(QWidget *parent = nullptr);
    ~deletewindow();
    void setLogin(const QString& login);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::deletewindow *ui;
    QString login;
    QButtonGroup *buttonGroup;
    QString setDate(QDate& date);
};
#endif // DELETEWINDOW_H
