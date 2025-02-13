#ifndef BASELAYER_H
#define BASELAYER_H
#include "tensor.h"

class BaseLayer
{
public:
    virtual bool isNeedSaving() = 0;
    virtual int getId() = 0;
    virtual TensorSize getInputSize() = 0;
    virtual TensorSize getOutputSize() = 0;
    virtual QString getHeading() = 0;
    virtual void save(QTextStream &dataStream) = 0;
    virtual bool upDateCore(Tensor core) = 0;
    virtual Tensor forward(Tensor &input) = 0;
    virtual Tensor backward(Tensor &input, double learningSpeed) = 0;
};

#endif // BASELAYER_H
