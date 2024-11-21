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
    double calculateOutput(QList<double> inputs);
    double func(double input);
    double derFunc(double input);
    //void makeLearningStep(double correctOutput);
    double multySum(QList<double> A, QList<double> B);
    void makeLearningStep(double correctOutput, double learningSpeed, double learningMoment);

    void clearInputsAndOutputs();
protected:
    double weightedSum(QList<double> inputs);

};

#endif // HERONFIELD_H
