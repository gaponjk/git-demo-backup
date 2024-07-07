#include <QtTest>
#include"checker.h"
//Гапоненко Яросав Александрович 5 группа
//Unit test

class testData : public QObject
{
    Q_OBJECT

public:
    testData();
    ~testData();

private slots:
    void test_case1();
    void loginPassword();
    void rights();
};

testData::testData()
{
}

testData::~testData()
{

}

void testData::test_case1()
{

}
//я проверял правильность ввода логина и пороля
void testData::rights()
{
    Checker check;
    QCOMPARE(check.right("jjdsfvwelngjefl"),false);
    QCOMPARE(check.right("gaponjk"),true);
}
void testData::loginPassword()
{
    Checker check;
    QCOMPARE(check.loginPassword("5454w54*-+","pas452 52sword"),false);
    QCOMPARE(check.loginPassword("",""),false);
    QCOMPARE(check.loginPassword("Логин","Пароль"),false);
}

QTEST_APPLESS_MAIN(testData)

#include "tst_testdata.moc"
