#include <QCoreApplication>
#include "heron.h"
#include <qDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "123123123123123123123123123123123123 yes";
    Heron heron = Heron();
    return a.exec();
}

