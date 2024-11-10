#include <QCoreApplication>
#include "heron.h"
#include <qDebug>
#include "heronfield.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "The start of programm";
    HeronField herons = HeronField(QList<int>{1,2,3,4,1});
    qDebug() << "The end of programm";
    return a.exec();
}

