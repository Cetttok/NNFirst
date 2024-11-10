#ifndef HERONFIELD_H
#define HERONFIELD_H
#include "heron.h"
#include <QList>
class HeronField
{
public:
    HeronField(QList<int> heronsOnLayersAmount);
    QList<QList<Heron*>> mHerons;

};

#endif // HERONFIELD_H
