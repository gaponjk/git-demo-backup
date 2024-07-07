#include "insertionwindow.h"
#include "ui_insertionwindow.h"

insertionwindow::insertionwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::insertionwindow)
{
    ui->setupUi(this);
    buttonGroup = new QButtonGroup(this);//нумерую кнопки
    buttonGroup->addButton(ui->radioButton, 1);
    buttonGroup->addButton(ui->radioButton2, 2);
    buttonGroup->addButton(ui->radioButton3, 3);
    buttonGroup->addButton(ui->radioButton4, 4);
}

insertionwindow::~insertionwindow()
{
    delete ui;
}
void insertionwindow::setLogin(const QString& login){//получаю логин из основного класса
    this->login=login;
}
QString insertionwindow::setDate(QDate& date){//внутренний метод для форматирования даты
    QString formateDate;
    if(date.day()<10)
        formateDate="0"+QString::number(date.day());
    else formateDate=QString::number(date.day());
    if(date.month()<10)
        formateDate+=".0"+QString::number(date.month())+".2024";
    else formateDate ="."+QString::number(date.month())+".2024";
    return formateDate;
}

void insertionwindow::on_buttonBox_accepted()// проверяю можно ли добавить в базу данных введенную информацию и
    //добавляю если она соответсвуе критериям
{
    QDate d1=ui->dateEdit->date(), d2=ui->dateEdit2->date();
    int count=d1.daysTo(d2);
    if(count>=0){
        QSqlDatabase base=QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        base.setDatabaseName("dataBase.db");
        base.open();
        if(!base.isOpen()){
            QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
            return;
        }

        double cost;
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
        query.exec("SELECT FlowerName, Count FROM Composition WHERE Name glob '"+composition+"';");
        QSqlRecord rec=query.record();
        query.next();
        cost=query.value(rec.indexOf("Count")).toDouble();

        query.exec("SELECT Cost FROM Flowers WHERE Name glob '"+query.value(rec.indexOf("FlowerName")).toString()+"';");
        rec=query.record();
        query.next();
        cost*=query.value(rec.indexOf("Cost")).toDouble();
        cost*=ui->lineEdit->text().toInt();

        if(count==1||count==0)
            cost=cost*1.25;
        else if(count>=2)
            cost=cost*1.15;
        query.prepare("INSERT INTO Orders (Name, Composition, Cost, Amount, OrderDate, FinalDate) "
                      "VALUES (:login, :composition, :cost, :amount, :orderDate, :finalDate)");
        query.bindValue(":login", login);
        query.bindValue(":composition", composition);
        query.bindValue(":cost", cost);
        query.bindValue(":amount", ui->lineEdit->text());
        query.bindValue(":orderDate", setDate(d1));
        query.bindValue(":finalDate", setDate(d2));
        if (!query.exec()) {
            QMessageBox::critical(this, "Ошибка", "Запрос не выполнен: " + query.lastError().text());
        } else {
            QMessageBox::information(this, "Успех", "Заказ успешно добавлен.");
        }

        base.close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Дата окончания должна быть позже или совпадать с датой начала.");
    }
}

