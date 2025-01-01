#include "numberrecognizer.h"
#include <QDir>

//#include "imagedecorder.h"
#include <qDebug>
NumberRecognizer::NumberRecognizer(QString data, int imageWidth, int imageHeight , QString convData, QString heronsData)
    :/*IMAGE_HEIGHT(imageHeight),IMAGE_WIDTH(imageWidth),*/_herons(CHNetwork(imageWidth,imageHeight))
//
    //QList<int>({imageHeight*imageWidth,imageHeight*imageWidth*2,1
{
    for(int i = 0; i< 10; i++){
        qDebug() << _decoder.decodeToMatrix(QImage("data\\nums\\test\\test_"+QString::number(i)+".bmp"));
    }

    mFileManager = new FileManager(convData, heronsData);
    //mFileManager->saveHeronFieldToFile(_herons.getLastLayer());
    //mFileManager->saveNetworkToFile(&_herons);
    QDir dir(data);
   // qDebug() << data << dir.entryList();
    QStringList filesOndata=dir.entryList();

    filesOndata.removeFirst();
    filesOndata.removeFirst();

    //qDebug() <<data<< filesOndata;
    //qDebug() << "printed";
    mData = QMap<int,ImageNumSelection>();

    for (QString& fileName : filesOndata ){
       //qDebug() << "NumberRecognizer: insert new learning element" <<  ((double)fileName.at(fileName.size()-5).unicode()-48)/10<< fileName;
       mData.insert(mData.size(),
                       ImageNumSelection(_decoder.decodeToMatrix(QImage(data+"\\"+fileName)),
                                                      getCorrectQListOutput(((double)fileName.at(fileName.size()-5).unicode()-48))));
//       mData.insert(mData.size(),
//                            ImageNumSelection(_decoder.decodeToMatrix(QImage(data+"\\"+fileName)),
//                                                           getCorrectQListOutput(((double)fileName.at(0).unicode()-48))));
        //qDebug() << "NumberRecognizer: insert new learning element" <<  ((double)fileName.at(fileName.size()-5).unicode()-48)<< fileName;
       //qDebug() << _decoder.decodeToMatrix(QImage(data+"\\"+fileName));
    }
    qDebug() << "NumberRecognizer(...): mData init succsesfull!!! Count images/resoures =" << mData.size();
    //qDebug () << "NumberRecognizer: herons on layers -"<<_herons.mHerons[0].size() <<_herons.mHerons[1].size()<< _herons.mHerons[2].size();
    _herons = *mFileManager->initNetworkFromFiles(imageWidth, imageHeight);
}

QList<double> NumberRecognizer::getCorrectQListOutput(int correctNum, int classes){
    QList<double> list = QList<double> ();
    for (int i = 0; i < classes; i++){
        if ( i == correctNum){
            list.append(1);
        }
        else{
            list.append(0);
        }
    }
    return list;
}
void NumberRecognizer::learningPass(double learningSpeed, double learningMoment)
{

    for (int imageId = 0; imageId<mData.size(); imageId++){
        //qDebug () << "NumberRecognizer: new image" << imageId+1<< "/" << mData.size();
       // qDebug() << "every!";
        _herons.calculateOutput(mData.find(imageId)->mPixels);
        //qDebug () << "debug "<<mData.find(imageId)->mPixels.size();
        //qDebug() << "mdaat "<<mData.find(imageId)->mNum;
        _herons.learningStep(mData.find(imageId)->mNum,learningSpeed);
    }
    //qDebug() << "NumberRecognizer: learning pass completed!" <<mData.size();
}

void NumberRecognizer::save()
{
    mFileManager->saveNetworkToFile(&_herons);
}


QList<double>NumberRecognizer::recognize(QImage image){

//    qDebug() << "debug" << _decoder.decode(image);
    //qDebug() << "NumberRecognizer::recognize  - started!";

//    for(auto &layer: _herons.mHerons){
//        for (auto &heron : layer){
//            //qDebug() << heron->mOutput;
//            //qDebug() << endl;
//        }
//    }
    return _herons.calculateOutput(_decoder.decodeToMatrix(image));;
}

QList<double> NumberRecognizer::recognize(QList<QList<double> > inputs)
{
    qDebug() << inputs;
    return _herons.calculateOutput(inputs);
}



QDebug operator<<(QDebug debug, const QList<QList<double>> &image)
{
    debug << "Image(" << image.size() << "*" << image.first().size() << "):" << endl;
    for (int y =0 ; y < image.size(); y++){
        QString line = QString();
        for(int x = 0; x < image[y].size();x++){
            line.append(QString::number(image[y][x])+ " " );
        }
        debug << qPrintable(line) << endl;
    }
    return debug;
}
