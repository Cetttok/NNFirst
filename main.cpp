//#include <QCoreApplication>
#include "heron.h"
#include <QDebug>
#include "heronfield.h"
#include <QApplication>
//#include <QDateTime>
#include "numberrecognizer.h"
#include <QApplication>
#include <QRandomGenerator>
#include <qmainwindow.h>
#include "convlayer.h"
#include "maxpoolinglayer.h"
#include "chnetwork.h"
#include "resultviewer.h"
#include "filemanager.h"
#include "resultchecker.h"
int main(int argc, char *argv[])
{

    QApplication * a = new QApplication(argc, argv);
//    ResultViewer viewer;
//    viewer.mWidget->show();
////
////    ResultViewer viewer = ResultViewer ();
//    qDebug() << "1234";
//    viewer.mWidget->show();
//    qDebug() << "the start" <<argc;
    qDebug() << argv[0] << argv[1] << argv[2];
    if (QString(argv[1]) == "learn"){

        qDebug() << "NNFirst - alpha version. Configuration: learn";
        ResultViewer viewer;
        viewer.mWidget->show();
        QList<QImage> images;
        for (int i = 0; i< 10; i++) {
            images.append(QImage("data//nums//test//" + QString::number(i)+"_002199.png" ));
            if (images.last().isNull()){
                qDebug() << "error" <<"data//nums//test//" + QString::number(i)+"_002199.png" ;
                return 1;
            }
        }
        qDebug() << "taram";
        NumberRecognizer network =NumberRecognizer (QString("D://miniMnist"), 8,8, "data//convData.txt", "data//heronFieldData.txt");
        qDebug() << "Start Error for training = "<< network.getErrorForTrainning();
        if (QString(argv[2])== "clear"){
            qDebug() << "cleared";
            network.clear();
            network.save();
            return 1 ;
        }

        for (int i = 0; i < 10000; i++){
            a->processEvents();
                for (int l = 0; l < 10; l++){
                    viewer.upDateRow(network.recognize(images[l]),l);
                }
                viewer.upDate(i);
            network.learningPass(0.01,0);
            if (i%20 == 0){
                network.save();
            }
            if (i%20 == 0 && i!=0){
                qDebug() <<  i<< "Error for training = " << network.getErrorForTrainning();
            }
        }
        network.save();


    }
    else if (QString(argv[1] )== "test"){
        qDebug() << "NNFirst - alpha version. Configuration: test";
    ResultChecker*  checker = new  ResultChecker(new NumberRecognizer (QString("data//nums//64"), 8,8, "data//convData.txt", "data//heronFieldData.txt"));
        qDebug() << "Learning error" << checker->network()->getErrorForTrainning();

    }
    else{
        qDebug() << "NNFirst - alpha version. Bad Configuration argument";
        return 0;
    }

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

//   FileManager* manager = new FileManager (QString("data//heronFieldData.txt"));
//   HeronField* herons = new HeronField(QList<int>({8,128,1}));/*manager->createNewHeronFieldFromFile(manager->readFile())*/;
//   manager->saveHeronFieldToFile(herons);
//   qDebug() << herons->calculateOutput(QList<double>({0,0,0,0,0,0,0,0}));
//   delete herons;
//   herons = manager->createNewHeronFieldFromFile(manager->readFile());
//   qDebug() << herons->calculateOutput(QList<double>({0,0,0,0,0,0,0,0}));
//   NumberRecognizer rec = NumberRecognizer("data//64",8,8);
//   FileManager * manager = new FileManager ("data//convData.txt", "data//heronFieldData.txt");
//   CHNetwork * net = new CHNetwork(8,8);
//   ImageDecorder dec = ImageDecorder ();
//   net  = manager->initNetworkFromFiles(8,8);
//   qDebug() << "inited";
//   qDebug() << net->getLastLayer()->calculateOutput(QList<double>({0,0,0,0,0,0,0,0}));
//   qDebug() << net->calculateOutput(dec.decodeToMatrix(QImage("data//nums//64//Verdana1_9.bmp")));
//   manager->saveNetworkToFile(net);
//   NumberRecognizer network = NumberRecognizer("data//nums//64",8,8, "data//convData.txt", "data//heronFieldData.txt");
//   qDebug() << network.recognize(QImage("data//nums//64//Verdana1_9.bmp"));

//   network.learningPass(0.3,0);
//   qDebug() << network.recognize(QImage("data//nums//64//Verdana1_9.bmp"));
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
//    NumberRecognizer net = NumberRecognizer (QString("data//nums//64"), 8,8, "data//convData.txt");
//    net.upDateAndConstructFromFile();
//    qDebug() << *net.getHerons();
//    qDebug() << net.recognize(QImage("data//nums//64//Verdana1_9.bmp"));
//    net.learningPass(1,0);
//    qDebug() << net.recognize(QImage("data//nums//64//Verdana1_9.bmp"));
//    net.mFileManager->saveNetworkToFile(net.getHerons());
    qDebug() << "before";
    qDebug() << a->applicationName();
//    int r = a->exec();
//    qDebug() << r;
//    return r;
    return a->exec();

}

