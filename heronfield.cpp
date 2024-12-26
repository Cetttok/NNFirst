#include "heronfield.h"
#include <qDebug>
#include <QRandomGenerator>
#include <QtMath>

double e = 2.7182818284;

HeronField::HeronField(QList<int> heronsOnLayersAmount, double startWeightMultiple)
{
    //QRandomGenerator::system();
    mHerons = QList<QList<Heron*>>();
    //create herons
    //qDebug() <<heronsOnLayersAmount;
    for (int layer = 0;layer<heronsOnLayersAmount.size(); layer++){ // on every layer
        mHerons.append(QList<Heron*>());
        for (int heron = 0; heron< heronsOnLayersAmount[layer];heron++){ //on every heron on layer
            mHerons[layer].append(new Heron(layer,heron,startWeightMultiple*(QRandomGenerator::global()->bounded(2.0)-1.0)));
        }
    }
    mSize = heronsOnLayersAmount;
    //qDebug() << "herons created for scheme = "<< heronsOnLayersAmount;


    //link herons
    for (int layer = 0;layer<mHerons.size(); layer++){ // on every layer
        for (Heron *heron : mHerons[layer]){ //on every heron on layer
            if(layer+1 <mHerons.size()){
                for(Heron *linkedHeron : mHerons[layer+1]){ // every heron to every heron
                    double weight = startWeightMultiple*(QRandomGenerator::global()->bounded(2.0)-1.0);
                    //qDebug() << "weight"<<weight;
                    if (weight != 0){
                    heron->addLink(linkedHeron, weight);//dont forget to add random weight!!
                    //(QRandomGenerator::system()->generateDouble()
                    }
                    else {
                        heron->addLink(linkedHeron,0.005);
                        qDebug() << "HeronField::HeronField(...): warning! weight is 0 :(";

                    }
                }
            }
        }
    }
    //qDebug() << "herons been linked";
//    for (int layer = 0;layer<mHerons.size(); layer++){ // on every layer
//        for (Heron *heron : mHerons[layer]){ //on every heron on layer
//            //qDebug() << heron->toQString();

//        }
//    }


}
QList<double> HeronField::makeLearningStep(QList<double> correctOutput, double learningSpeed,double learningMoment){
    //calculate errors for heron

    for(int i = 0; i < mHerons.last().size();i++){
        mHerons.last()[i]->mLayerError = derFunc(weightedSum(mHerons.last()[i]->mInputs))
            *(correctOutput[i] - mHerons.last()[i]->mOutput);
    }
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
                weightForForwardErrors.append(link.weight());
            }
            activeHeron->mLayerError = derFunc(weightedSum(activeHeron->mInputs))
                    *multySum(forwardErrors,weightForForwardErrors);
            //qDebug() << activeHeron->toQString() << "error = " <<activeHeron->mLayerError;
        }
    }

//    for (QList<Heron*> &layer : mHerons){
//        for(Heron *heron : layer){
//            for(Link &link : heron->mLinks){
//                double dWeight = learningSpeed*heron->mOutput*heron->mLayerError+learningMoment*link.mLastDWeight;
//                //qDebug() << dWeight;
//                //qDebug() << dWeight <<" = " <<heron->mOutput<< heron->mLayerError;
//                link.mWeight += dWeight;
//                link.mLastDWeight = dWeight;
//            }
//        }
//    }

        for (QList<Heron*> &layer : mHerons){
            for(Heron *heron : layer){
                for(Link &link : heron->mLinks){
                    double dWeight = learningSpeed*link.mSender->mOutput*link.mRecever->mLayerError+learningMoment*link.mLastDWeight;

                    //qDebug() << dWeight;
                    //qDebug() << dWeight <<" = " <<heron->mOutput<< heron->mLayerError;
                    link.mWeight += dWeight;
                    link.mLastDWeight = dWeight;
                }
                heron->mBias = learningSpeed*heron->mLayerError;
            }

        }
    QList<double> errors  = QList<double> ();
    for (Heron * heron: mHerons.first()){
        errors.append(heron->mLayerError);
    }
    return errors;

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
QList<double> HeronField::calculateOutput(QList<double> inputs)
{
    clearInputsAndOutputs();

    for(int i = 0; i<inputs.size(); i++){
        mHerons[0][i]->mInputs.append(inputs[i]);

    }

    for (int layer = 0; layer<mHerons.size(); layer++){
        for (int heron =0; heron < mHerons[layer].size(); heron++){
             //qDebug() << "new Heron - " <<mHerons[layer][heron]->toQString();
             mHerons[layer][heron]->mInputs.append(mHerons[layer][heron]->mBias);
             mHerons[layer][heron]->mOutput = func(weightedSum(mHerons[layer][heron]->mInputs));
             //qDebug() << "HeronField::calculateOutput Heron" << layer<<"input: "<< mHerons[layer][heron]->mInputs <<"before func: " <<weightedSum(mHerons[layer][heron]->mInputs) << "output : " << func(weightedSum(mHerons[layer][heron]->mInputs));
             for (Link link : mHerons[layer][heron]->mLinks){
                link.mRecever->mInputs.append(mHerons[layer][heron]->mOutput*link.mWeight);
                //qDebug() <<"mOutput * link.Weifghr = "<<mHerons[layer][heron]->mOutput << "*"

               //qDebug() <<mHerons[layer][heron]->toQString();      //<<link.mWeight << "=" << mHerons[layer][heron]->mOutput*link.mWeight;
            }

            //qDebug() << mHerons[layer][heron]-> mInputs;
        }
        //qDebug() << "new layer - "<< layer;
    }
    //qDebug() << "Herons field has been calculated last var";
    QList<double> result = QList<double>();
    for (Heron* heron : mHerons.last()){
        result.append(func(weightedSum(heron->mInputs)));
    }
    return result;

}

void HeronField::updateHeron(HeronData data)
{
    QList<Link*> links;
    if (data.mLayer < mHerons.size()){
        if (data.mId < mHerons[data.mLayer].size()){
            links = mHerons[data.mLayer][data.mId]->getPointersToLinks();
            mHerons[data.mLayer][data.mId]->mBias = data.mBasis;
        }
        else{
            qDebug() << "HeronField::updateHeron(...):  Cant update heron _ bad mId!";
            return;
        }
    }
    else{
        qDebug() << "HeronField::updateHeron(...): Cant update data - bad LayerId";
        return;
    }

    if (data.mWeights.size() != links.size()){
        qDebug() << "HeronField::updateHeron(...): Bad data or different strucuture" << data;
        return;
    }
    for (int  i = 0 ; i < data.mWeights.size(); i++){
        if (i >= links.size()){
            qDebug() << "HeronField::updateHeron(...): Tram - pam. Bad struct or data";
            break;
        }
        links[i]->mWeight= data.mWeights[i];
        links[i]->mLastDWeight = 0;

    }
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
    //return input;

    //sigmoid
//    return sin(input);
    //return 1/(1+ qPow(e,(-input)));
    //if (result!=result){
      //  qDebug() << "invalid "<<result;
    //}
    //qDebug() << input;
//    //return result;
//    if (input > 0){
//          return input;
//    }

//     return 0.001 * input;
    return input/(1+fabs(input));
    //return input;
}
double HeronField::derFunc(double input){
    //relLU

//    if (input > 1){
//        return 0;
//    }
//    return 1;

//    //sigmoid
//    if (input > 0){
//      return 1.0;}

//     return 0.001;
    return 1/((1+fabs(input))*(1+fabs(input)));

    ////    //return cos(input);
    //return func(input)*(1.0-func(input));
//    if (result!=result){
//        qDebug() <<"invalid for derFunc"<< func(input);
//    }
//    //qDebug() << result <<func(input)<<input;
//    return result;
    //return 1;
}
double HeronField::weightedSum(QList<double> inputs){
    double result =0;
    for (double &input : inputs){
        result += input;
    }
    //qDebug() << "weightedSum()" << result << inputs;
    return result;
}
