#include "heronfield.h"
#include <qDebug>
#include <QRandomGenerator>
double e = 2.7182818284;

HeronField::HeronField(QList<int> heronsOnLayersAmount)
{
     mHerons = QList<QList<Heron*>>();
    //create herons
    //qDebug() <<heronsOnLayersAmount;
    for (int layer = 0;layer<heronsOnLayersAmount.size(); layer++){ // on every layer
        mHerons.append(QList<Heron*>());
        for (int heron = 0; heron< heronsOnLayersAmount[layer];heron++){ //on every heron on layer
            mHerons[layer].append(new Heron(layer,heron));
        }
    }
    //qDebug() << "herons created for scheme = "<< heronsOnLayersAmount;


    //link herons
    for (int layer = 0;layer<mHerons.size(); layer++){ // on every layer
        for (Heron *heron : mHerons[layer]){ //on every heron on layer
            if(layer+1 <mHerons.size()){
                for(Heron *linkedHeron : mHerons[layer+1]){ // every heron to every heron
                    double weight = QRandomGenerator::system()->generateDouble()/100;
                    if (weight != 0){
                    heron->addLink(linkedHeron, weight);//dont forget to add random weight!!
                    //(QRandomGenerator::system()->generateDouble()
                    }
                    else {
                        heron->addLink(linkedHeron,0.005);

                    }
                }
            }
        }
    }
    //qDebug() << "herons been linked";
    for (int layer = 0;layer<mHerons.size(); layer++){ // on every layer
        for (Heron *heron : mHerons[layer]){ //on every heron on layer
            //qDebug() << heron->toQString();

        }
    }


}
void HeronField::makeLearningStep(double correctOutput, double learningSpeed,double learningMoment){
    //calculate errors for heron

    mHerons.last().last()->mLayerError = derFunc(weightedSum(mHerons.last().last()->mInputs))
            *(correctOutput-mHerons.last().last()->mOutput);
    //errors.append(correctOutput-mHerons.last().last()->mOutput);
    //qDebug () << mHerons.first().last()->toQString();

    for (int layer = mHerons.size() - 2 ; layer >= 0; layer--){
        //qDebug() << "using" << layer;
        for (int heron = 0; heron < mHerons[layer].size(); heron++){
            Heron* activeHeron = mHerons[layer][heron];
            QList<double> forwardErrors = QList<double>();
            QList<double> weightForForwardErrors = QList<double>();
            for (Link link : activeHeron->mLinks){
                forwardErrors.append(link.mRecever->mLayerError);
                weightForForwardErrors.append(link.mWeight);
            }
            activeHeron->mLayerError = derFunc(weightedSum(activeHeron->mInputs))
                    *multySum(forwardErrors,weightForForwardErrors);
            //qDebug() << activeHeron->toQString() << "error = " <<activeHeron->mLayerError;
        }
    }

    for (QList<Heron*> &layer : mHerons){
        for(Heron *heron : layer){
            for(Link &link : heron->mLinks){
                double dWeight = learningSpeed*heron->mOutput*heron->mLayerError+learningMoment*link.mLastDWeight;
                //qDebug() << dWeight;
                //qDebug() << dWeight <<" = " <<heron->mOutput<< heron->mLayerError;
                link.mWeight += dWeight;
                link.mLastDWeight = dWeight;
            }
        }
    }


}
void HeronField::clearInputsAndOutputs(){
    for (const auto& layer : mHerons){
        for (auto& heron: layer){
            heron->mOutput = 0;
            heron->mInputs.clear();
        }
    }
}

double HeronField::multySum(QList<double> A, QList<double> B){
    double output;
    if(A.size()!=B.size()){
        qDebug() << "A.size() = " <<A.size()<< "B.size() = "<<B.size()<< " invalid!";
        return NULL;
    }
    for (int i = 0; i < A.size(); i++){
        output+=A[i] * B[i];
    }
    return output;
}
double HeronField::calculateOutput(QList<double> inputs)
{
    clearInputsAndOutputs();

    for(int i = 0; i<inputs.size(); i++){
        mHerons[0][i]->mInputs.append(inputs[i]);

    }

    for (int layer = 0; layer<mHerons.size(); layer++){
        for (int heron =0; heron < mHerons[layer].size(); heron++){
             //qDebug() << "new Heron - " <<mHerons[layer][heron]->toQString();
             mHerons[layer][heron]->mOutput = func(weightedSum(mHerons[layer][heron]->mInputs));

             for (Link link : mHerons[layer][heron]->mLinks){
                link.mRecever->mInputs.append(mHerons[layer][heron]->mOutput*link.mWeight);
                //qDebug() <<"mOutput * link.Weifghr = "<<mHerons[layer][heron]->mOutput << "*"

                        //<<link.mWeight << "=" << mHerons[layer][heron]->mOutput*link.mWeight;
            }
            //qDebug() << mHerons[layer][heron]-> mInputs;
        }
        //qDebug() << "new layer - "<< layer;
    }
    //qDebug() << "Herons field has been calculated last var";

    return func(weightedSum(mHerons.last().last()->mInputs));

}

double HeronField::func(double input)
{
    //qDebug() << "func "<< input;
    //return input;

 //relLU
//    if (input < 0){
//        return 0;
//    }
//return input;
    return input;
    //sigmoid
//    return sin(input);
//    double result = 1/(1+ pow(e,(0-input)));
//    if (result!=result){
//        qDebug() << "invalid "<<pow(e,(0-input));
//    }
//    //return result;
//    if (input > 0){

    //      return input;}

//     return 0;
}
double HeronField::derFunc(double input){
    //relLU

//    if (input > 1){
//        return 0;
//    }
//    return 1;

//    //sigmoid
//    if (input < 0){
//      return 0;}

//..     return 1;
//    //return cos(input);
//    double result = func(input)*(1-func(input));
//    if (result!=result){
//        qDebug() <<"invalid for derFunc"<< func(input);
//    }
//    return result;
    return 1;
}
double HeronField::weightedSum(QList<double> inputs){
    double result =0;
    for (double input : inputs){
        result += input;
    }
    //qDebug() << "weightedSum()" << result << inputs;
    return result;
}
