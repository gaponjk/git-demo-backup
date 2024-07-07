#include "passWindow.h"

PassWindow::PassWindow(QWidget* pwgt) : QDialog(pwgt) {//по факту создаю окно с вводом данных пользователя

    line1 = new QLineEdit;
    line2 = new QLineEdit;

    QLabel* Login = new QLabel("Login");
    QLabel* Password = new QLabel("Password");

    Login->setBuddy(line1);
    Password->setBuddy(line2);

    signIn = new QPushButton("Sign in");
    signUp = new QPushButton("Sign up");

    connect(signIn, SIGNAL(clicked()), this, SLOT(siIn()));
    connect(signUp, SIGNAL(clicked()), this, SLOT(siUp()));


    QGridLayout* Layout = new QGridLayout;//распологаю по окну кнопки и lineEdit
    Layout->addWidget(Login, 0, 0);
    Layout->addWidget(Password, 1, 0);
    Layout->addWidget(line1, 0, 1);
    Layout->addWidget(line2, 1, 1);
    Layout->addWidget(signIn, 2, 1);
    Layout->addWidget(signUp, 2, 2);

    setLayout(Layout);
}

PassWindow::~PassWindow() {

    delete line1;
    delete line2;
    delete signIn;
    delete signUp;
}

void PassWindow::siIn() {//при нажатии этой кнопки я пытаююсь войти в аккаунт
    QString str1 = line1->text();
    QString str2 = line2->text();

    if (Checker::loginPassword(str1, str2) && !str1.isEmpty() && !str2.isEmpty()) {
        if (Checker::right(str1)) {
            emit is_direction();
        }
        emit send_login(str1);
        accept();
        close();
    } else {
        QMessageBox::information(this, "Сообщение", "\tПользователь не найден", QMessageBox::Ok);
    }
}

void PassWindow::siUp() {//при нажатии этой кнопки регестрирую аккаунт
    QString str1 = line1->text();
    QString str2 = line2->text();

    if (Checker::corectness(str1, str2) && !str1.isEmpty() && !str2.isEmpty()) {
        QSqlDatabase base = QSqlDatabase::addDatabase("QSQLITE");
        base.setDatabaseName("dataBase.db");
        base.open();
        if (!base.open()) {
            QMessageBox::information(this, "Сообщение", "\tБаза данных не открыта", QMessageBox::Ok);
            return;
        }

        QSqlQuery query(base);

        if (!query.exec("INSERT INTO PersonalData(Login, Password) VALUES('"+str1+"','"+str2+"');")) {
            QMessageBox::information(this, "Сообщение", "\tОшибка выполнения запроса: " + query.lastError().text(), QMessageBox::Ok);
            return;
        }
        QMessageBox::information(this, "Сообщение", "\tВы успешно зарегестрировались", QMessageBox::Ok);
        base.close();
    } else {
        QMessageBox::information(this, "Сообщение", "\tНеверный пароль или логин(Формат:^\\w|\\d$)", QMessageBox::Ok);
    }
}
