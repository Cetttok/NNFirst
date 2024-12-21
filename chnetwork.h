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
    const int IMAGE_WIDTH;
    const int IMAGE_HEIGHT;
    CHNetwork(int width, int height);
    QList<double> calculateOutput(QList<QList<double>> inputMatrix);
    //void makeLearningStep();
    void learningStep(QList<double> correctOutput, double learningSpeed);

    QList<Forwarded *> layers() const;

    //void reconstructWhithLayersData(QList<LayerData> data);
    void reconstructWithLayersData(QList<LayerData> data);
    void setFilters(QList<Tensor> filters, QList<LayerData> data);
protected:
    Tensor fromQListToTensor(QList<double> list, TensorSize size);
private:
    QList<Forwarded*> _layers;
    HeronField _lastLayer = HeronField(QList<int>({1,1}));

    QList<double> matrixToQList(QList<QList<double> > matrix);
    QList<double> tensorToQList(Tensor tensor);

};
QDebug operator<<(QDebug debug, const CHNetwork &tensor);


QDebug operator<<(QDebug debug, const LayerData &data);
QDebug operator<<(QDebug debug, const QList<LayerData> &data);

#endif // CHNETWORK_H
