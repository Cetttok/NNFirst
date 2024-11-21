#ifndef IMAGEDECORDER_H
#define IMAGEDECORDER_H

#include <QImage>
class ImageDecorder
{
public:

    ImageDecorder();
    QList<double> decode(QImage image);
    int getNumForColor(QRgb color);
    QList<QRgb> activeColors = QList<QRgb>();
};

#endif // IMAGEDECORDER_H
