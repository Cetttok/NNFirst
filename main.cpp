#include <QCoreApplication>
#include "heron.h"
#include <qDebug>
#include "heronfield.h"
#include <QDateTime>
#include "numberrecognizer.h"
#include <QRandomGenerator>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    qDebug() << "The start of programm";
//    QList <QList<double>> selection = QList <QList<double>>();

//    selection.append(QList<double>{1,1,1});
//    selection.append(QList<double>{0,0,0});
//    selection.append(QList<double>{0,1,0});
//    selection.append(QList<double>{1,0,0});




//    for (int y = 0; y<5; y++){
//        qDebug() << "Iteration = " << y+1;
//        HeronField herons = HeronField(QList<int>{2,1});
//        for (auto &layer: herons.mHerons){
//            for(auto &heron: layer){
//                qDebug() << heron->toQString();
//            }
//        }
//        for (int i = 1; i < 10000; i++){
//            for (auto &input : selection){
//                //qDebug() << herons.calculateOutput(QList<double>{input[0],input[1]});
//                herons.calculateOutput(QList<double>{input[0],input[1]});
//                herons.makeLearningStep(input[2],0.03,0.01);

//                //qDebug() << "err = " << herons.mHerons.last().last()->mLayerError;
//                //qDebug() << "Input data: " << input
//                  //       << "Error: "<<input[2] - herons.calculateOutput(QList<double>{input[0],input[1]});

//            }
//            //qDebug() << endl;



//        }
//        //qDebug() << "output " <<herons.calculateOutput(QList<double>{0,1});
//        //qDebug() <<

//        for (auto &input : selection){
//            qDebug() <<"The END:"<< "Input data: " << input
//                     << "Result: "<<herons.calculateOutput(QList<double>{input[0],input[1]});

//        }
//        for (auto &layer: herons.mHerons){
//            for(auto &heron: layer){
//                qDebug() << heron->toQString();
//            }
//        }
//    }

//    qDebug() << "The end of programm";
    QImage image = QImage("data\\nums\\40\\Times_5.bmp");
    QImage anotherImage = QImage("data\\nums\\40\\Times_2.bmp");
    QImage tryItImage = QImage("data\\nums\\40\\Times_1.bmp");
    QImage anotherTryItImage = QImage("data\\nums\\40\\Times_7.bmp");

    QImage anotherTryItImageDouble = QImage("data\\nums\\40\\Times_9.bmp");
    QList<QImage> images;
    for (int i = 0; i< 10; i++) {
        images.append(QImage("data\\nums\\40\\Times_"+QString::number(i)+".bmp"));
    }


    NumberRecognizer heroLink = NumberRecognizer(QString("data\\nums\\40"),5,8);
    for (auto &limage: images) {
        qDebug() << "Main: Testing BASE" << heroLink.recognize(limage) << "correct - "<<images.indexOf(limage);
    }
    for (int i = 0; i< 50000; i++){
        qDebug () << i+1 << "learning iteration";
        heroLink.learningPass(0.03,0.01);

        qDebug() << "Main: Testing " << heroLink.recognize(image) << "correct - 5";
        qDebug() << "Main: Testing " << heroLink.recognize(anotherImage) << "correct - 2";
        qDebug() << "Main: Testing " << heroLink.recognize(tryItImage) << "correct - 1";
        qDebug() << "Main: Testing " << heroLink.recognize(anotherTryItImage) << "correct - 7";
        qDebug() << "Main: Testing " << heroLink.recognize(anotherTryItImageDouble) << "correct - 9";
        if (heroLink.recognize(image)==0){
            qDebug () << heroLink.getHerons()->mHerons.last().last()->toQString();
            break;
        }

    }

    for (auto &limage: images) {
        qDebug() << "Main: Testing FINAL" << heroLink.recognize(limage) << "correct - "<<images.indexOf(limage);
    }
    return a.exec();
}

