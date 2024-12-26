#include "filemanager.h"
#include <QString>
QRegExp FileManager::mTensorSizeExp(QString("[(][0-9]+,[0-9]+,[0-9]+\[)]"));
QRegExp FileManager::mLayerExp(QString("(ConvLayer|MaxPool|Tensor)_size_[(][0-9]+,[0-9]+,[0-9]+[)]->[(][0-9]+,[0-9]+,[0-9]+[)]"));
QRegExp FileManager::mNetworkSizeExp(QString("Network:((ConvLayer|MaxPool)_size_[(][0-9]+,[0-9]+,[0-9]+[)]->[(][0-9]+,[0-9]+,[0-9]+[)];)+"));
QRegExp FileManager::mHeronFieldSizeExp("HeronField_size[(]([0-9]+,)+[0-9]+[)];");
QRegExp FileManager::mHeronDataExp("Heron\\([0-9]+_\\[((-?[0-9]+[.][0-9]*,)*(-?[0-9]+[.][0-9]*(e-?[0-9]+)?)?\\]_basis\\(-?[0-9]+(\\.[0-9]+)?(e-?[0-9]+)?)\\)\\);" /*+\?,?)+\]_basis[(][0-9]+([.][0-9])?+[)][)];"*/);
FileManager::FileManager(QString convData, QString heronsData):mConvFile(convData), mHeronsFile(heronsData)
{
    mConvData = readFile(mConvFile);
    mHeronsData = readFile(mHeronsFile);
}

QList<QString> FileManager::readFile(QFile &file){
    //mConvData = QList<QString>();
    QList<QString> lines;
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
    lines.removeAll(QString(" "));

    //mConvData.append(lines);
    qDebug() << "FileManager::readFile(...): readCompleted! lines_size_" << lines.size();
    ///qDebug() << mConvData;
    file.close();
    return lines;
}

CHNetwork *FileManager::initNetworkFromFiles(int width, int height)
{

    CHNetwork * result = new CHNetwork(width, height);
    result->reconstructWithLayersData(getLayersData());
    result->setFilters(getFilters());
    HeronField * herons = createNewHeronFieldFromData(mHeronsData);
    result->setLastFilter(herons);
    return result;

}
HeronData FileManager::parseHeronData(QString data, int layer){
    if (!data.contains(mHeronDataExp)){
        qDebug() <<"FileManager::parseHeronData(...): Error bad heronData and data = " <<data;
        //return HeronData(0,0,QList<double>(),0);
    }
    data.remove(QRegExp("Heron|[;]"));
    data.remove(0,1);
    data.remove(data.size()-1,1);
    QList<QString> splited = data.split("_");
    int id = splited[0].toInt();
    splited[2].remove(QRegExp("basis\\(|\\)"));
    splited[2].remove("_basis[(]|[)]");
    double basis = splited[2].toDouble();
    splited[1].remove(0,1);
    splited[1].remove(splited[1].size()-1,1);
    splited = splited[1].split(",");
    QList<double> weights;
    for (QString weight : splited){
        if (weight!=""){
            weights.append(weight.toDouble());
        }

    }

    return HeronData(id,layer,weights,basis);


}
HeronField* FileManager::createNewHeronFieldFromData(QList<QString> data){
    qDebug() << getHeronFieldSize(data.first());
    HeronField * result = new HeronField(getHeronFieldSize(data.takeFirst()));
    QList<HeronData> heronsData = getLinksFromFile(data);
    for (HeronData data : heronsData){
        result->updateHeron(data);
    }
    return result;

}
QList<HeronData> FileManager::getLinksFromFile(QList<  QString > data){
    //QList<int> heronFieldSize = getHeronFieldSize(data.takeFirst());
    //qDebug() << data;
    QList<HeronData> result;
    int layer = 0;
    for (int i = 0; i < data.size(); i++){
        if (data[i].contains("Layer{")){
            i++;
            while (!data[i].contains("}") && i < data.size()){
                result.append(parseHeronData(data[i], layer));
                i++;
            }
            layer++;
        }
    }
    return result;
}
QList<int> FileManager::getHeronFieldSize(QString data){
    if (!data.contains(mHeronFieldSizeExp)){
        qDebug() << "FileManager::getHeronFieldSize(...): Error and bad structure, string - " << data;
    }
    QList<QString> splited  = data.split("HeronField_size");
    //qDebug() << splited;
    splited.last().remove(QRegExp("[(]|[)]|;"));
    //qDebug() << splited;
    splited = splited.last().split(",");
    //qDebug() << splited;
    QList<int> result;
    for (QString &el : splited){
        result.append(el.toInt());
    }
    return result;


}
QList<LayerData> FileManager::getLayersData(){
    return *parseLayersSize(mConvData.takeFirst());
    //qDebug() << *_layersData;
}

QList<Tensor> FileManager::getFilters(){
    QList<Tensor> result = QList<Tensor> ();
    for (int i = 0; i < mConvData.size(); i++){
        QList<QString> atFilter = QList<QString> ();
        if (mConvData[i].contains("ConvLayer_filters{")){
            mConvData.removeAt(i);
            while (!mConvData[i].contains("}") && i<mConvData.size()){
                atFilter.append(mConvData[i]);
                i++;
            }
            atFilter.append(mConvData[i]);
            atFilter.removeLast();
            //TensorSize size = parseTensorSize(atFilter.takeFirst());
            //qDebug() << size;
            result.append(parseTensor(atFilter,parseTensorSize(atFilter.takeFirst())));
        }
        else{
            //qDebug() << mConvData[i];
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
            dCount++;
            break;
        }
        QList<QString> splited = line.split("_");
        for (int x =0; x < splited.size(); x++){
            result.set(x,yCount,dCount,splited[x].toDouble(), QString("Parse tensor"));
        }
        yCount++;
    }
    if (dCount != size.depth || yCount!= size.height){
        qDebug() << "FileManager::parseTensor(...): Warning! wrong parsing tensor. Be carefully...";
        qDebug() << dCount << yCount << "dCount and yCount";
    }
    return result;
}
QList<LayerData> *FileManager::parseLayersSize(QString data){
    if (!data.contains(mNetworkSizeExp)){
        qDebug() << "FileManager::parseLayersSize(...): Error. dont metch pattern!" << data;
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

void FileManager::saveNetworkToFile(CHNetwork *network)
{

    //QFile mFile(name);
    if (!mConvFile.open(QIODevice::WriteOnly| QIODevice::Truncate)){
        qDebug() << "FileManager::saveNetworkToFile(...): 404. (CAN NOT OPEN FILE | NOT FOUND)";
        return;
    }
    //qDebug() << "FileManager::readFile(...): FileOpened sucsessful, FileSize: " << file.size();
    QTextStream dataStream(&mConvFile);
    dataStream << "Network:";
    for (int i =0; i < network->convLayers().size();i++){

        dataStream << "ConvLayer_size_" << network->convLayers()[i]->getInputSize().exportToString() <<
                      "->" << network->convLayers()[i]->getOutputSize().exportToString() << ";";
        dataStream << "MaxPool_size_" << network->maxPoolLayers()[i]->getInputSize().exportToString() <<
                      "->" << network->maxPoolLayers()[i]->getOutputSize().exportToString() << ";";

    }

    dataStream << endl;

    for (int i = 0; i < network->convLayers().size(); i++){
//        LayerData data = getLayersData()[i];
//        if (data.mType == LayerType::CONV){
            dataStream << "ConvLayer_filters{" << endl;
            Tensor filter = network->convLayers()[i]->getFilters();
            dataStream<< "Tensor_size_(" << filter.mSize.width<<","<< filter.mSize.height<<","<< filter.mSize.depth << ");" <<endl;

            for (int d = 0; d < filter.mSize.depth; d++){
                for (int y = 0; y < filter.mSize.height; y ++){
                    for (int x = 0; x < filter.mSize.width; x++){
                        dataStream << filter.get(x,y,d,"saveNetwork");
                        if (x +1< filter.mSize.width){
                            dataStream << "_";
                        }
                    }
                    dataStream << endl;
                }
                if (d+1 < filter.mSize.depth){
                    dataStream << "and" << endl;
                }


            }
            dataStream << "end" << endl <<"}";
            //qDebug() << getLayersData().size();
            break;
        }
    //}
    mConvFile.close();
    //qDebug() << "taram";
    saveHeronFieldToFile(network->getLastLayer());
}
QString FileManager::heronToQStringForWrite(Heron * heron){
    QString result;
    result.append("Heron(");
    result.append(QString::number(heron->mId));
    result.append("_");
    result.append("[");
    for (Link *link: heron->getPointersToLinks()){
        result.append(QString::number(link->mWeight)+",");

    }
    if (heron->getPointersToLinks().size()>0){
        result.remove(result.size()-1, 1);
    }

    result.append("]_basis(");
    result.append(QString::number(heron->mBias));
    result.append("));");
    return result;

}
void FileManager::saveHeronFieldToFile(HeronField *field){
    //QFile mFile(name);
    if (!mHeronsFile.open(QIODevice::WriteOnly| QIODevice::Truncate)){
        qDebug() << "FileManager::saveHeronFieldToFile(...): 404. (CAN NOT OPEN FILE | NOT FOUND)";
        return;
    }
    QTextStream dataStream(&mHeronsFile);
    dataStream << "HeronField_size(";
    for (int sizeOnLayer : field->mSize){
        dataStream<< sizeOnLayer;
        if (field->mSize.indexOf(sizeOnLayer) <  field->mSize.size()-1){
            dataStream << ",";
        }
    }

    dataStream << ");" << endl;
    for (QList<Heron*> &onLayer : field->mHerons){
        dataStream << "Layer{" << endl;
        for (Heron * heron : onLayer){
            dataStream << heronToQStringForWrite(heron)<<endl;
        }
        dataStream << "}" << endl;
    }

    mHeronsFile.close();
}
