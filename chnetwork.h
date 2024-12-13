#ifndef CHNETWORK_H
#define CHNETWORK_H
#include "convlayer.h"
#include "maxpoolinglayer.h"
#include <QDebug>
//#include "numberrecognizer.h"
#include "heronfield.h"
class CHNetwork
{
public:
    const int IMAGE_WIDTH;
    const int IMAGE_HEIGHT;
    CHNetwork(int width, int height);
    double calculateOutput(QList<QList<double>> inputMatrix);
    //void makeLearningStep();
    void learningStep(QList<double> correctOutput, double learningSpeed);

    QList<Forwarded *> layers() const;

protected:
    Tensor fromQListToTensor(QList<double> list, TensorSize size);
private:
    QList<Forwarded*> _layers;
    HeronField _lastLayer = HeronField(QList<int>({1,1}));

    QList<double> matrixToQList(QList<QList<double> > matrix);
    QList<double> tensorToQList(Tensor tensor);

};
QDebug operator<<(QDebug debug, const CHNetwork &tensor);

#endif // CHNETWORK_H
