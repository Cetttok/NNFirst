#ifndef ACTIVATIONLAYER_H
#define ACTIVATIONLAYER_H

#include "baselayer.h"



class ActivationLayer : public BaseLayer
{
public:
    ActivationLayer(TensorSize size, int id);
    bool isNeedSaving();
    int getId();
    TensorSize getInputSize();
    TensorSize getOutputSize();
    QString getHeading();
    void save(QTextStream &dataStream);
    bool upDateCore(Tensor core);
    Tensor forward(Tensor &input);
    Tensor backward(Tensor &input, double learningSpeed);
private:
    Tensor *_lastInput = nullptr;
    TensorSize _size;
    int _id;
    double func(double input);
    double derFunc(double input);
};

#endif // ACTIVATIONLAYER_H
