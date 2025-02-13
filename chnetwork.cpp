#include "activationlayer.h"
#include "chnetwork.h"
#include <QDebug>
CHNetwork::CHNetwork(int width, int height)//:/*IMAGE_HEIGHT(height),IMAGE_WIDTH(width)*/
{
//    _layers.append(new ConvLayer(TensorSize(IMAGE_WIDTH,IMAGE_WIDTH,1),
//                             TensorSize(IMAGE_WIDTH-2,IMAGE_HEIGHT-2,2),3,4));
//    _layers.append(new MaxPoolingLayer(TensorSize(IMAGE_WIDTH-2,IMAGE_HEIGHT-2,4)));
//        _layers.append(new ConvLayer(TensorSize(8,8,1),
//                                 TensorSize(6,6,4),3,4));
//        _layers.append(new MaxPoolingLayer(TensorSize(6,6,4)));
//    int baseSize = _layers.last()->getOutputSize().width*
//            _layers.last()->getOutputSize().height*
//            _layers.last()->getOutputSize().depth;
//    _lastLayer = HeronField(QList<int>({baseSize,baseSize*0.5,10}));
//    qDebug() << "CHNetwork::CHNetwork(...) Created! Size: ";
//    for (Forwarded *layer : _layers){
////        qDebug() << "Layer: size(" << layer->getOutputSize().width<<"*" << layer->getOutputSize().height <<
////                    ") depth(" << layer->getOutputSize().depth<<")";
        
//    qDebug() << "Layer: size(" << layer->getOutputSize().width<<"*" << layer->getOutputSize().height <<
//        ") depth(" << layer->getOutputSize().depth<<")";

//    }

    //layers.append(new MaxPoolingLayer(TensorSize(8,8,1), 2, 0));
    //_layers.append(new ConvLayer(TensorSize(4,4,1), TensorSize(2,2,8), 3, 8,1));
    //_layers.append(new ConvLayer(TensorSize(8,8,1),
    //                         TensorSize(6,6,4),3,4, _layers.size()));
   // _layers.append(new ActivationLayer(TensorSize(6,6,4),_layers.size()));
    // _layers.append(new ConvLayer(TensorSize(6,6,4),TensorSize(4,4,8),3,2,_layers.size()));
    //_layers.append(new MaxPoolingLayer(TensorSize(6,6,4),2,_layers.size()));
    //_layers.append(new MaxPoolingLayer(TensorSize(4,4,8),2,_layers.size()));

//    _layers.append(new ConvLayer(TensorSize(28,28,1),TensorSize(22,22,4),7,4,0));
//    _layers.append(new MaxPoolingLayer(TensorSize(22,22,4), 2,1));
//    _layers.append(new ConvLayer(TensorSize(11,11,4), TensorSize(7,7,16), 5,4,2));
//    _layers.append(new ConvLayer(TensorSize(7,7,16), TensorSize(1,1,64),7,4,3));

    //1 config
    _layers.append(new MaxPoolingLayer(TensorSize(28,28,1),2,0));
    _layers.append(new ConvLayer(TensorSize(14,14,1), TensorSize(12,12,4),3,4,1));
    _layers.append(new MaxPoolingLayer(TensorSize(12,12,4),2,3));
    _layers.append(new ConvLayer(TensorSize(6,6,4),TensorSize(4,4,8),3,2,4));
////
    int baseSize = getBaseSize();

    _lastLayer = HeronField(QList<int>({baseSize,int(baseSize*0.5),10}));
    qDebug() << "CHNetwork::CHNetwork(...) Created! Size: ";
    //for (Forwarded *layer : _layers){
//        qDebug() << "Layer: size(" << layer->getOutputSize().width<<"*" << layer->getOutputSize().height <<
//                    ") depth(" << layer->getOutputSize().depth<<")";

//    qDebug() << "Layer: size(" << layer->getOutputSize().width<<"*" << layer->getOutputSize().height <<
//        ") depth(" << layer->getOutputSize().depth<<")";

//    }

}
int CHNetwork::getBaseSize(){


    return _layers.last()->getOutputSize().width*
                _layers.last()->getOutputSize().height*
                _layers.last()->getOutputSize().depth;


}
void CHNetwork::setFilters(QList<Tensor> filters){
    //qDebug() << data.size();

    for (BaseLayer * layer : _layers){
        if (layer->upDateCore(filters.first())){
            filters.removeFirst();
            if(filters.isEmpty()){
                break;
            }
        }

    }
}
void CHNetwork::reconstructWithLayersData(QList<LayerData> data){
    if (data.size() == 0){
        qDebug() << "CHNetwork::reconstructWithLayersData(...): Bad Data because her size == 0";
        return;
    }
    _layers.clear();
    //_maxPoolLayers.clear();
    for (LayerData &layer: data){
        if (layer.mType == LayerType::CONV){
            _layers.append(new ConvLayer(layer.mInputSize, layer.mOutputSize, layer.mInputSize.width - layer.mOutputSize.width + 1,layer.mOutputSize.depth/layer.mInputSize.depth , _layers.size()));
        }
        else if (layer.mType == LayerType::MXPOOL){
            _layers.append(new MaxPoolingLayer(layer.mInputSize,2, _layers.size()));
        }
        else if (layer.mType == LayerType::ACTIV){
            _layers.append(new ActivationLayer(layer.mInputSize,_layers.size()));
        }

    }
    int baseSize = getBaseSize();
    _lastLayer = HeronField(QList<int>({baseSize,int(baseSize*0.5),10}));
}
QList<double> CHNetwork::calculateOutput(QList<QList<double> > inputMatrix)
{
    //qDebug() << "double CHNetwork::calculateOutput(...): Starting calculating...";

    Tensor input = Tensor(_layers.first()->getInputSize());
    //qDebug() << input;
    input.setMatrix(0,inputMatrix);
    //qDebug() << input;
    Tensor  activeTensor = input;

    for (int i = 0; i < _layers.size(); i++){
//        if (_convLayers.size() > i){
//            activeTensor = _convLayers[i]->forward(activeTensor);
//        }
//        if (_maxPoolLayers.size() > i){
//            activeTensor = _maxPoolLayers[i]->forward(activeTensor);
//        }
        activeTensor = _layers[i]->forward(activeTensor);
        //qDebug() << "double CHNetwork::calculateOutput(...): layer has been calculated!";
    }
    //qDebug() << "double CHNetwork::calculateOutput(...): Nice! All tensors has been caluclulated!";
    //qDebug() << *activeTensor;
    //double result = [0];
    //qDebug() << "double CHNetwork::calculateOutput(...): Perfect! Result has been calculated: " << result;
    //delete input;
    return _lastLayer.calculateOutput(tensorToQList(activeTensor));

}
void CHNetwork::learningStep(QList<double> correctOutput, double learningSpeed){
//    if (_maxPoolLayers.size() >= _convLayers.size()){

//    }
    Tensor inputs = fromQListToTensor(_lastLayer.makeLearningStep(correctOutput,learningSpeed,learningSpeed*1.5), _layers.last()->getOutputSize());
    //qDebug() << "void CHNetwork::learningStep(...): last layer bakcwareded and changed weights";
    //qDebug() <<inputs;
    for (int layer = _layers.size()-1; layer >=0; layer --){
        inputs = _layers[layer]->backward(inputs, learningSpeed);
        //qDebug() << inputs;
    }
    //qDebug() << "void CHNetwork::learningStep(...): learning StepMaked";

}

void CHNetwork::setLastFilter(HeronField *lastFilter)
{
    _lastLayer  = *lastFilter;

}
QDebug operator<<(QDebug debug, const CHNetwork &net){
//    debug << "CHNetwork(" <<  net.layers().size() << ");" << endl;
//    for (int i  = 0; i < ){

//        layer->debug(debug);
//       // qDebug() << "normaly";
//    }
    return debug;
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

QList<BaseLayer *> CHNetwork::getLayers() const
{
    return _layers;
}

//QList<MaxPoolingLayer *> CHNetwork::maxPoolLayers() const
//{
//    return _maxPoolLayers;
//}

//QList<ConvLayer *> CHNetwork::convLayers() const
//{
//    return _convLayers;
//}

HeronField *CHNetwork::getLastLayer()
{
    return &_lastLayer;
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

//LayerData::LayerData(LayerType type, TensorSize input, TensorSize output):mType(type),
//    mInputSize(input), mOutputSize(output)
//{

//}

QDebug operator<<(QDebug debug, const LayerData &data)
{

    if (data.mType == LayerType::CONV){
        debug << "ConvLayer:" << data.mInputSize << "->"<<data.mOutputSize;
    }
    else if (data.mType == LayerType::MXPOOL){
        debug << "MaxPool:" << data.mInputSize << "->"<<data.mOutputSize;
    }
    else{
        debug << "udefinded type";
    }
    return debug;
}

QDebug operator<<(QDebug debug, const QList<LayerData> &data)
{
    debug << "LayerData("<< data.size()<<"){";
    for (const LayerData &el : data){
        debug << endl<< el;

    }
    debug << "};";
}
