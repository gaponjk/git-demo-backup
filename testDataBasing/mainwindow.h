#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QListView>
#include <QMouseEvent>
#include <QTimer>
#include "passWindow.h"
#include "insertionwindow.h"
#include "deletewindow.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    ~MainWindow();

private slots:
    void setStatus();
    void setLogin(const QString& str);
    void on_allComposition_clicked();

    void on_allFlowers_clicked();

    void on_allOrders_clicked();

    void on_deleteOrder_clicked();

    void on_makeOrder_clicked();

    void on_myOrders_clicked();

    void on_orderedFlowers_clicked();

    void on_periodMoney_clicked();

    void on_periodOrders_clicked();

    void on_popComp_clicked();

private:
    Ui::MainWindow *ui;
    PassWindow* pass;
    insertionwindow* insertion;
    deletewindow* deletion;
    QSqlDatabase *base;
    QString login;
    bool rights=false;
    bool sign=false;
    QString setDate(QDate& date);
};
#endif // MAINWINDOW_H
