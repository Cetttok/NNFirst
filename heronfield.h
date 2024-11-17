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
    float derFunc(float input);
    //void makeLearningStep(float correctOutput);
    float multySum(QList<float> A, QList<float> B);
    void makeLearningStep(float correctOutput, float learningSpeed, float learningMoment);

    void clearInputsAndOutputs();
protected:
    float weightedSum(QList<float> inputs);

};

#endif // HERONFIELD_H
