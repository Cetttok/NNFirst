#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QTextStream>
#include <QList>
#include "chnetwork.h"

class FileManager{
public:
    FileManager(QString data);

    QList<QString> readFile(QString name);
    QList <QString> mData;
    QList<LayerData> mLayerData;
    static QRegExp mTensorSizeExp;
    static QRegExp mLayerExp;
    static QRegExp mNetworkSizeExp;

    QList<LayerData> getLayersData();
    QList<Tensor> getFilters();
    //parseTensorSize(QString data);
    TensorSize parseTensorSize(QString data);
    LayerData parseLayerData(QString data);
    QList<LayerData> *parseLayersSize(QString data);
    Tensor parseTensor(QList<QString> list, TensorSize size);
    Tensor parseFilter(QList<QString> list);
protected:
    QList<LayerData> * _layersData = nullptr;
};


#endif // FILEMANAGER_H
