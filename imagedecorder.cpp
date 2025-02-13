#include "imagedecorder.h"
#include <QDebug>
ImageDecorder::ImageDecorder()
{
    qDebug() << "IMAGE DECODER HAS BEEN CREATED!";
}


int ImageDecorder::getNumForColor(QRgb color, int countClasses){
    if (activeColors.contains(color)){

        return activeColors.indexOf(color);
    }
    else{
        if (activeColors.size() < countClasses){
            activeColors.append(color);
            return activeColors.size()-1;
            qDebug() << "ImageDecorder: added new color";
        }
        else{
            return activeColors.size();
        }

    }
}
double getLightness(QColor color){
    return ((double(color.red() + color.green() + color.blue())/765.0));
}
QList<double> ImageDecorder::decode(QImage image)
{

    QList<double> list;
    //qDebug () << "decoded";
    for (unsigned i=0; i<image.width(); ++i)
    {
       for (unsigned j=0; j<image.height(); ++j)
          list.append(getLightness(image.pixelColor(i,j)));
    }
    return list;
}
QList<QList<double> > ImageDecorder::decodeToMatrix(QImage image)
{
    if(image.isNull()){
        qDebug() << "ImageDecorder::decodeToMatrix(QImage image): nullImage!";
        return QList<QList<double>>();
    }
    QList<QList<double>> matrix;
    //qDebug () << "decoded";
    for (unsigned i=0; i<image.width(); ++i)
    {
        matrix.append(QList<double>());
        for (unsigned j=0; j<image.height(); ++j)
          matrix[i].append(getLightness(image.pixelColor(i,j)));
    }
    return matrix;
}

