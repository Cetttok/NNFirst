#include "imagedecorder.h"
#include <qDebug>
ImageDecorder::ImageDecorder()
{
    qDebug() << "IMAGE DECODER HAS BEEN CREATED TYPE: ";
}


int ImageDecorder::getNumForColor(QRgb color){
    if (activeColors.contains(color)){
        return activeColors.indexOf(color);
    }
    else{
        activeColors.append(color);
        qDebug() << "ImageDecorder: added new color";
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

