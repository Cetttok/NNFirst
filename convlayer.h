#ifndef CONVLAYER_H
#define CONVLAYER_H
#include "tensor.h"
#include "baselayer.h"
class ConvLayer : public BaseLayer
{
public:
    ConvLayer(TensorSize inputSize, TensorSize outputSize, int filterSize, int filterCount, int id);
    int getId();
    bool isNeedSaving();
    TensorSize getInputSize();
    TensorSize getOutputSize();
    QString getHeading();
    void save(QTextStream &dataStream);
    bool upDateCore(Tensor core);
    Tensor forward(Tensor &input);
    Tensor backward(Tensor &input);
    void debug(QDebug &debug);


//    Tensor forward(Tensor &inputTensor);
//    TensorSize getOutputSize();
//    TensorSize getInputSize();
//    Tensor getFilters();
//    void upDateCore(Tensor newCore);
private:
    int _id;
    TensorSize mInputSize;
    TensorSize mOutputSize;
    Tensor backward(Tensor &inputDeltas, double learningSpeed);
    Tensor _filter;
    Tensor * _filtersGradients = nullptr;
    void updateWeightsOfFilters(double learningSpeed);
    Tensor * _lastInputTensor = nullptr;

    double pairedMultyply(QList<QList<double> > &a, QList<QList<double> > &b);

    int _filtersCount; // количество фильтров
    int _filtersSize; // размер фильтров

    QList<QList<double> > getCellsUnderFilter(QList<QList<double> > &filter, QList<QList<double> > &field, int x, int y);
};

#endif // CONVLAYER_H
