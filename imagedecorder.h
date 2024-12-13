#ifndef IMAGEDECORDER_H
#define IMAGEDECORDER_H

#include <QImage>
class ImageDecorder
{
public:

    ImageDecorder();
    int getNumForColor(QRgb color);
    QList<QRgb> activeColors = QList<QRgb>();
    QList<double> decode(QImage image);
    QList<QList<double>> decodeToMatrix(QImage image);
};

#endif // IMAGEDECORDER_H
