#include "addflower.h"
#include "ui_addflower.h"

addflower::addflower(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addflower)
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
    QVector<QString> vector;
    while (true) {
        query.prepare("SELECT Sort FROM Flowers WHERE Number = :number");
        query.bindValue(":number", var++);
        if (!query.exec() || !query.next()) {
            break;
        }
        QSqlRecord rec = query.record();
        QString name = query.value(rec.indexOf("Sort")).toString();
        if(!vector.contains(name)){
        vector.append(name);
        ui->comboBox->addItem(name);
        }
    }
    ui->comboBox->setEditable(true);
    base.close();
}

addflower::~addflower()
{
    delete ui;
}

void addflower::on_buttonBox_accepted()
{
    if(!Checker::dotcheck(ui->lineEdit2->text())){
        QMessageBox::information(this, "Сообщение", "\tВы ввели цену неверно", QMessageBox::Ok);
        return;
    }
    QSqlDatabase base=QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
        return;
    }

    QSqlQuery query(base);
    query.prepare("INSERT INTO Flowers (Name, Sort, Cost) "
                  "VALUES (:name, :sort, :cost)");
    query.bindValue(":name", ui->lineEdit->text());
    query.bindValue(":sort", ui->comboBox->currentText());
    query.bindValue(":cost", ui->lineEdit2->text());
    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Запрос не выполнен: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Успех", "Цветок успешно добавлен.");
    }

    base.close();
}



