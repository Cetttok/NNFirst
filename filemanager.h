#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QTextStream>
#include <QList>
#include "chnetwork.h"
#include "heronfield.h"

class FileManager{
public:
    FileManager(QString convData, QString heronsData);
    CHNetwork * initNetworkFromFiles(int width, int height);
    void saveNetworkToFile(CHNetwork * network);

protected:
    static QRegExp mTensorSizeExp;
    static QRegExp mLayerExp;
    static QRegExp mNetworkSizeExp;
    static QRegExp mHeronFieldSizeExp;
    static QRegExp mHeronDataExp;

    QFile mConvFile;
    QList <QString> mConvData;
    QFile mHeronsFile;
    QList <QString> mHeronsData;

    //QList<LayerData> mLayerData;
    //QList<LayerData> * _layersData = nullptr;
    QList<QString> readFile(QFile &file);


    QString heronToQStringForWrite(Heron *heron);
    //HeronField *createHeronFieldFromFile();
    HeronField *createNewHeronFieldFromData(QList<QString> data);
    QList<int> getHeronFieldSize(QString data);
    void saveHeronFieldToFile(HeronField *field);


    Tensor parseFilter(QList<QString> list);
    HeronData parseHeronData(QString data, int layer);
    QList<HeronData> getLinksFromFile(QList<QString> data);
    TensorSize parseTensorSize(QString data);
    LayerData parseLayerData(QString data);
    QList<LayerData> *parseLayersSize(QString data);
    Tensor parseTensor(QList<QString> list, TensorSize size);
    QList<Tensor> getFilters();
    QList<LayerData> getLayersData();
    //parseTensorSize(QString data);
    //HeronField *createHeronFieldFromFile();
};


#endif // FILEMANAGER_H
