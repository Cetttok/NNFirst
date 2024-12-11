#ifndef CHFLAYER_H
#define CHFLAYER_H
#include <QList>

class CHFLayer
{
public:
    CHFLayer(int inputSize, int outputSize);
    //QList<QList<double>>mCore;
    int mInputSize;
    int mOutputSize;
    virtual QList<QList<double>> calculateOutput(QList<QList<double>> input){
        return input;
    }

    QList<QList<double> > getCellsUnderCursor(int x, int y, int size, QList<QList<double> > &map);
protected:
    //QList<QList<double> > getCellsUnderCursor(int x, int y, int size);
};
class CHFConvolutionalLayer: public CHFLayer
{
public:
    CHFConvolutionalLayer(int size, int cursorSize);
    QList<QList<double>> mCore;
    QList<QList<double>> calculateOutput(QList<QList<double>> input);
    //double fListSummationSum(QList<double> list);
    double fListSummation(QList<QList<double> > &list);
    //double fListSummation(QList<double> &list);

    QList<QList<double> > pairedMultyply(QList<QList<double> > &a, QList<QList<double> > &b);
};
class CHFSubsamplingLayer : public CHFLayer{
public:
    CHFSubsamplingLayer(int size, double scale = 0.5);
    double fMaxPool(QList<double> input);
    QList<QList<double>> calculateOutput(QList<QList<double>> input);
    int mCoreSize = 2;
};
#endif // CHFLAYER_H
