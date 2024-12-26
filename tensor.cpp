#include "tensor.h"
//#include <QDebug>
Tensor::Tensor(int width, int height, int depth): mSize(width,height,depth)
{
    for (int d = 0; d < depth; d++){
        _values.append(QList<QList<double>>());
        for (int h = 0; h < height;h++){
            _values[d].append(QList<double>());
            for (int w = 0; w < width; w++){
                _values[d][h].append(0);
            }
        }
    }
}

Tensor::Tensor(TensorSize size):mSize(size)
{
    for (int d = 0; d < size.depth; d++){
        _values.append(QList<QList<double>>());
        for (int h = 0; h < size.height;h++){
            _values[d].append(QList<double>());
            for (int w = 0; w < size.width; w++){
                _values[d][h].append(0);
            }
        }
    }
}

QString Tensor::toQStringSize() const
{
    return QString("Tensor: size{ width(" + QString::number(mSize.width)+
                              ") height(" + QString::number(mSize.height)+
                              ") depth(" + QString::number(mSize.depth)+")}");

}

QList<QList<double> > Tensor::getMatrix(int z)
{
    if (z >=0 && z< _values.size()){
        return _values[z];
    }
    else{
        qDebug() << "QList<QList<double>> Tensor::getMatrix(int z): ERROR: 'z' = " << z << "not acceptable!";
        return QList<QList<double>>();
    }
}

void Tensor::set(int x, int y, int z, double value, QString log){
    if (z < _values.size() && y < _values[z].size() && x < _values[z][y].size()){
        if (x <0&& y<0 && z < 0 ){
            qDebug()<<log << "ERROR : set invalid z = " << z << "y = "<< y <<"x = "<< x;
            qDebug() << "max size for varies= " << _values.size()-1 << _values[0].size()-1 << _values[0][0].size()-1;
        }
        else{
            _values[z][y][x] = value;
        }
    }
    else{
        qDebug()<< log <<"ERROR : set invalid z = " << z << "y = "<< y <<"x = "<< x;
        qDebug() << "max size for varies= " << _values.size()-1 << _values[0].size()-1 << _values[0][0].size()-1;

    }
}

void Tensor::setMatrix(int z, QList<QList<double> > list)
{
    //qDebug() <<  *this;

    if(z >= 0 && z < _values.size()){
        _values[z] = list;
        //qDebug() <<  *this;
        //qDebug() << "normally";
    }
    else{
        qDebug() << "ERROR set matrix  is invalid!  z = " << z<< "/" << _values.size()-1  << "max legal" ;
    }
}

double Tensor::get(int x, int y, int z, QString log) const
{
//    if (log == QString("Weights")){


//        qDebug() << "svershilos" << this << nullptr;
//        qDebug() << this->toQStringSize();
//        qDebug() << " 1222"<<_values.first().first().first();
//        qDebug() << "values size" << _values.size();
//    }

    if (z < _values.size() && y < _values[z].size() && x < _values[z][y].size()){
        if (x <0&& y<0 && z < 0 ){
            qDebug()<< log << "ERROR: get value is invalid! x/y/z = 0? What it mean?" << z << y << x;
            }
        else{
            return _values[z][y][x];
        }
    }
    else{
        qDebug() << log <<"ERROR: get value is  invalid! z = " << z << "y = "<< y <<"x = "<< x;
        qDebug() << "max size for varies= " << _values.size()-1 << _values[0].size()-1 << _values[0][0].size()-1;
        return 0;
    }

}

void Tensor::augment(int x, int y, int z, double value, QString log)
{
    //qDebug() << log <<"augment";
    set(x,y,z, get(x,y,z,log) + value, log );
}

Tensor* Tensor::copy()
{
    Tensor *result = new Tensor(mSize);
    for (int z =0; z < mSize.depth; z++){
        for (int y = 0; y < mSize.height; y++  ){
            for(int x = 0; x<mSize.width;x++){
                result->set(x,y,z,get(x,y,z,QString("copy - get")), QString("copy - set"));
            }
        }
    }
    return result;
}



QDebug operator<<(QDebug debug, const Tensor &tensor)
{
    debug << endl;
    debug << qPrintable(tensor.toQStringSize())<<endl;

    for(int y = 0; y < tensor.mSize.height; y++){
        QString string = QString("");

        for(int z = 0; z < tensor.mSize.depth; z++){
            string.append("|");
            for(int x = 0; x < tensor.mSize.width; x++){

                string.append(QString::number(tensor.get(x,y,z)).rightJustified(8,' ' ,true)+" ");

            }
            string.append("|     ");
        }
        debug<< qPrintable(string) << endl << endl;

    }
    return debug;
}

QDebug operator<<(QDebug debug, const TensorSize &tensorSize)
{

    debug << "TensorSize(" << tensorSize.width << "*" << tensorSize.height << "," << tensorSize.depth << ")";
    return debug;
}

bool operator ==(TensorSize &a, TensorSize &b)
{

    if (a.depth == b.depth){
        if (a.height == b.height){
            if (a .width == b.width){
                return true;
            }
        }
    }
    return false;

}

QString TensorSize::exportToString()
{
    return QString("(" + QString::number(width) + "," + QString::number(height) + "," + QString::number(depth) + ")");
}
