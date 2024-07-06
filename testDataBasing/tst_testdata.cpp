#include <QtTest>
#include"checker.h"
// add necessary includes here

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

void testData::rights()
{
    Checker check;
    QCOMPARE(check.right("jjdsfvwelngjefl"),false);
    QCOMPARE(check.right("gaponjk"),true);
}
void testData::loginPassword()
{
    Checker check;
    QCOMPARE(check.loginPassword("5454w54*-+","pas45252sword"),false);
    QCOMPARE(check.loginPassword("",""),false);
    QCOMPARE(check.loginPassword("Логин","Пароль"),false);
}

QTEST_APPLESS_MAIN(testData)

#include "tst_testdata.moc"
