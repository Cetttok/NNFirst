#ifndef MAXPOOLINGLAYER_H
#define MAXPOOLINGLAYER_H

#include "baselayer.h"
#include "tensor.h"
class MaxPoolingLayer : public BaseLayer
{
public:
    MaxPoolingLayer(TensorSize size, int scale, int id);
    int getId();
    TensorSize getInputSize();
    TensorSize getOutputSize();
    QString getHeading();
    void save(QTextStream &dataStream);
    bool upDateCore(Tensor core);
    Tensor forward(Tensor &input);
    Tensor backward(Tensor &input, double learningSpeed);
    bool isNeedSaving();

    //Tensor* forward(Tensor *inputTensor, bool isSaveInputs = true);
    //int getId();
//    TensorSize getOutputSize();
//    TensorSize getInputSize();
    void debug(QDebug &debug);
//    Tensor backward(Tensor &inputErrors, double learningSpeed);
//    Tensor forward(Tensor &inputTensor);
private:
    int _id;
    int _scale;
    TensorSize mInputSize;
    TensorSize mOutputSize;
    Tensor _maskOfMaximums;
};

#endif // MAXPOOLINGLAYER_H
