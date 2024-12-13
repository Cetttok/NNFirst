#include <QCoreApplication>
#include "heron.h"
#include <qDebug>
#include "heronfield.h"
#include <QDateTime>
#include "numberrecognizer.h"
#include <QRandomGenerator>
#include "convlayer.h"
#include "maxpoolinglayer.h"
#include "chnetwork.h"
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
//    QImage image = QImage("data\\nums\\test\\Test_3.bmp");
//    QImage anotherImage = QImage("data\\nums\\256\\Times_9.bmp");
//    QImage tryItImage = QImage("data\\nums\\40\\Times_1.bmp");
//    QImage anotherTryItImage = QImage("data\\nums\\40\\Times_7.bmp");

//    QImage anotherTryItImageDouble = QImage("data\\nums\\40\\Times_9.bmp");
//    QList<QImage> images;
//    for (int i = 0; i< 10; i++) {
//        images.append(QImage("data\\nums\\256\\Times_"+QString::number(i)+".bmp"));
//    }


//    NumberRecognizer heroLink = NumberRecognizer(QString("data\\nums\\256"),16,16);
//    qDebug() << "Main: _herons created";
//    for (auto &limage: images) {
//        qDebug() << "Main: Testing Start" << heroLink.recognize(limage) << "correct - "<<images.indexOf(limage);
////        i f (heroLink.recognize(limage)  == 0){
////            qDebug() << heroLink.getHerons()->mHerons.last().last()->toQString();
////        }
//    }
//    for (int i = 0; i< 100; i++){

//        //qDebug () <<"Main:" <<i+1 << "learning iteration";
//        heroLink.learningPass(0.001,0.0003);

//        //qDebug() << "Main: Testing " << heroLink.recognize(anotherImage) << "correct - 9";

//        if(i%2 == 0){
//            qDebug() << "Main: " << i<< "iteration:";
//            QList<double> errors = QList<double>();

//            for (auto &limage: images) {
//            double result = heroLink.recognize(limage);
//                double error = fabs(((double)images.indexOf(limage)/10.0)-result);
//                qDebug() << "Main:: Testing" << result << "correct - "<<(double)images.indexOf(limage)/10.0 << error;
//                errors.append(error);
//            }
//            double gError = 0;
//            for (auto &error :errors){
//                gError += error;
//            }
//            qDebug() << "Main: gError ="<<gError/errors.size();
//        }
////        qDebug() << "Main: Testing " << heroLink.recognize(anotherImage) << "correct - 7";
////        qDebug() << "Main: Testing " << (heroLink.recognize(image)) << "correct - 0.3";

////        qDebug() << "Main: Testing " << heroLink.recognize(tryItImage) << "correct - 1";
////        qDebug() << "Main: Testing " << heroLink.recognize(anotherTryItImage) << "correct - 7";
////        qDebug() << "Main: Testing " << heroLink.recognize(anotherTryItImageDouble) << "correct - 9";
////        if (heroLink.recognize(image)==0){
////            //qDebug () << heroLink.getHerons()->mHerons.last().last()->toQString();
////            break;
////        }

//    }
//    QList<double> errors = QList<double>();

//    for (auto &limage: images) {
//        double result = heroLink.recognize(limage);
//        double error = fabs(((double)images.indexOf(limage)/10.0)-result);
//        qDebug() << "Main: Testing FINAL" << result << "correct - "<<(double)images.indexOf(limage)/10.0 << error;
//        errors.append(error);
//    }
//    double gError = 0;
//    for (auto &error :errors){
//        gError += error;
//    }
//    qDebug() << "Main: gError ="<<gError/errors.size();
//    qDebug() << "3 - " << heroLink.recognize(image);
//    qDebug() << "7 - " << heroLink.recognize(anotherImage);
//    HeronField herons  = HeronField(QList<int>({1,1,1}));
//    for (int i = 0; i< 1000; i++) {
//        qDebug() << herons.calculateOutput(QList<double>({0.5}));
//        herons.makeLearningStep(QList<double>({1.0}),0.03,0.01);

//    }
//    qDebug() << herons.calculateOutput(QList<double>({0.5})) << "corr 1.0";
//    Tensor *data = new Tensor(8,8,1);
//    for (int y = 0; y < data->mSize.height ; y++){
//        for (int x =0; x < data->mSize.width; x++){
//            data->set(x,y,0,QRandomGenerator::global()->bounded(2.0)-1);//QRandomGenerator::global()->bounded(5.0)-2.5
//        }
//    }
//    ConvLayer firstLayer  = ConvLayer(TensorSize(8,8,1),TensorSize(4,4,2),5,2);
//    MaxPoolingLayer secondLayer = MaxPoolingLayer(TensorSize(4,4,2));
//    Tensor* ten = secondLayer.forward(firstLayer.forward(data));

//    for (int y = 0; y < ten->mSize.height ; y++){
//        for (int x =0; x < ten->mSize.width; x++){
//            qDebug() <<ten->get(x,y,0);
//        }
//    }
//    for (int y = 0; y < ten->mSize.height ; y++){
//        for (int x =0; x < ten->mSize.width; x++){
//            qDebug() <<ten->get(x,y,1);
//        }
//    }

//    CHNetwork chNet = CHNetwork(8,8);
//    QList<QList<double>> data=  QList<QList<double>>();
//    for (int y = 0; y < 8;y++) {
//        data.append(QList<double>());
//        for(int x = 0; x < 8; x++){
//            data[y].append(1);
//        }
//    }
//    qDebug() << "MAIN: Result = " << chNet.calculateOutput(data);
//    ConvLayer convLayer = ConvLayer(TensorSize(8,8,2), TensorSize(6,6,8),3,4);
//    Tensor *data = new Tensor(6,6,8);
//    for (int z = 0; z < data->mSize.depth; z++) {
//        for (int y = 0; y < data->mSize.height ; y++){
//            for (int x =0; x < data->mSize.width; x++){
//                data->set(x,y,z,0.005);//QRandomGenerator::global()->bounded(5.0)-2.5
//            }
//        }

//    }
//    Tensor *input= new Tensor(8,8,2.0);
//    for (int y = 0; y < data->mSize.height ; y++){
//        for (int x =0; x < data->mSize.width; x++){
//            input->set(x,y,0,1);//QRandomGenerator::global()->bounded(5.0)-2.5
//        }
//    }
//    MaxPoolingLayer maxPool = MaxPoolingLayer(TensorSize(8,8,2));

//    Tensor input= Tensor(8,8,2.0);

//    for (int d = 0; d < input.mSize.depth; d++){
//        for (int y = 0; y < input.mSize.height ; y++){
//            for (int x =0; x < input.mSize.width; x++){
//                input.set(x,y,d,QRandomGenerator::global()->bounded(5.0)-2.5);//QRandomGenerator::global()->bounded(5.0)-2.5
//            }
//        }
//    }
//    qDebug() << maxPool.forward(&input);
//    qDebug() << maxPool.backward(input);

//    Tensor result = convLayer.backward(*data, *input);
////    for (int i = 0; i < result.mSize.width; i++){
////        QString layer = QString();
////        for(int ii = 0; ii < result.mSize.height; ii++){
////            layer.append(QString::number(result.get(ii,i,0)));

////        }
////        qDebug() << layer;
////    }
//    Tensor filter = *convLayer._filtersGradients;
////    qDebug() << endl;
////    for (int i = 0; i < filter.mSize.width; i++){
////        QString layer = QString();
////        for(int ii = 0; ii < filter.mSize.height; ii++){
////            layer.append(QString::number(filter.get(ii,i,0))+ " ");

////        }
////        qDebug() << layer;
////    }
//    qDebug() << result;
//    qDebug() << filter;
//    convLayer.updateWeightsOfFilters(0.3);
//    qDebug() << convLayer._filter;
//    //qDebug() << result.toQStringSize();
//    CHNetwork chNet = CHNetwork (8,8);
//    QList<QList<double>> data;
//    for(int y = 0; y < 8; y++){
//        data.append(QList<double>());
//        for(int x =0; x < 8; x++){
//            data[y].append(1.0);
//        }

//    }
    QList<QImage> images;
//    for (int i = 0; i< 10; i++) {
//        images.append(QImage("data\\nums\\test\\Arial_"+QString::number(i)+".bmp"));
//    }
    for (int i = 0; i< 10; i++) {
        images.append(QImage("data\\nums\\test\\Times_"+QString::number(i)+".bmp"));
    }

    NumberRecognizer network =NumberRecognizer (QString("data\\nums\\64"), 8,8);
    //qDebug() << network.recognize(QImage("data\\nums\\64\\Times_9.bmp"))<< endl << endl<< endl << endl;
    //qDebug() << *network.getHerons() << endl;
    for (int i = 0; i < 1000; i++){
        if  (network.recognize(images[0]) == NAN){
            qDebug() << i << " iteration!";
            qDebug() << *network.getHerons();
            break;
        }
        if (i%50 == 0){
            qDebug() << i << " iteration";
            qDebug() << *network.getHerons();
            for (int l = 0; l < 10; l++){

                qDebug() << l    << network.recognize(images[l]);
            }

        }

        network.learningPass(0.03,0);
                //qDebug() << endl << endl<< endl << endl;
        //qDebug() << network.recognize(QImage("data\\nums\\64\\Times_9.bmp"));
        //qDebug() << "output " << chNet.calculateOutput(data);

    }
    qDebug() << *network.getHerons();
    for (int l = 0; l < 10; l++){

        qDebug() << l    << network.recognize(images[l]);
    }
//    auto &aaa = *network.getHerons();
//    qDebug() << aaa;
    //CHNetwork net  = CHNetwork (8,8);
//    NumberRecognizer num = NumberRecognizer(QString("data\\nums\\64"), 8,8);
//    qDebug() << *num.getHerons();
    qDebug()<<"the end";
    return a.exec();
}

