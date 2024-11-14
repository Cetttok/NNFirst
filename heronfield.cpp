#include "heronfield.h"
#include <qDebug>
float e = 2.7182818284;
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
            if(layer+1 <mHerons.size()){
                for(Heron *linkedHeron : mHerons[layer+1]){ // every heron to every heron
                    heron->addLink(linkedHeron, 0.5);//dont forget to add random weight!!


                }
            }
        }
    }
    qDebug() << "herons been linked";
    for (int layer = 0;layer<mHerons.size(); layer++){ // on every layer
        for (Heron *heron : mHerons[layer]){ //on every heron on layer
            qDebug() << heron->toQString();

        }
    }


}

float HeronField::calculateOutput(QList<float> inputs)
{


    for(int i = 0; i<inputs.size(); i++){
        mHerons[0][i]->mInputs.append(inputs[i]);
    }

    for (int layer = 0; layer<mHerons.size(); layer++){
        for (int heron =0; heron < mHerons[layer].size(); heron++){
             qDebug() << "new Heron - " <<mHerons[layer][heron]->toQString();
             mHerons[layer][heron]->mOutput = func(weightedSum(mHerons[layer][heron]->mInputs));

             for (Link link : mHerons[layer][heron]->mLinks){
                link.mRecever->mInputs.append(mHerons[layer][heron]->mOutput*link.mWeight);
                qDebug() <<"mOutput * link.Weifghr = "<<mHerons[layer][heron]->mOutput << "*"
                        <<link.mWeight << "=" << mHerons[layer][heron]->mOutput*link.mWeight;
            }

        }
        qDebug() << "new layer - "<< layer;
    }
    qDebug() << "Herons field has been calculated last var";

    return func(weightedSum(mHerons.last().last()->mInputs));

}

float HeronField::func(float input)
{
    //qDebug() << "func "<< input;
    //return input;
    return 1/(1+ pow(e,(0-input)));
}
float HeronField::weightedSum(QList<float> inputs){
    float result =0;
    for (float input : inputs){
        result += input;
    }
    qDebug() << "weightedSum()" << result << inputs;
    return result;
}
