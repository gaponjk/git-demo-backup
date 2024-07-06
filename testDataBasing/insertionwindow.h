#ifndef INSERTIONWINDOW_H
#define INSERTIONWINDOW_H

#include <QDialog>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
#include<QButtonGroup>
namespace Ui {
class insertionwindow;
}

class insertionwindow : public QDialog
{
    Q_OBJECT

public:
    explicit insertionwindow(QWidget *parent = nullptr);
    void setLogin(const QString& login);
    ~insertionwindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::insertionwindow *ui;
    QString login;
    QButtonGroup *buttonGroup;
    QString setDate(QDate& date);
};

#endif // INSERTIONWINDOW_H
