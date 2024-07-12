#include "passWindow.h"

PassWindow::PassWindow(QWidget* pwgt) : QDialog(pwgt) {//по факту создаю окно с вводом данных пользователя
    setWindowTitle("Вход");
    setWindowIcon(QIcon("account.png"));
    QColor color ("#5e2180");
    this->setPalette(color);
    QString lineStyle = R"(
QLineEdit{
 background-color: #8e44ad;
 border: 2px solid #732d91;
  color: white;
    font-size: 16px;
    font-weight: bold;
    padding: 10px 20px;
}
 QLineEdit:hover {
                background-color: #732d91;
            }
        )";
    QString labelStyle=R"(QLabel{
 color: white;
    font-size: 16px;
    font-weight: bold;
})";
    QString pushButtonStyle=R"(
             QPushButton {
                background-color: #5e2180;
                color: white;
                border: 1px solid #8f4a9f;
                border-radius: 4px;
                padding: 5px 10px;
            }
             QPushButton:hover {
                background-color: #7c3bb8;
                border: 1px solid #9f5ecf;
            }
             QPushButton:pressed {
                background-color: #4a1760;
                border: 1px solid #7a3a8e;
            })";
    line1 = new QLineEdit;
    line2 = new QLineEdit;
    line1->setStyleSheet(lineStyle);
    line2->setStyleSheet(lineStyle);
    QLabel* Login = new QLabel("Логин");
    QLabel* Password = new QLabel("Пароль");
    Login->setStyleSheet(labelStyle);
    Password->setStyleSheet(labelStyle);
    Login->setBuddy(line1);
    Password->setBuddy(line2);

    signIn = new QPushButton("Войти");
    signUp = new QPushButton("Зарегестрироваться");
    signIn->setStyleSheet(pushButtonStyle);
    signUp->setStyleSheet(pushButtonStyle);
    connect(signIn, SIGNAL(clicked()), this, SLOT(siIn()));
    connect(signUp, SIGNAL(clicked()), this, SLOT(siUp()));


    QGridLayout* Layout = new QGridLayout;//распологаю по окну кнопки и lineEdit
    Layout->addWidget(Login, 0, 0);
    Layout->addWidget(Password, 1, 0);
    Layout->addWidget(line1, 0, 1, 1, 2);
    Layout->addWidget(line2, 1, 1,1,2);
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
