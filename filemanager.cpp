#include "filemanager.h"
#include <QString>
QRegExp FileManager::mTensorSizeExp(QString("[(][0-9]+,[0-9]+,[0-9]+\[)]"));
QRegExp FileManager::mLayerExp(QString("(ConvLayer|MaxPool|Tensor)_size_[(][0-9]+,[0-9]+,[0-9]+[)]->[(][0-9]+,[0-9]+,[0-9]+[)]"));
QRegExp FileManager::mNetworkSizeExp(QString("Network:((ConvLayer|MaxPool)_size_[(][0-9]+,[0-9]+,[0-9]+[)]->[(][0-9]+,[0-9]+,[0-9]+[)];)+"));
FileManager::FileManager(QString data):mData()
{
    mData = readFile(data);
}

QList<QString> FileManager::readFile(QString name){
    mData = QList<QString>();
    QList<QString> lines;
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "FileManager::readFile(...): 404. (CAN NOT OPEN FILE | NOT FOUND)";
        return QList<QString>();
    }
    qDebug() << "FileManager::readFile(...): FileOpened sucsessful, FileSize: " << file.size();
    QTextStream dataStream(&file);

    while (!dataStream.atEnd()){
        lines.append(dataStream.readLine());
        //qDebug() << "line";
    }
    //removing bad symbols
//    lines.removeAll(QString(" "));
//    lines.removeAll(QString(""));
//    lines.removeAll(QString("\n"));
//    lines.removeAll(QString("\t"));
    //mData.append(lines);
    qDebug() << "FileManager::readFile(...): readCompleted! lines_size_" << lines.size();
    ///qDebug() << mData;
    return lines;
}
QList<LayerData> FileManager::getLayersData(){
    if (_layersData == nullptr){
        //QList<LayerData> layerData = parseLayersSize();
        _layersData  = parseLayersSize(mData.first());

        return *parseLayersSize(mData.takeFirst());
    }
    else{
        return *_layersData;
    }
    //qDebug() << *_layersData;
}

QList<Tensor> FileManager::getFilters(){
    QList<Tensor> result = QList<Tensor> ();
    for (int i = 0; i < mData.size(); i++){
        QList<QString> atFilter = QList<QString> ();
        if (mData[i].contains("ConvLayer_filters{")){
            mData.removeAt(i);
            while (!mData[i].contains("}") && i<mData.size()){
                atFilter.append(mData[i]);
                i++;
            }
            atFilter.append(mData[i]);
            atFilter.removeLast();
            //TensorSize size = parseTensorSize(atFilter.takeFirst());
            //qDebug() << size;
            result.append(parseTensor(atFilter,parseTensorSize(atFilter.takeFirst())));
        }
        else{
            //qDebug() << mData[i];
            //qDebug() << "FileManager::getFilters(): Error or BadFile: first string domt containts 'ConvLayer_filters{' ";
        }
    }
    return result;
}
TensorSize FileManager::parseTensorSize(QString data){

    if (!data.contains(mTensorSizeExp)){
        qDebug() << "FileManager::parseTensorSize(...): Error! invalid data for mTensorSizeExp! data:" <<data;
        return TensorSize(0,0,0);
    }
    QList<QString> splited = data.split(QRegExp("[/,/)/(]"));
    splited.removeFirst();
    splited.removeLast();
    if(splited.size()!=3){
        qDebug() << "FileManager::parseTensorSize(...): Error! badSplit...";
        qDebug() << splited;
    }
    //TensorSize(1,1, 1);
    //
    return TensorSize(splited[0].toInt(),splited[1].toInt(), splited[2].toInt());

}
Tensor FileManager::parseFilter(QList<QString> list){
    if (!list.first().contains("ConvLayer_filters{")){
        qDebug() << "FileManager::parseFilter(...): Bad Signature!";

        return Tensor(0,0,0);
    }
    else{
        list.removeFirst();
    }
    if (list.last().contains("}")){
        list.removeLast();
    }
    else{
        qDebug() << "FileManager::parseFilter(...): Bad Sigantture (not '}' at th end)";
        return Tensor(0,0,0);
    }
    TensorSize filterSize = parseTensorSize(list.first());
    qDebug() << filterSize;
    list.removeFirst();
    Tensor result = parseTensor(list,filterSize);
    return result;

}
Tensor FileManager::parseTensor(QList<QString> list, TensorSize size){
    if (list.size() != ((size.height*size.depth)+(size.depth))){
        qDebug() << "FileManager::parseTensor(...): Error bad strings" <<(size.height)+(size.depth) << list.size();
        qDebug() << list;
    }
    Tensor result(size);
    int dCount = 0;
    int yCount =0;
    for (QString line : list){
        if (line == "and"){
            dCount++;
            yCount=0;
            if (dCount == size.depth){
                break;
            }
            continue;
        }
        else if(line == "end"){
            break;
        }
        QList<QString> splited = line.split("-");
        for (int x =0; x < splited.size(); x++){
            result.set(x,yCount,dCount,splited[x].toDouble(), QString("Parse tensor"));
        }
        yCount++;
    }
    return result;
}
QList<LayerData> *FileManager::parseLayersSize(QString data){
    if (!data.contains(mNetworkSizeExp)){
        qDebug() << "FileManager::parseLayersSize(...): Error. dont metch pattern!";
    }
    QList<QString> splited = data.split(":");
    splited.append(splited.last().split(";"));
    splited.removeFirst();
    splited.removeLast();
    splited.removeFirst();
    //qDebug() << splited;
    QList<LayerData>* result =new QList<LayerData>();
    for (QString layer : splited){
        result->append(parseLayerData(layer));
    }
    return result;

}
LayerData FileManager::parseLayerData(QString data){
    if (!data.contains(mLayerExp)){
        qDebug() << "FileManager::parseLayerData(QString data): ERROR! dont match to pattern" << data;
    }
    LayerData result;

    QList<QString> splited = data.split("_size_");
    if (splited.first() == "ConvLayer"){
        result.mType = LayerType::CONV;
    }
    else if(splited.first() == "MaxPool"){
        result.mType = LayerType::MXPOOL;

    }
    else{
        qDebug() << "FileManager::parseLayerData(...): Error! invalid type.";
    }
    splited = splited[1].split("->");

    result.mInputSize = parseTensorSize(splited[0]);
    result.mOutputSize = parseTensorSize(splited[1]);

    //qDebug() << result.mInputSize;
    //qDebug() << result.mOutputSize;
    return result;
}
