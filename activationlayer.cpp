#include "activationlayer.h"
#include <math.h>
ActivationLayer::ActivationLayer(TensorSize size, int id):_size(size), _id(id)
{

}

bool ActivationLayer::isNeedSaving()
{
    return false;
}

int ActivationLayer::getId()
{
    return _id;
}

TensorSize ActivationLayer::getInputSize()
{
    return _size;
}

TensorSize ActivationLayer::getOutputSize()
{
    return _size;
}

QString ActivationLayer::getHeading()
{
    return QString("ActivationLayer_size_" + _size.exportToString() + "->" + _size.exportToString() + ";");
}

void ActivationLayer::save(QTextStream &dataStream)
{
}

bool ActivationLayer::upDateCore(Tensor core)
{
    return false;
}

Tensor ActivationLayer::forward(Tensor &input)
{
    if (!(input.mSize == _size)){
        qDebug() << "ActivationLayer::forward(...): bad input size!" << input.mSize.exportToString();
    }
    if (_lastInput != nullptr){
        delete _lastInput;
    }
    _lastInput = input.copy();
    Tensor result(_size);
    for (int d = 0 ; d < _size.depth; d++){
        for (int y =0; y < _size.height; y++){
            for (int x = 0; x < _size.width; x++){
                result.set (x,y,d,func(input.get(x,y,d,"Activation forward" )),"Activation forward" );
            }
        }
    }
    return result;
}

Tensor ActivationLayer::backward(Tensor &input, double learningSpeed)
{
    if (!(input.mSize == _size)){
        qDebug() << "ActivationLayer::backward(...): bad input size!" << input.mSize.exportToString();
    }
    Tensor result(_size);
    for (int d = 0; d < _size.depth; d++){
        for(int y = 0; y < _size.height; y++){
            for (int x = 0; x < _size.width; x++){
                result.set(x,y,d, input.get(x,y,d,"Activation backward")*derFunc(_lastInput->get(x,y,d,"Activation Backward")));
            }
        }
    }
    return result;
}

double ActivationLayer::func(double input)
{
    return input/(1+fabs(input));
}
double ActivationLayer::derFunc(double input){
    return 1/((1+fabs(input))*(1+fabs(input)));
}
