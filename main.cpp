#include <QCoreApplication>
#include "heron.h"
#include <qDebug>
#include "heronfield.h"
#include <QDateTime>
#include "numberrecognizer.h"
#include <QApplication>
#include <QRandomGenerator>
#include "convlayer.h"
#include "maxpoolinglayer.h"
#include "chnetwork.h"
#include "resultviewer.h"
#include "filemanager.h"
int main(int argc, char *argv[])
{

//    qDebug() << "the start";
   QApplication a(argc, argv);
//    ResultViewer viewer;
//    viewer.mWidget->show();
//    QList<QImage> images;
//    for (int i = 0; i< 10; i++) {
//        images.append(QImage("data\\nums\\test\\Calibri_"+QString::number(i)+".bmp"));
//        if (images.last().isNull()){
//            qDebug() << "error" <<"data\\nums\\test\\Calibri_"+QString::number(i)+".png" ;
//            return 1;
//        }
//    }

//    NumberRecognizer network =NumberRecognizer (QString("data\\nums\\64"), 8,8);
//    for (int i = 0; i < 10000; i++){
//        a.processEvents();
//        if (i%1 == 0){
//            for (int l = 0; l < 10; l++){
//                viewer.upDateRow(network.recognize(images[l]),l);
//            }
//            viewer.upDate(i);

//        }

//        network.learningPass(0.01,0);
//    }
//    qDebug()<<"the end";
//    FileManager manager =FileManager ("data\\data.txt");
////    qDebug() << manager.parseTensorSize("(64,32,8)");
////    qDebug() << manager.parseLayerData("ConvLayer_size_(8,8,1)->(6,6,4)");
////    qDebug() << manager.parseLayersSize("Network:ConvLayer_size_(8,8,1)->(6,6,4);MaxPool_size_(6,6,4)->(3,3,4);");
////    QList<QString> data;
////    data.append("ConvLayer_filters{");
////    data.append("Tensor_size_(3,3,3);");
////    data.append("7-7-7");
////    data.append("8-8-8");
////    data.append("9-9-9");
////    data.append("and");
////    data.append("10-10-10");
////    data.append("11-11-11");
////    data.append("12-12-12");
////    data.append("and");
////    data.append("7-7-7");
////    data.append("8-8-8");
////    data.append("9-9-9");
////    data.append("end");
////    data.append("}");
//    qDebug() << manager.getLayersData();
//    qDebug() << manager.getFilters()[0];
    NumberRecognizer net = NumberRecognizer (QString("data\\nums\\64"), 8,8, "data\\data.txt");
    net.upDateAndConstructFromFile();
    qDebug() << *net.getHerons();
    qDebug() << net.recognize(QImage("data\\nums\\64\\Verdana1_9.bmp"));
    net.learningPass(1,0);
    qDebug() << net.recognize(QImage("data\\nums\\64\\Verdana1_9.bmp"));
    return a.exec();
}

