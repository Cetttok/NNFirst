#ifndef MAXPOOLINGLAYER_H
#define MAXPOOLINGLAYER_H

#include "tensor.h"
class MaxPoolingLayer : public Forwarded
{
public:
    MaxPoolingLayer(TensorSize size, int scale = 2);
    TensorSize mInputSize;
    int _scale;

    TensorSize mOutputSize;
    //Tensor* forward(Tensor *inputTensor, bool isSaveInputs = true);
    TensorSize getOutputSize();
    TensorSize getInputSize();
    void debug(QDebug &debug);
    Tensor backward(Tensor &inputErrors, double learningSpeed);
    Tensor forward(Tensor &inputTensor, bool isSaveInputs);
private:
    Tensor _maskOfMaximums;
};

#endif // MAXPOOLINGLAYER_H
