#ifndef NUMBERRECOGNIZER_H
#define NUMBERRECOGNIZER_H

#include <QImage>
#include "heronfield.h"
#include <imagedecorder.h>
//#include "chnetwork.h"
#include "chnetwork.h"
#include "filemanager.h"
//#include "convolutionalheronfield.h"
class ImageNumConvolutionSelection;
class ImageNumSelection;
class NumberRecognizer
{
public:
//    const int IMAGE_WIDTH;
//    const int IMAGE_HEIGHT;
    QMap<int,ImageNumSelection> mData;
    //QMap<int,ImageNumConvolutionSelection> mData;
    NumberRecognizer(QString data, int imageWidth, int imageHeight, QString convData = "null", QString heronsData = "null");
    QList<double> recognize(QImage image);
    QList<double> recognize(QList<QList<double> > inputs);

    void learningPass(double learningSpeed, double learningMoment);
    CHNetwork * getHerons(){
        return &_herons;
    }
    FileManager *mFileManager = nullptr;

    //void upDateAndConstructFromFile();
    void save();
protected:
    //HeronField _herons;
    CHNetwork _herons;
    //ConvolutionalHeronField _herons;
    ImageDecorder _decoder = ImageDecorder();

    //QList<double> getCorrectQListOutput(int correctNum);
    QList<double> getCorrectQListOutput(int correctNum, int classes = 10);
};
QDebug operator<<(QDebug debug, const QList<QList<double>> &image);
class ImageNumSelection{
public:
    ImageNumSelection(QList<QList<double>> pixels, QList<double> num){
        mNum = num;
        mPixels = pixels;
    }
    QList <double> mNum;

    QList<QList<double>> mPixels;
};
//class ImageNumConvolutionSelection{
//public:
//    ImageNumConvolutionSelection(QList<QList<double>> pixels, double num){
//        mNum = num;
//        mPixels = pixels;
//    }
//    double mNum;

//    QList<QList<double>> mPixels;

//};
#endif // NUMBERRECOGNIZER_H
