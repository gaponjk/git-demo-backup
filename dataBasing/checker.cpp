#include "checker.h"

bool Checker::loginPassword(const QString &login, const QString &password){//проверяю на соответсвие регулярному выражению
    QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("dataBase.db");
    base.open();
    if(!base.isOpen()){
        qDebug()<<"База данных не открыта\n";
        return 0;
    }
    QSqlQuery query(base);
    query.exec("SELECT Login FROM PersonalData WHERE Login glob '"+login.trimmed()+"';");
    QRegularExpression exp("^(?:[0-9]+|[a-zA-Z]+)$");
    if(exp.match(login.trimmed()).hasMatch()&&exp.match(password.trimmed()).hasMatch()){
        base.close();
        return 1;
    }else{
        base.close();
        return 0;
    }
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
