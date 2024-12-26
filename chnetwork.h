#ifndef CHNETWORK_H
#define CHNETWORK_H
#include "convlayer.h"
#include "maxpoolinglayer.h"
#include <QDebug>
//#include "numberrecognizer.h"
#include "heronfield.h"

enum LayerType{
    CONV,MXPOOL
};
struct LayerData
{
    LayerType mType;
    TensorSize mOutputSize;
    TensorSize mInputSize;
    //LayerData(LayerType type, TensorSize input, TensorSize output);

};
class CHNetwork
{
public:
//    const int IMAGE_WIDTH;
//    const int IMAGE_HEIGHT;
    CHNetwork(int width, int height);
    QList<double> calculateOutput(QList<QList<double>> inputMatrix);
    //void makeLearningStep();
    void learningStep(QList<double> correctOutput, double learningSpeed);
    void setLastFilter(HeronField * lastFilter);
//    QList<Forwarded *> layers() const;
//    QList<Forwarded *>* pointerToLayers();

    //void reconstructWhithLayersData(QList<LayerData> data);
    void reconstructWithLayersData(QList<LayerData> data);
    void setFilters(QList<Tensor> filters);
    QList<ConvLayer *> convLayers() const;
    HeronField* getLastLayer();
    QList<MaxPoolingLayer *> maxPoolLayers() const;

protected:
    Tensor fromQListToTensor(QList<double> list, TensorSize size);
private:
    //ist<Forwarded*> _layers;

    QList<ConvLayer*> _convLayers;
    QList<MaxPoolingLayer*> _maxPoolLayers;
    Forwarded *_lastMatrixLayer;

    HeronField _lastLayer = HeronField(QList<int>({1,1}));

    QList<double> matrixToQList(QList<QList<double> > matrix);
    QList<double> tensorToQList(Tensor tensor);


    int updateLastMatrixLayer();
};
QDebug operator<<(QDebug debug, const CHNetwork &tensor);


QDebug operator<<(QDebug debug, const LayerData &data);
QDebug operator<<(QDebug debug, const QList<LayerData> &data);

#endif // CHNETWORK_H
