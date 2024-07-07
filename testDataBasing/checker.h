#ifndef CHECKER_H
#define CHECKER_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QMessageBox>
class Checker{
public:
    static bool right(const QString& login);
    static bool loginPassword(const QString& login, const QString& password);
    static bool corectness(const QString& login, const QString& password);
};
#endif // CHECKER_H
