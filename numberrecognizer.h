#ifndef NUMBERRECOGNIZER_H
#define NUMBERRECOGNIZER_H

#include <QImage>
#include "heronfield.h"
#include <imagedecorder.h>


class ImageNumSelection;
class NumberRecognizer
{
public:
    const int IMAGE_WIDTH;
    const int IMAGE_HEIGHT;
    QMap<int,ImageNumSelection> mData;
    NumberRecognizer(QString data, int imageWidth, int imageHeight);
    double recognize(QImage image);
    void learningPass(double learningSpeed, double learningMoment);
    HeronField * getHerons(){
        return &_herons;
    };
protected:
    HeronField _herons;
    ImageDecorder _decoder = ImageDecorder();

};

class ImageNumSelection{
public:
    ImageNumSelection(QList<double> pixels, double num){
        mNum = num;
        mPixels = pixels;
    }
    double mNum;

    QList<double> mPixels;
};

#endif // NUMBERRECOGNIZER_H
