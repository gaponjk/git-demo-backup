#include <QCoreApplication>
#include "shared.h"
int main()
{
    //int*a=new int(1);
    int*b=new int(10);
    Shared_ptr<int> gh(b);
    Shared_ptr<int> jh;
    jh=gh;
}

