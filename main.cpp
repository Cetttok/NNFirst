#include <QCoreApplication>
#include "heron.h"
#include <qDebug>
#include "heronfield.h"
#include <QDateTime>
#include <QRandomGenerator>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "The start of programm";
    QList <QList<float>> selection = QList <QList<float>>();

    selection.append(QList<float>{0,0,0});
    selection.append(QList<float>{1,1,1});
    selection.append(QList<float>{0,1,1});
    selection.append(QList<float>{1,0,1});
    for (int y = 0; y<5; y++){
        qDebug() << "Iteration = " << y+1;
        HeronField herons = HeronField(QList<int>{2,1});
        for (int i = 1; i < (y+1)*400000; i++){
            for (auto &input : selection){
                //qDebug() << herons.calculateOutput(QList<float>{input[0],input[1]});
                herons.makeLearningStep(input[2],0.001,0.0002);
                //qDebug() << "err = " << herons.mHerons.last().last()->mLayerError;
            }


        }
        //qDebug() << "output " <<herons.calculateOutput(QList<float>{0,1});
        //qDebug() <<

        for (auto &input : selection){
            qDebug() << "Input data: " << input
                     << "Result: "<<herons.calculateOutput(QList<float>{input[0],input[1]});

        }
    }

    qDebug() << "The end of programm";
    return a.exec();
}

