#ifndef HERONFIELD_H
#define HERONFIELD_H
#include "heron.h"
#include <QList>
#include <cmath>
class HeronField
{
public:
    HeronField(QList<int> heronsOnLayersAmount, double startWeightMultiple = 1.0);
    QList<QList<Heron*>> mHerons;
    QList<double> calculateOutput(QList<double> inputs);
    double func(double input);
    double derFunc(double input);
    //void makeLearningStep(double correctOutput);
    double multySum(QList<double> A, QList<double> B);
    //void makeLearningStep(double correctOutput, double learningSpeed, double learningMoment);

    void clearInputsAndOutputs();
    void makeLearningStep(QList<double> correctOutput, double learningSpeed, double learningMoment);
protected:
    double weightedSum(QList<double> inputs);

};

#endif // HERONFIELD_H
