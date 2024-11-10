#include "heronfield.h"
#include <qDebug>
HeronField::HeronField(QList<int> heronsOnLayersAmount)
{
     mHerons = QList<QList<Heron*>>();
    //create herons
    qDebug() <<heronsOnLayersAmount;
    for (int layer = 0;layer<heronsOnLayersAmount.size(); layer++){ // on every layer
        mHerons.append(QList<Heron*>());
        for (int heron = 0; heron< heronsOnLayersAmount[layer];heron++){ //on every heron on layer
            mHerons[layer].append(new Heron(layer,heron));
        }
    }
    qDebug() << "herons created for scheme = "<< heronsOnLayersAmount;

    //link herons
    for (int layer = 0;layer<mHerons.size(); layer++){ // on every layer
        for (Heron *heron : mHerons[layer]){ //on every heron on layer
            for(Heron *linkedHeron : mHerons[layer]){ // every heron to every heron
                if (*heron != *linkedHeron){
                    heron->addLink(linkedHeron, 1);//dont forget to add random weight!!
                }
            }
        }
    }
    qDebug() << "herons been linked";
    for (int layer = 0;layer<mHerons.size(); layer++){ // on every layer
        for (Heron *heron : mHerons[layer]){ //on every heron on layer
            qDebug() << heron->mIdLayer << heron ->mId;

        }
    }


}
