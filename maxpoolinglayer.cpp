#include "maxpoolinglayer.h"

MaxPoolingLayer::MaxPoolingLayer(TensorSize size, int scale):_maskOfMaximums(size)
{
    _scale = scale;
    mInputSize = size;
    mOutputSize = TensorSize(size.width/scale, size.height/scale,size.depth);

}
TensorSize MaxPoolingLayer::getOutputSize(){
    return mOutputSize;
}

TensorSize MaxPoolingLayer::getInputSize()
{
    return mInputSize;
}
void MaxPoolingLayer::debug(QDebug &debug)
{
    debug << "Maxpool (" << mInputSize.width << mInputSize.height << mInputSize.depth<<") -> ("
          << mOutputSize.width << mOutputSize.height << mOutputSize.depth << ")";
    //debug << _filter;
}
Tensor MaxPoolingLayer::backward(Tensor &inputErrors, double learningSpeed){
    //qDebug() << "Tensor MaxPoolingLayer::backward(...) started!";
    Tensor result = Tensor(mInputSize);
    for (int z = 0; z < mInputSize.depth; z++){
        for (int y =0; y < mInputSize.height; y++){
            for(int x = 0; x < mInputSize.width;x++){
                result.set(x,y,z, inputErrors.get(x/_scale,y/_scale,z,QString("maxPool get error"))*
                    _maskOfMaximums.get(x,y,z,QString("maxPool get from mask")),QString("maxPool set value for output"));
            }
        }
    }
    //qDebug() << "Tensor MaxPoolingLayer::backward(...) completed succesfull!";
    return result;
}
Tensor MaxPoolingLayer::forward(Tensor &inputTensor)
{
    Tensor result = Tensor(mOutputSize);
    for (int z = 0; z < mInputSize.depth; z++){
        for(int y = 0; y < mInputSize.height; y+= _scale) {
            for(int x = 0; x <mInputSize.width; x+= _scale){
                double max = inputTensor.get(x,y,z,QString("get first maximun"));
                int maxDX = 0;
                int maxDY = 0;
                for (int dY = 0; dY < _scale; dY++){
                    for (int dX = 0; dX < _scale; dX++){
                        _maskOfMaximums.set(x+dX, y+dY,z,0,QString("Mask set 0"));
                        if (inputTensor.get(x+dX,y+dY,z) > max){
                            max = inputTensor.get(x+dX,dY+y,z);
                            maxDY = dY;
                            maxDX = dX;
                        }
                    }

                }
                _maskOfMaximums.set(x+maxDX, y + maxDY, z,1, QString("Set max mask"));
                result.set(x/2,y/2,z,max);
            }
        }
    }
    //qDebug() << *result;
    return result;
}

