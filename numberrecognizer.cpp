#include "numberrecognizer.h"
#include <QDir>

//#include "imagedecorder.h"
#include <qDebug>
NumberRecognizer::NumberRecognizer(QString data, int imageWidth, int imageHeight)
    :IMAGE_HEIGHT(imageHeight),IMAGE_WIDTH(imageWidth),_herons(CHNetwork(imageWidth,imageHeight))
//
    //QList<int>({imageHeight*imageWidth,imageHeight*imageWidth*2,1
{

    QDir dir(data);

    QStringList filesOndata=dir.entryList();

    filesOndata.removeFirst();
    filesOndata.removeFirst();

    qDebug() <<data<< filesOndata;
    qDebug() << "printed";
    mData = QMap<int,ImageNumSelection>();

    for (QString& fileName : filesOndata ){
       qDebug() << "NumberRecognizer: insert new learning element" <<  ((double)fileName.at(fileName.size()-5).unicode()-48)/10<< fileName;
       mData.insert(mData.size(),
                       ImageNumSelection(_decoder.decodeToMatrix(QImage(data+"\\"+fileName)),
                                                      ((double)fileName.at(fileName.size()-5).unicode()-48)/10));
       qDebug() << "NumberRecognizer: insert new learning element" <<  ((double)fileName.at(fileName.size()-5).unicode()-48)/10<< fileName;
       qDebug() << _decoder.decode(QImage(data+"\\"+fileName));
    }
    // qDebug () << "NumberRecognizer: herons on layers -"<<_herons.mHerons[0].size() <<_herons.mHerons[1].size()<< _herons.mHerons[2].size();

}

void NumberRecognizer::learningPass(double learningSpeed, double learningMoment)
{

    for (int imageId = 0; imageId<mData.size(); imageId++){
        //qDebug () << "NumberRecognizer: new image" << imageId+1<< "/" << mData.size();
       // qDebug() << "every!";
        _herons.calculateOutput(mData.find(imageId)->mPixels);
        //qDebug () << "debug "<<mData.find(imageId)->mPixels.size();
        //qDebug() << "mdaat "<<mData.find(imageId)->mNum;
        _herons.learningStep(QList<double>({mData.find(imageId)->mNum}),learningSpeed);
    }
    //qDebug() << "NumberRecognizer: learning pass completed!" <<mData.size();
}
double NumberRecognizer::recognize(QImage image){

//    qDebug() << "debug" << _decoder.decode(image);
    //qDebug() << "NumberRecognizer::recognize  - started!";
    double result = _herons.calculateOutput(_decoder.decodeToMatrix(image));
//    for(auto &layer: _herons.mHerons){
//        for (auto &heron : layer){
//            //qDebug() << heron->mOutput;
//            //qDebug() << endl;
//        }
//    }
    return result;
}
