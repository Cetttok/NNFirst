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
//    qDebug() << QRandomGenerator::global()->bounded(2.0)-1;
//    qDebug() <<  QRandomGenerator::global()->bounded(2.0)-1;
//    qDebug() << QRandomGenerator::global()->bounded(2.0)-1;
//    qDebug() << QRandomGenerator::global()->bounded(2.0)-1;
//    qDebug()  << QRandomGenerator::global()->bounded(2.0)-1;
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
    QImage image = QImage("data\\nums\\test\\Test_3.bmp");
    QImage anotherImage = QImage("data\\nums\\test\\Test_7.bmp");
    QImage tryItImage = QImage("data\\nums\\40\\Times_1.bmp");
    QImage anotherTryItImage = QImage("data\\nums\\40\\Times_7.bmp");

    QImage anotherTryItImageDouble = QImage("data\\nums\\40\\Times_9.bmp");
    QList<QImage> images;
    for (int i = 0; i< 10; i++) {
        images.append(QImage("data\\nums\\40\\Times_"+QString::number(i)+".bmp"));
    }


    NumberRecognizer heroLink = NumberRecognizer(QString("data\\nums\\40"),5,8);
    qDebug() << "Main: _herons created";
    for (auto &limage: images) {
        qDebug() << "Main: Testing Start" << heroLink.recognize(limage) << "correct - "<<images.indexOf(limage);
        if (heroLink.recognize(limage)  == 0){
            qDebug() << heroLink.getHerons()->mHerons.last().last()->toQString();
        }
    }
    for (int i = 0; i< 1000; i++){
        qDebug () <<"Main:" <<i+1 << "learning iteration";
        heroLink.learningPass(0.001,0.0003);

        //qDebug() << "Main: Testing " << heroLink.recognize(image) << "correct - 5";
        //qDebug() << "Main: Testing " << heroLink.recognize(anotherImage) << "correct - 7";
        qDebug() << "Main: Testing " << (heroLink.recognize(image)) << "correct - 0.6";

        //qDebug() << "Main: Testing " << heroLink.recognize(tryItImage) << "correct - 1";
        //qDebug() << "Main: Testing " << heroLink.recognize(anotherTryItImage) << "correct - 7";
        //qDebug() << "Main: Testing " << heroLink.recognize(anotherTryItImageDouble << "correct - 9";
        if (heroLink.recognize(image)==0){
            //qDebug () << heroLink.getHerons()->mHerons.last().last()->toQString();
            break;
        }

    }
    QList<double> errors = QList<double>();

    for (auto &limage: images) {
        double result = heroLink.recognize(limage);
        double error = fabs(((double)images.indexOf(limage)/10.0)-result);
        qDebug() << "Main: Testing FINAL" << result << "correct - "<<(double)images.indexOf(limage)/10.0 << error;
        errors.append(error);
    }
    double gError = 0;
    for (auto &error :errors){
        gError += error;
    }
    qDebug() << "Main: gError ="<<gError/errors.size();
    qDebug() << "3 - " << heroLink.recognize(image);
    qDebug() << "7 - " << heroLink.recognize(anotherImage);
//    HeronField herons  = HeronField(QList<int>({1,1,1}));
//    for (int i = 0; i< 1000; i++) {
//        qDebug() << herons.calculateOutput(QList<double>({0.5}));
//        herons.makeLearningStep(QList<double>({0.9}),0.03,0.01);

//    }
//    qDebug() << herons.calculateOutput(QList<double>({0.5})) << "corr 0.9";
    return a.exec();
}

