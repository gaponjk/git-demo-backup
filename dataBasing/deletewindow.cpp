#include "deletewindow.h"
#include "ui_deletewindow.h"

deletewindow::deletewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletewindow)
{
    ui->setupUi(this);
    QColor color ("#5e2180");
    this->setPalette(color);
    setWindowTitle("Цветочки");
    setWindowIcon(QIcon("flower.png"));
    QSqlDatabase base=QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
        return;
    }
    QSqlQuery query(base);
    int var = 1;

    while (true) {
        query.prepare("SELECT Name FROM Composition WHERE Number = :number");
        query.bindValue(":number", var++);
        if (!query.exec() || !query.next()) {
            break;
        }
        QString name = query.value(0).toString();
        ui->comboBox->addItem(name);
    }
    base.close();

}
deletewindow::~deletewindow()
{
    delete ui;
}

void deletewindow::setLogin(const QString& login){//получаю логин из основного класса
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

void deletewindow::on_buttonBox_accepted()
{//нахожу заказ в базе данных и удаляю его
    QDate d1=ui->dateEdit->date(), d2=ui->dateEdit2->date();
    QSqlDatabase base=QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
        return;
    }
    QSqlQuery query(base);
    query.prepare("DELETE FROM Orders WHERE Name GLOB :name AND Composition GLOB :composition AND Amount "
                  "= :amount AND OrderDate GLOB :orderDate AND FinalDate GLOB :finalDate");

    query.bindValue(":name", login);
    query.bindValue(":composition", ui->comboBox->currentText());
    query.bindValue(":amount", ui->lineEdit->text());
    query.bindValue(":orderDate", QString(setDate(d1)));
    query.bindValue(":finalDate", QString(setDate(d2)));

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Запрос не выполнен: " + query.lastError().text());
    } else {
        if (query.numRowsAffected() == 0)
            QMessageBox::warning(this, "Ошибка", "Не найден заказ с указанными параметрами.");
         else
            QMessageBox::information(this, "Успех", "Заказ успешно удален.");

    }
}



void deletewindow::on_buttonBox_rejected()
{
    this->hide();
}

