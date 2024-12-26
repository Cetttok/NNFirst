#ifndef CONVLAYER_H
#define CONVLAYER_H
#include "tensor.h"

class ConvLayer : public Forwarded
{
public:
    ConvLayer(TensorSize inputSize, TensorSize outputSize, int filterSize, int filterCount);

    Tensor forward(Tensor &inputTensor);
    TensorSize mInputSize;
    void updateWeightsOfFilters(double learningSpeed);
    TensorSize mOutputSize;
    Tensor backward(Tensor &inputDeltas, double learningSpeed);

    TensorSize getOutputSize();
    TensorSize getInputSize();
    void debug(QDebug &debug);
    Tensor getFilters();
    void upDateCore(Tensor newCore);
    Tensor * _filtersGradients = nullptr;
    Tensor _filter;
private:
    Tensor * _lastInputTensor = nullptr;

    double pairedMultyply(QList<QList<double> > &a, QList<QList<double> > &b);

    int _filtersCount; // количество фильтров
    int _filtersSize; // размер фильтров

    QList<QList<double> > getCellsUnderFilter(QList<QList<double> > &filter, QList<QList<double> > &field, int x, int y);
};

#endif // CONVLAYER_H
