#ifndef TENSOR_H
#define TENSOR_H
#include <QVector>
#include <QDebug>
struct TensorSize
{
    int width=0;
    int height=0;
    int depth=0;
    TensorSize(int w, int h, int d){
        width = w;
        height = h;
        depth = d;
    }
    TensorSize(){
        width = 0;
        height = 0;
        depth = 0;
    }

};

class Tensor
{
private:
    QList<QList<QList<double>>> _values;

public:
    Tensor(int width, int height, int depth);
    Tensor(TensorSize size);
    QString toQStringSize() const;
    TensorSize mSize;
    QList<QList<double>> getMatrix(int z);
    void set(int x,int y,int z, double value, QString log = "null");
    void setMatrix(int z, QList<QList<double>> list);
    double get(int x,int y,int z, QString log ="null") const;
    void augment(int x, int y, int z, double value, QString log = "null");
    Tensor *copy();

    //QDebug &QDebug::operator<<(bool t);
    //QDebug operator<< (QDebug &debug) const;

};
QDebug operator<<(QDebug debug, const Tensor &tensor);
QDebug operator<<(QDebug debug, const TensorSize &tensorSize);

class Forwarded // and backwarded
{
public:
    virtual Tensor forward(Tensor &inputTensor, bool isSaveInputs = true) = 0;
    virtual Tensor backward(Tensor &inputErrors, double learningSpeed) = 0;
    virtual void upDateCore(Tensor  newCore) = 0;
    virtual TensorSize getOutputSize() = 0;
    virtual TensorSize getInputSize() = 0;
    virtual void debug(QDebug &debug) = 0;
    //TensorSize mOutputSize;
    //TensorSize mInputSize;

};

#endif // TENSOR_H
