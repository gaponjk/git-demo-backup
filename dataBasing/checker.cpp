#include "checker.h"

bool Checker::loginPassword(const QString& login, const QString& password){
    if(login.isEmpty()||password.isEmpty()) return 0;
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        qDebug()<<"База данных не открыта\n";
        return 0;
    }
    QSqlQuery query(base);
    QString command="SELECT * FROM PersonalData WHERE Login glob '"+login+"' AND Password glob '"+password+"';";
    query.exec(command);
    base.close();
    QSqlRecord rec= query.record();
    query.next();
    if(query.value(rec.indexOf("Login")).toString()==login&&query.value(rec.indexOf("Password")).toString()==password)
        return 1;
    else return 0;

}
bool Checker::corectness(const QString &login, const QString &password){//проверяю на соответсвие регулярному выражению
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        qDebug()<<"База данных не открыта\n";
        return 0;
    }
    QSqlQuery query(base);
    query.exec("SELECT Login FROM PersonalData WHERE Login glob '"+login.trimmed()+"';");
    QSqlRecord rec= query.record();
    query.next();
    QRegularExpression exp("^(?:[0-9]+|[a-zA-Z]+)$");
    if(exp.match(login.trimmed()).hasMatch()&&exp.match(password.trimmed()).hasMatch()&&query.value(rec.indexOf("Login")).toString()!=login){
        base.close();
        return 1;
    }else{
        base.close();
        return 0;
    }
}

bool Checker::dotcheck(const QString &cost)
{
    QRegularExpression exp("^(\\d+(\\.\\d*)?|\\.\\d+)$");
    if(exp.match(cost.trimmed()).hasMatch())
        return true;
    else
        return false;
}

bool Checker::right(const QString &login){//узнаю права пользователя
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        qDebug()<<"База данных не открыта\n";
        return 0;
    }
    QSqlQuery query(base);
    query.exec("SELECT Access FROM PersonalData WHERE Login glob '"+login.trimmed()+"';");
    QSqlRecord rec= query.record();
    query.next();

    if(query.value(rec.indexOf("Access")).toString()=="director"){
        base.close();  return 1;
    }
    else {base.close(); return 0;}
}
