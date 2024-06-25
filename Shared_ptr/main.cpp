#include <QCoreApplication>
#include "shared.h"
int main()
{
    int*a=new int(1);
    int*b=new int(10);
    Shared_ptr<int> gh(b);
    Shared_ptr<int> jh(a);
    QTextStream(stdout)<<*gh<<Qt::endl;
    if(jh<gh)
        QTextStream(stdout)<<"it works"<<Qt::endl;
    Shared_ptr<int> kl;
    kl=gh;
    QTextStream(stdout)<<*kl<<Qt::endl;
}

