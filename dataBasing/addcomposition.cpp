#include "addcomposition.h"
#include "ui_addcomposition.h"

addcomposition::addcomposition(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addcomposition)
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
        query.prepare("SELECT Name FROM Flowers WHERE Number = :number");
        query.bindValue(":number", var++);
        if (!query.exec() || !query.next()) {
            break;
        }
        QSqlRecord rec = query.record();
        QString name = query.value(rec.indexOf("Name")).toString();
        ui->comboBox->addItem(name);

    }
    base.close();
}

addcomposition::~addcomposition()
{
    delete ui;
}

void addcomposition::on_buttonBox_accepted()
{
    QSqlDatabase base=QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
        return;
    }

    QSqlQuery query(base);
    QSqlRecord rec;
    QString sortName;
    query.prepare("SELECT Sort FROM Flowers WHERE Name GLOB :name");
    query.bindValue(":name", ui->comboBox->currentText());
    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Ошибка", "Запрос не выполнен: " + query.lastError().text());
        return;
    }
    rec = query.record();
    sortName = query.value(rec.indexOf("Sort")).toString();

    query.prepare("INSERT INTO Composition (Name, FlowerName,SortName, Count) "
                  "VALUES (:name,:flowerName, :sortName, :count)");
    query.bindValue(":name", ui->lineEdit->text());
    query.bindValue(":flowerName", ui->comboBox->currentText());
    query.bindValue(":sortName", sortName);
    query.bindValue(":count", ui->lineEdit2->text().toInt());
    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Запрос не выполнен: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Успех", "Композиция успешно добавлена.");
    }

    base.close();
}

