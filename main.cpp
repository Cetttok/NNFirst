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

    qDebug() << "the start";
   QApplication a(argc, argv);
    ResultViewer viewer;
    viewer.mWidget->show();
    QList<QImage> images;
    for (int i = 0; i< 10; i++) {
        images.append(QImage("data\\nums\\test\\Calibri_"+QString::number(i)+".bmp"));
        if (images.last().isNull()){
            qDebug() << "error" <<"data\\nums\\test\\Calibri_"+QString::number(i)+".png" ;
            return 1;
        }
    }

    NumberRecognizer network =NumberRecognizer (QString("data\\nums\\64"), 8,8, "data\\convData.txt", "data\\heronFieldData.txt");
    for (int i = 0; i < 10000; i++){
        a.processEvents();
            for (int l = 0; l < 10; l++){
                viewer.upDateRow(network.recognize(images[l]),l);
            }
            viewer.upDate(i);
        network.learningPass(0.01,0);
        if (i%20 == 0){
            network.save();
        }
    }
    network.save();
    qDebug()<<"the end";
//       QList<QString> data;
//       data.append("Layer{");
//       data.append("Heron(0_[0.1,0.2]_basis(1.0));");
//       data.append("Heron(1_[0.1,0.3]_basis(2.0));");
//       data.append("Heron(2_[0.1,0.4]_basis(3.0));");
//       data.append("Heron(3_[0.1,0.5]_basis(4.1));");
//       data.append("}");
//       data.append("Layer{");
//       data.append("Heron(0_[0.1,0.2]_basis(1.0));");
//       data.append("Heron(1_[0.1,0.3]_basis(2.0));");
//       data.append("Heron(2_[0.1,0.4]_basis(3.0));");
//       data.append("Heron(3_[0.1,0.5]_basis(4.1));");
//       data.append("}");

//   FileManager* manager = new FileManager (QString("data\\heronFieldData.txt"));
//   HeronField* herons = new HeronField(QList<int>({8,128,1}));/*manager->createNewHeronFieldFromFile(manager->readFile())*/;
//   manager->saveHeronFieldToFile(herons);
//   qDebug() << herons->calculateOutput(QList<double>({0,0,0,0,0,0,0,0}));
//   delete herons;
//   herons = manager->createNewHeronFieldFromFile(manager->readFile());
//   qDebug() << herons->calculateOutput(QList<double>({0,0,0,0,0,0,0,0}));
//   NumberRecognizer rec = NumberRecognizer("data\\64",8,8);
//   FileManager * manager = new FileManager ("data\\convData.txt", "data\\heronFieldData.txt");
//   CHNetwork * net = new CHNetwork(8,8);
//   ImageDecorder dec = ImageDecorder ();
//   net  = manager->initNetworkFromFiles(8,8);
//   qDebug() << "inited";
//   qDebug() << net->getLastLayer()->calculateOutput(QList<double>({0,0,0,0,0,0,0,0}));
//   qDebug() << net->calculateOutput(dec.decodeToMatrix(QImage("data\\nums\\64\\Verdana1_9.bmp")));
//   manager->saveNetworkToFile(net);
//   NumberRecognizer network = NumberRecognizer("data\\nums\\64",8,8, "data\\convData.txt", "data\\heronFieldData.txt");
//   qDebug() << network.recognize(QImage("data\\nums\\64\\Verdana1_9.bmp"));

//   network.learningPass(0.3,0);
//   qDebug() << network.recognize(QImage("data\\nums\\64\\Verdana1_9.bmp"));
//   network.save();
   //qDebug() << net->getLastLayer()->mHerons.first().size();



//    qDebug() << herons->calculateOutput(QList<double>({1,1,1,1}));

//    for (auto & layer : herons->mHerons){
//        for (auto * heron: layer){
//            qDebug () << heron->toQString();
//        }
//    }
//     //qDebug() << manager->getLinksFromFile(data) << manager->getLinksFromFile(data).size();
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
//    NumberRecognizer net = NumberRecognizer (QString("data\\nums\\64"), 8,8, "data\\convData.txt");
//    net.upDateAndConstructFromFile();
//    qDebug() << *net.getHerons();
//    qDebug() << net.recognize(QImage("data\\nums\\64\\Verdana1_9.bmp"));
//    net.learningPass(1,0);
//    qDebug() << net.recognize(QImage("data\\nums\\64\\Verdana1_9.bmp"));
//    net.mFileManager->saveNetworkToFile(net.getHerons());
    return a.exec();
}

