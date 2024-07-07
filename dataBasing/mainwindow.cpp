#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow), pass(new PassWindow)
{

    this->setPalette(Qt::white);
    ui->setupUi(this);
    pass->show();
    connect(pass, SIGNAL(is_direction()), this, SLOT(setStatus()));
    connect(pass, SIGNAL(send_login(QString)), this, SLOT(setLogin(QString)));
    //base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    //base->setDatabaseName("dataBase.db");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete insertion;
    delete deletion;
    delete base;
}
void MainWindow::setStatus(){//задаю права
    rights=true;
}

void MainWindow::setLogin(const QString& login){//вывожу логин в основное окно
    this->login=login;
    ui->name->setText(ui->name->text()+login);
    sign=true;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {//для проверки того авторизовалс яопльзователь или нет
    if (!sign&&event->button() == Qt::LeftButton) {
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
    }
}

QString MainWindow::setDate(QDate& date){//внутрення функция, которую я использовал, чтобы преобразовывать дату в нужный формат
    QString formateDate;
    if(date.day()<10)
        formateDate="0"+QString::number(date.day());
    else formateDate=QString::number(date.day());
    if(date.month()<10)
        formateDate+=".0"+QString::number(date.month())+".2024";
    else formateDate ="."+QString::number(date.month())+".2024";
    return formateDate;
}



void MainWindow::on_allFlowers_clicked()//вывод всех цветков
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base->setDatabaseName("dataBase.db");
    if(rights){
        base->open();
        if(!base->isOpen()){
            QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
            return;
        }
        QSqlQuery query(*base);
        query.exec("SELECT * FROM Flowers");
        QSqlRecord rec= query.record();
        ui->textBrowser->clear();
        while (query.next()){
            ui->textBrowser->append("Название: "+query.value(rec.indexOf("Name")).toString()+"  Сорт: "+query.value(rec.indexOf("Sort")).toString()
                                    +"  Стоимость: "+query.value(rec.indexOf("Cost")).toString());
        }
        base->close();
    }else
        QMessageBox::information(this, "Сообщение", "\tВы не имеете надлежащих прав", QMessageBox::Ok);

}


void MainWindow::on_allOrders_clicked()//вывод всех заказов
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base->setDatabaseName("dataBase.db");
    if(rights){
        base->open();
        if(!base->isOpen()){
            QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
            return;
        }
        QSqlQuery query(*base);
        query.exec("SELECT * FROM Orders");
        QSqlRecord rec= query.record();
        ui->textBrowser->clear();

        while (query.next()){
            ui->textBrowser->append("Заказчик: "+query.value(rec.indexOf("Name")).toString()+" Композиция: "
                                    +query.value(rec.indexOf("Composition")).toString()
                                    +" Количество: "+query.value(rec.indexOf("Count")).toString()+"  Стоимость: "+
                                    query.value(rec.indexOf("Cost")).toString()+"  Дата заказа: "+
                                    query.value(rec.indexOf("OrderВate")).toString()+" Дата выполнения: "+
                                    query.value(rec.indexOf("FinalDate")).toString());
        }
        base->close();
    }else
       QMessageBox::information(this, "Сообщение", "\tВы не имеете надлежащих прав", QMessageBox::Ok);
}


void MainWindow::on_deleteOrder_clicked()// кнопка удаление заказа
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    deletion=new deletewindow();//открываю для этого отдельное окно
    deletion->setLogin(login);
    deletion->show();
}


void MainWindow::on_makeOrder_clicked()//кнопка добалвление заказа
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    insertion=new insertionwindow();//открываю для этого отдельное окно
    insertion->setLogin(login);
    insertion->show();
}


void MainWindow::on_myOrders_clicked()//посмотреть свои заказы
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base->setDatabaseName("dataBase.db");
    base->open();
    if(!base->isOpen()){
        QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
        return;
    }
    QSqlQuery query(*base);
    query.exec("SELECT * FROM Orders WHERE Name glob '"+login+"';");
    QSqlRecord rec= query.record();
    ui->textBrowser->clear();
    ui->textBrowser->append("Мои заказы:\n");
    while (query.next()){
        ui->textBrowser->append("Композиция: "+query.value(rec.indexOf("Composition")).toString()
                                +" Количество: "+query.value(rec.indexOf("Amount")).toString()+"  Стоимость: "+
                                query.value(rec.indexOf("Cost")).toString()+"  Дата заказа: "+
                                query.value(rec.indexOf("OrderDate")).toString()+" Дата выполнения: "+
                                query.value(rec.indexOf("FinalDate")).toString());
    }
    base->close();
}


void MainWindow::on_orderedFlowers_clicked()//какие цветы были заказаны
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    if(rights){
    base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base->setDatabaseName("dataBase.db");
    QDate d1=ui->dateEdit->date(), d2=ui->dateEdit2->date();
    int count=d1.daysTo(d2);
    if(count>=0){
        base->open();
        if(!base->isOpen()){
            QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
            return;
        }

        QSqlQuery query(*base), query2(*base);

        query.exec("SELECT Composition, COUNT(*) FROM Orders WHERE FinalDate BETWEEN '"+setDate(d1)+"' AND '"+setDate(d2)+"' GROUP BY Composition;");
        QSqlRecord rec= query.record(), rec2;
        ui->textBrowser->clear();
        ui->textBrowser->append("Кол-во использованных цветов за указанный период: ");
        while (query.next()){
            query2.exec("SELECT flowerName FROM Composition WHERE Name glob '"+query.value(rec.indexOf("Composition")).toString()+"';");
            rec2= query2.record();
            query2.next();
            ui->textBrowser->append(query2.value(rec2.indexOf("flowerName")).toString()+"  Кол-во проданных штук: "+query.value(rec.indexOf("COUNT(*)")).toString());
        }
    }
    base->close();
}else
    QMessageBox::information(this, "Сообщение", "\tВы не имеете надлежащих прав", QMessageBox::Ok);
}


void MainWindow::on_periodMoney_clicked()//какие деньги были заработаны за период
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base->setDatabaseName("dataBase.db");
    QDate d1=ui->dateEdit->date(), d2=ui->dateEdit2->date();
    int count=d1.daysTo(d2);
    if(count>=0){
        base->open();
        if(!base->isOpen()){
            QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
            return;
        }
        QSqlQuery query(*base);
        query.exec("SELECT Cost FROM Orders WHERE FinalDate BETWEEN '"+setDate(d1)+"' AND '"+setDate(d2)+"';");
        QSqlRecord rec= query.record();
        double price=0;
        ui->textBrowser->clear();
        ui->textBrowser->append("Прибыль за указанный период: ");
        while (query.next()){
            price+=query.value(rec.indexOf("Cost")).toDouble();
        }
        ui->textBrowser->append(QString::number(price));
        base->close();
    }
}


void MainWindow::on_periodOrders_clicked()//какие заказы были сделаны за период
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    if(rights){
    base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base->setDatabaseName("dataBase.db");
    QDate d1=ui->dateEdit->date(), d2=ui->dateEdit2->date();
    int count=d1.daysTo(d2);
    if(count>=0){
    base->open();
    if(!base->isOpen()){
        QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
        return;
    }
    QSqlQuery query(*base);
    query.exec("SELECT * FROM Orders WHERE OrderDate BETWEEN '"+setDate(d1)+"' AND '"+setDate(d2)+"';");
    QSqlRecord rec= query.record();

    ui->textBrowser->clear();
    ui->textBrowser->append("Все заказы поступившие в указанные числа: ");
    while (query.next()){
        ui->textBrowser->append("Заказчик: "+query.value(rec.indexOf("Name")).toString()+" Композиция: "+query.value(rec.indexOf("Composition")).toString()
                                +" Количество: "+query.value(rec.indexOf("Count")).toString()+"  Стоимость: "+
                                query.value(rec.indexOf("Cost")).toString()+"  Дата заказа: "+
                                query.value(rec.indexOf("OrderDate")).toString()+" Дата выполнения: "+
                                query.value(rec.indexOf("FinalDate")).toString());
    }



    base->close();
    }
}else
    QMessageBox::information(this, "Сообщение", "\tВы не имеете надлежащих прав", QMessageBox::Ok);
}


void MainWindow::on_popComp_clicked()//популярность композиций
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    if(rights){
    base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base->setDatabaseName("dataBase.db");
    base->open();
    if(!base->isOpen()){
        QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
        return;
    }
    QSqlQuery query(*base);
    query.exec("SELECT Composition, COUNT(*) FROM Orders GROUP BY Composition");
    QSqlRecord rec= query.record();
    ui->textBrowser->clear();
    ui->textBrowser->append("Популярность композиций:\n");
    while (query.next()){
        ui->textBrowser->append(query.value(rec.indexOf("Composition")).toString()+"  Кол-во проданных штук: "+query.value(rec.indexOf("COUNT(*)")).toString());
    }

    base->close();
}else
    QMessageBox::information(this, "Сообщение", "\tВы не имеете надлежащих прав", QMessageBox::Ok);
}


void MainWindow::on_allComposition_clicked()//вывод всех композиций
{
    if(!sign){
        QMessageBox::warning(this, "Сообщение", "\tВы не авторизовались", QMessageBox::Ok);
        return;
    }
    base=new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base->setDatabaseName("dataBase.db");
    if(rights){
        base->open();
        if(!base->isOpen()){
            QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
            return;
        }
        QSqlQuery query2(*base), query(*base);
        query.exec("SELECT * FROM Composition");
        QSqlRecord rec= query.record();
        QString buf, flowerName;
        ui->textBrowser->clear();
        while (query.next()){
            flowerName=query.value(rec.indexOf("FlowerName")).toString();
            query2.exec("SELECT Cost FROM Flowers WHERE Name glob '"+flowerName+"';");
            query2.next();
            buf="Название: "+query.value(rec.indexOf("Name")).toString()+" Цветы: "+
                  query.value(rec.indexOf("FlowerName")).toString()+"  Сорт: "+query.value(rec.indexOf("SortName")).toString()+
                  "  Стоимость: "+QString::number(query.value(rec.indexOf("Count")).toInt()*query2.value(query2.record().indexOf("Cost")).toDouble());
            ui->textBrowser->append(buf);
        }
        base->close();
    }else
        QMessageBox::information(this, "Сообщение", "\tВы не имеете надлежащих прав", QMessageBox::Ok);
}

