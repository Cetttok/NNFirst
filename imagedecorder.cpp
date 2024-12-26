#include "imagedecorder.h"
#include <qDebug>
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
QList<double> ImageDecorder::decode(QImage image)
{
    QList<double> list;
    //qDebug () << "decoded";
    for (unsigned i=0; i<image.width(); ++i)
    {
       for (unsigned j=0; j<image.height(); ++j)
          list.append((getNumForColor(image.pixel(i,j))));
    }
    return list;
}

QList<QList<double> > ImageDecorder::decodeToMatrix(QImage image)
{
    QList<QList<double>> matrix;
    //qDebug () << "decoded";
    for (unsigned i=0; i<image.width(); ++i)
    {
        matrix.append(QList<double>());
        for (unsigned j=0; j<image.height(); ++j)
          matrix[i].append((getNumForColor(image.pixel(i,j))));
    }
    return matrix;
}

