#ifndef HERONFIELD_H
#define HERONFIELD_H
#include "heron.h"
#include <QList>
#include <cmath>
class HeronField
{
public:
    HeronField(QList<int> heronsOnLayersAmount);
    QList<QList<Heron*>> mHerons;
    float calculateOutput(QList<float> inputs);
    float func(float input);
protected:
    float weightedSum(QList<float> inputs);

};

#endif // HERONFIELD_H
