#include "deletewindow.h"
#include "ui_deletewindow.h"

deletewindow::deletewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletewindow)
{
    ui->setupUi(this);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->radioButton, 1);
    buttonGroup->addButton(ui->radioButton2, 2);
    buttonGroup->addButton(ui->radioButton3, 3);
    buttonGroup->addButton(ui->radioButton4, 4);
}

deletewindow::~deletewindow()
{
    delete ui;
}

void deletewindow::setLogin(const QString& login){
    this->login=login;
}
QString deletewindow::setDate(QDate& date){
    QString formateDate;
    if(date.day()<10)
        formateDate="0"+QString::number(date.day());
    else formateDate=QString::number(date.day());
    if(date.month()<10)
        formateDate+=".0"+QString::number(date.month())+".2024";
    else formateDate ="."+QString::number(date.month())+".2024";
    return formateDate;
}

void deletewindow::on_buttonBox_accepted()//могут возникать проблемы с композицией, потому что в базе данных может кто то написать К английскую
{
    QDate d1=ui->dateEdit->date(), d2=ui->dateEdit2->date();
    QSqlDatabase base=QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
        return;
    }
    QString composition="";
    int id = buttonGroup->checkedId();
    switch (id) {
    case 1:
        composition = "К1";
        break;
    case 2:
        composition = "К2";
        break;
    case 3:
        composition = "К3";
        break;
    case 4:
        composition = "К4";
        break;
    default:
        break;
    }
    QSqlQuery query(base);
    query.next();
    query.prepare("DELETE FROM Orders WHERE Name GLOB :name AND Composition GLOB :composition AND Amount "
                  "= :amount AND OrderDate GLOB :orderDate AND FinalDate GLOB :finalDate");

    query.bindValue(":name", login);
    query.bindValue(":composition", composition);
    query.bindValue(":amount", ui->lineEdit->text());
    query.bindValue(":orderDate", QString(setDate(d1)));
    query.bindValue(":finalDate", QString(setDate(d2)));

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Запрос не выполнен: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Успех", "Заказ успешно удален.");
    }
}

