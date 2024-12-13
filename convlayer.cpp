#include "convlayer.h"
#include <QRandomGenerator>
#include <qDebug>
ConvLayer::ConvLayer(TensorSize inputSize,TensorSize outputSize,int filterSize, int filterCount):
    mInputSize(inputSize),
    mOutputSize(outputSize),
    _filter(Tensor(filterSize,filterSize,filterCount))
{
    qDebug() << "ConvLayer::ConvLayer start creating..." << endl;
    //_inputSize = size;
    //_outputSize = ;
    //_filter = Tensor(_filtersSize,_filtersSize,_filtersCount);
//    for (int filterNum = 0; filterNum < _filtersCount; _filtersCount++){
//        _filters.append(Tensor());
//    }
    //qDebug() << _filter.mSize.depth<<_filter.mSize.height<<_filter.mSize.width;
    for(int z = 0; z < _filter.mSize.depth; z++) {
        for ( int y = 0; y < _filter.mSize.height; y++){
            //qDebug () << z << y;
            for (int x = 0; x < _filter.mSize.width; x++){
                //qDebug() << z << y << x;
                _filter.set(x,y,z,QRandomGenerator::global()->bounded(2.0)-1.0);//QRandomGenerator::global()->bounded(5.0)-2.5
            }
        }
    }
    _filtersGradients = new Tensor(TensorSize(filterSize,filterSize, filterCount));
    _filtersSize = filterSize;
    _filtersCount = filterCount;
    qDebug() << "ConvLayer::ConvLayer(...): input size" << mInputSize.width << mInputSize.height << mInputSize.depth;
    qDebug() << "ConvLayer::ConvLayer(...): output size " << mOutputSize.width << mOutputSize.height << mOutputSize.depth;
    qDebug() << "ConvLayer::ConvLayer created! :)" <<endl;


}
TensorSize ConvLayer::getOutputSize(){
    return mOutputSize;
}

TensorSize ConvLayer::getInputSize()
{
    return mInputSize;
}

void ConvLayer::debug(QDebug &debug)
{
    debug << "Convlayer (" << mInputSize.width << mInputSize.height << mInputSize.depth<<") -> ("
          << mOutputSize.width << mOutputSize.height << mOutputSize.depth << ")" << endl;
    debug << _filter;
}
Tensor ConvLayer::forward(Tensor& inputTensor, bool isSaveInputs)
{
    //qDebug()<<
    int cheack = 0;
    int filterRadius = (_filter.mSize.width-1)/2;

    if(filterRadius < 1){
        qDebug() << "Tensor *ConvLayer::forward(...) WHat! Why filter rasius = " << filterRadius;
    }
    else{
        //qDebug() << "Tensor *ConvLayer::forward(...) filterRadius = " << filterRadius;
    }

    //qDebug() << "Tensor *ConvLayer::forward(Tensor *inputTensor):";
    //qDebug() <<  "inputTesnor "<<inputTensor->toQStringSize();
    //qDebug() << "_filter " << _filter.toQStringSize();
    Tensor result = Tensor(mOutputSize);
    //qDebug() << _filter.mSize.width << _filter.mSize.height << _filter.mSize.depth;
    for (int i = 0; i< _filter.mSize.depth; i++ ){ // evry filter
        //qDebug() <<"Tensor *ConvLayer::forward(...) by new filter" << i ;
        for (int z =0; z < inputTensor.mSize.depth; z++){ // every input matrix
            //qDebug() <<"z = " << z;
            QList<QList<double>> lfilter = _filter.getMatrix(i);
            QList<QList<double>> inputMatrix = inputTensor.getMatrix(z);

            for (int y = filterRadius; y < inputTensor.mSize.height-filterRadius; y++){ // every layer
                //qDebug() << "y = " << y;
                for (int x = filterRadius; x < inputTensor.mSize.width-filterRadius; x++){ // every cell
                    //qDebug() << "x = " << x;
                    double sum = 0; // можно добавить смешение

                    QList<QList<double>> underFilter = getCellsUnderFilter(lfilter,inputMatrix,x,y);
                    sum+= pairedMultyply(underFilter, lfilter);
                    //sum+= pairedMulytply(getCellsUnderFilter(&_filter[i],&inputTensor[z],x,y), &_filter);
                    //qDebug() <<"sum = "<<    sum;
                    result.set(x-filterRadius,y-filterRadius,i,sum);
                    cheack++;

                }
                //qDebug() << 1;
            }
            //qDebug() <<2;
        }
        //qDebug() << 3;

    }
    if (true){
        delete _lastInputTensor;
        _lastInputTensor = inputTensor.copy();
        //delete inputTensor;
        //qDebug() << "Tensor *ConvLayer::forward(...) input saved." << _lastInputTensor->toQStringSize();
    }
    //qDebug() << "Tensor *ConvLayer::forward(...) forward ended sucsessfuul!";
    //qDebug() << *result;
    return result;
}

void ConvLayer::updateWeightsOfFilters(double learningSpeed)
{
    for (int filter = 0; filter < _filter.mSize.depth; filter++){
        for (int  y = 0; y < _filter.mSize.height; y++){
            for (int x = 0; x < _filter.mSize.width; x++){
                _filter.augment(x,y,filter,_filtersGradients->get(x,y,filter,QString("UpDate weights"))* (-learningSpeed), QString("UpDate weights"));
                _filtersGradients->set(x,y,filter,0, QString("UpDate weights, clear gradients"));
            }
        }
    }
    //qDebug() << "void ConvLayer::updateWeightsOfFilters(...): DONE! :| all weights for all filters upDated!";
}

Tensor ConvLayer::backward(Tensor &inputDeltas, double learningSpeed)
{
    
     // размер дельт

    // расчитываем размер для дельт
    //qDebug() << _lastInputTensor;
    //qDebug() << _lastInputTensor->toQStringSize() << _lastInputTensor->get(0,0,0);
    if (_lastInputTensor ==  nullptr){
        qDebug() << "Tensor ConvLayer::backward(...): Ta-dam! Please make calulating step before!";
        return Tensor(0,0,0);
    }
    int filterRadious = (_filtersSize-1)/2;

    Tensor deltas(mOutputSize); // создаём тензор для дельт

    // расчитываем значения дельт
    for (int d = 0; d < mOutputSize.depth; d++){
        for (int i = 0; i < mOutputSize.height; i++){
            for (int j = 0; j < mOutputSize.width; j++){
                deltas.set(j,i,d, inputDeltas.get(j,i,d));
                //qDebug() << inputDeltas.get(j,i,d);
            }
        }
    }
    //qDebug() << _lastInputTensor;
    //qDebug() << "Tensor ConvLayer::backward(...): setted.";
    for (int z = 0; z < _filtersCount; z++) {
        //qDebug() << "Tensor ConvLayer::backward(...): new filter!";
        for (int y = 0; y < mOutputSize.height; y++) {
            for (int x = 0; x < mOutputSize.width; x++) {// every cell
                //qDebug() << z << y << x;

                double delta = inputDeltas.get(x, y, z, QString("starting Weighs")); // запоминаем значение градиента
//                if (delta == 0){
//                    qDebug() << "Tensor ConvLayer::backward(...): delta is 0! x, y,z - " <<x<<y<<z;
//                }


                for (int dX = -filterRadious; dX < filterRadious+1; dX++) { //по всему фильтру высота
                    for (int dY = -filterRadious; dY < filterRadious+1; dY++) { // по весму фильтру ширина

                        // игнорируем выходящие за границы элементы
                        if (x+dX < 0 || x+dX >= mInputSize.height || y+dY< 0 || y+dY >= mInputSize.width){

                        }//провести

                            //qDebug() << "continue" << dY << dX;
                        else{
                            //qDebug() <<;

                            for (int d = 0 ; d < mInputSize.depth; d++) {
                                //qDebug() << _lastInputTensor;
                                _lastInputTensor->get(x+dX, y+dY, d, QString("Weights"));
                                double value = delta* _lastInputTensor->get(x+dX, y+dY, d, QString("Weights"));
                                _filtersGradients->augment(dX+filterRadious, dY+filterRadious, z,value);
                            }


                        }

                        // наращиваем градиент фильтра

                        // input * входной градиент
                    }
                }
            }
        }
    }
    //qDebug() << "Tensor ConvLayer::backward(...): weight gradients maked" << _filtersGradients->toQStringSize();




    int pad = _filtersSize - 1; // заменяем величину дополнения
    Tensor inputGradienst(mInputSize); // создаём тензор градиентов по входу

    // расчитываем значения градиента

    for(int z = 0; z < mInputSize.depth; z++){


        for (int y = 0; y < mInputSize.height; y++) {
            for (int x = 0; x < mInputSize.width; x++) {

               double sum = 0; // сумма для градиента

               // идём по всем весовым коэффициентам фильтров
               for (int i = 0; i < _filtersSize; i++) {
                   for (int j = 0; j < _filtersSize; j++) {
                       int i0 = y + i - pad;
                       int j0 = x + j - pad;

                       // игнорируем выходящие за границы элементы
                       if (i0 < 0 || i0 >= mOutputSize.height || j0 < 0 || j0 >= mOutputSize.width){
                           continue;}

                       // суммируем по всем фильтрам
                       for (int f = 0; f < _filtersCount; f++){
                           sum += _filter.get(_filtersSize - 1 - j,_filtersSize - 1 - i, f,QString("InputGradient")) * inputDeltas.get(j0, i0, f, QString("InputGradient")); // добавляем произведение повёрнутых фильтров на дельты
                            //qDebug() <<"geted"<< inputDeltas.get(j0, i0, f, QString("InputGradient"));
                       }
                   }

               }

               inputGradienst.set(x, y, z,sum); // записываем результат в тензор градиента

            }
        }
    }




    updateWeightsOfFilters(learningSpeed);

    return inputGradienst; // возвращаем тензор градиентов

}
QList<QList<double>>   ConvLayer::getCellsUnderFilter(QList<QList<double>> &filter, QList<QList<double>> &field, int x, int y)
{
    if (filter.size() != filter[0].size()){
        qDebug() << "QList<QList<double>>   ConvLayer::getCellsUnderFilter(...) ERROR: filter is not square!";
        return QList<QList<double>>();
    }
    if(filter.size() < 3 | filter.size()&2 == 0){
        qDebug() << "QList<QList<double>>   ConvLayer::getCellsUnderFilter(...) ERROR: filter is very small or even!";
        return QList<QList<double>>();
    }
    QList<QList<double>> result;
    int filterRadius = (filter.size()-1)/2;
    for (int i = -filterRadius; i <= filterRadius; i++){
        result.append(QList<double>());
        for (int ii = -filterRadius; ii <= filterRadius; ii++){
            if (y + i >= 0 && x + ii >=0){
                if (y + i < field.size() && x+ ii < field[y+i].size() ){
                    result.last().append(field[y+i][x+ii]);
                }
                else{
                    result.last().append(0);
                }
                
            }
            else{
                result.last().append(0);
            }
        } 
    }
    //qDebug() << "QList<QList<double>>   ConvLayer::getCellsUnderFilter(...): result.size: y = " << result.size() << "x = " << result.first().size();
    return result;
}
double ConvLayer::pairedMultyply(QList<QList<double>> &a, QList<QList<double>> &b){
    
    if (a.size() != b.size()){
        qDebug() << "double ConvLayer::pairedMultyply(...) ERROR: y size dont same!";
        return 0;
    }
    if (a.first().size() != b.first().size()){
        qDebug() << "double ConvLayer::pairedMultyply(...) ERROR: first x size dont same!";
        return 0;
    }
    double sum = 0;
    int sizeY = a.size();
    int sizeX = a.first().size();
    for (int y = 0; y < sizeY; y++){
        for (int x = 0; x < sizeX; x++){
            sum+= a.at(y).at(x) * b.at(y).at(x);
        }
    } 
    return sum;
}
