#include "chnetwork.h"
#include <qDebug>
CHNetwork::CHNetwork(int width, int height):IMAGE_HEIGHT(height),IMAGE_WIDTH(width)
{
    _layers.append(new ConvLayer(TensorSize(IMAGE_WIDTH,IMAGE_WIDTH,1),
                             TensorSize(IMAGE_WIDTH-2,IMAGE_HEIGHT-2,2),3,2));
    _layers.append(new MaxPoolingLayer(TensorSize(IMAGE_WIDTH-2,IMAGE_HEIGHT-2,2)));
    int baseSize = _layers.last()->getOutputSize().width*
            _layers.last()->getOutputSize().height*
            _layers.last()->getOutputSize().depth;
    _lastLayer = HeronField(QList<int>({baseSize,baseSize,1}));
    qDebug() << "CHNetwork::CHNetwork(...) Created! Size: ";
    for (Forwarded *layer : _layers){
//        qDebug() << "Layer: size(" << layer->getOutputSize().width<<"*" << layer->getOutputSize().height <<
//                    ") depth(" << layer->getOutputSize().depth<<")";
        
    qDebug() << "Layer: size(" << layer->getOutputSize().width<<"*" << layer->getOutputSize().height <<
        ") depth(" << layer->getOutputSize().depth<<")";
    
    }

}

double CHNetwork::calculateOutput(QList<QList<double> > inputMatrix)
{
    qDebug() << "double CHNetwork::calculateOutput(...): Starting calculating...";
    Tensor *input = new Tensor(IMAGE_WIDTH, IMAGE_HEIGHT,1);
    input->setMatrix(0,inputMatrix);
    Tensor * activeTensor = input;
    for (Forwarded * layer : _layers){
        activeTensor = layer->forward(activeTensor);
        qDebug() << "double CHNetwork::calculateOutput(...): layer has been calculated!";
    }
    qDebug() << "double CHNetwork::calculateOutput(...): Nice! All tensors has been caluclulated!";
    qDebug() << *activeTensor;
    double result = _lastLayer.calculateOutput(tensorToQList(*activeTensor))[0];
    qDebug() << "double CHNetwork::calculateOutput(...): Perfect! Result has been calculated: " << result;
    return result;

}
void CHNetwork::learningStep(double learningSpeed, QList<double> correctOutput){
    Tensor inputs = fromQListToTensor(_lastLayer.makeLearningStep(correctOutput,learningSpeed,0.0), TensorSize(_layers.first()->getInputSize()));
    qDebug() << "void CHNetwork::learningStep(...): last layer bakcwareded and changed weights";
    qDebug() <<inputs;
    for (Forwarded * layer : _layers){
        inputs = layer->backward(inputs, learningSpeed);
    }
    qDebug() << "void CHNetwork::learningStep(...): learning StepMaked";

}

Tensor CHNetwork::fromQListToTensor(QList<double> list, TensorSize size){
    int element = 0;
    Tensor result = Tensor(size);
    if (list.size() < size.width*size.depth* size.height){
        qDebug() << "Tensor CHNetwork::fromQListToTensor(...): ERROR!! size doesn't match :("
                 << size.width*size.depth* size.height
                 <<"!=" << list.size();
        return result;
    }
    for (int d =0; d < size.depth; d++) {
        for(int y = 0; y < size.height; y++){
            for(int x =0 ; x < size.width; x++){
                result.set(x,y,d,list[element], QString("list to tensor chnetwork"));
                element++;
            }
        }
    }

    return result;
}
QList<double> CHNetwork::tensorToQList(Tensor tensor){
    QList<double> result = QList<double> ();
    for (int z = 0; z < tensor.mSize.depth; z++){
        for (int y = 0 ; y < tensor.mSize.height; y++){
            for(int x =0; x< tensor.mSize.width; x++){
                result.append(tensor.get(x,y,z));
            }
        }
    }
    return result;
}
