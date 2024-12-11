#include "chflayer.h"
#include <QRandomGenerator>
#include <qDebug>
CHFLayer::CHFLayer(int inputSize, int outputSize)
{
   mInputSize = inputSize;
   mOutputSize = outputSize;
}

CHFConvolutionalLayer::CHFConvolutionalLayer(int size,int cursorSize):CHFLayer(size,size)
{
    for (int y = 0; y < cursorSize; y++){
        mCore.append(QList<double>());
        for (int x = 0; x < cursorSize; x++){
            mCore[y].append(QRandomGenerator::system()->bounded(-1,1));
        }
    }
}

double CHFConvolutionalLayer::fListSummation(QList<QList<double> > &list)
{
    double result = 0;
    for (QList<double> &layer: list){
        for(double &component : layer){
            result += component;
        }
    }
    return result;
}

//double CHFConvolutionalLayer::fListSummation(QList<double> &list)
//{
//    double result = 0;
//    for (double &component : list){
//        result+= component;
//    }
//    return result;
//}
QList<QList <double>> CHFConvolutionalLayer::calculateOutput(QList<QList<double> > input){
    qDebug() << "inputed";
    QList<QList<double>> result = QList<QList<double>>();
    for (int y =0; y<input.size();y++){
        result.append(QList<double>());
        for (int x =0; x< input[y].size();x++){
            QList<QList<double>> cellsFromCursur  =  getCellsUnderCursor(x,y,mCore.size(),input);
            QList<QList<double>> cellsPaired =   pairedMultyply(cellsFromCursur,mCore);
            result[y].append(
                        fListSummation(
                            cellsPaired
                        ));
        }
    }
    qDebug() << "outputed";
    return result;
}
QList<QList<double>> CHFConvolutionalLayer::pairedMultyply(QList<QList<double> > &a, QList<QList<double> > &b){
    QList<QList<double>> result = QList<QList<double>>();
    for (int i = 0; i< a.size(); i++){
        result.append(QList<double>());
        for (int ii = 0; ii< a.size(); ii++){
            result[i].append(a[i][ii]*b[i][ii]);
        }
    }
    return result;

}
QList<QList<double>> CHFLayer::getCellsUnderCursor(int x,int y, int size, QList<QList<double>> &map){

    QList<QList<double>> result = QList<QList<double>>();
    for (int dY = -size/2; y < size/2; y++){
        result.append(QList<double>());
        for (int dX  = -size/2; x < size/2; x++){
            if (y+ dY < 0 || y+dY >=  map.size()){
                result[y].append(0.0);
            }
            else{
                if(x+dX < 0|| x+dX >= map[y].size()){
                    result[y
                            ].append(0.0);
                }
                else{
                    result[y].append(map[y+dY][x+dX]);
                }
            }

        }
    }
    return result;
}






CHFSubsamplingLayer::CHFSubsamplingLayer(int size, double scale):CHFLayer(size,size*scale)
{

}

double CHFSubsamplingLayer::fMaxPool(QList<double> input)
{
    double max = input.first();
    for (double& num :  input){
        if (max < num ){
            max = num;
        }
    }
    return max;
}
QList<QList<double>> CHFSubsamplingLayer::calculateOutput(QList<QList<double> > input){
    QList<QList<double>> result = QList<QList<double>>();
    for (int y = 0; y< input.size()-mCoreSize/2; y+=mCoreSize){
        result.append(QList<double>());
        for (int x = 0; x < input.size()-mCoreSize/2; x=+mCoreSize){
            result[y].append(fMaxPool(QList<double>({input[y][x],input[y][x+1],
                                                     input[y+1][x],input[y+1][x+1]})));
        }
    }
    return result;
}
