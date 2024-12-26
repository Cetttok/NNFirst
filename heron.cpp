#include "heron.h"
#include <qDebug>

Heron::Heron(int idLayer, int id, double bias):mIdLayer(idLayer),mId(id),mBias(bias)
{
    //constructor
}

bool Heron::operator ==(const Heron &heron) const
{
    if (heron.mId == mId && heron.mIdLayer == mIdLayer){
        return true;
    }
    return false;
}

bool Heron::operator !=(const Heron &heron) const
{
    if (heron.mId == mId && heron.mIdLayer == mIdLayer){
        return false;
    }
    return true;
}

QList<Link *> Heron::getPointersToLinks()
{
    QList<Link*> result;
    for (Link &link: mLinks){
        result.append(&link);
    }
    return result;
}
QString getQStringFromQList(QList <double> list){
    QString string = QString("(");
    for (double el: list){
        string.append(QString::number(el)+",");
    }
    string.append(")");
    return string;
}
QString Heron::toQString()
{
    QString string =QString();
    string+=(QString("Heron("));
    string+=(QString::number(mIdLayer)+QString(","));
    string+=(QString::number(mId)+QString("){"));
    string+=(QString("Links{"));
    for (Link &link : mLinks){
        string+= (link.toQString()+QString(";"));
    }
    string+=(QString("}"));
    string+=(QString("Inputs - ") + getQStringFromQList(mInputs));
    string+=(QString("Output - ")+QString::number(mOutput))+QString("}");
    string+=(QString("basis - ")+ QString::number(mBias));
    return string;
}

Link Heron::getLinkForHeron(int layer, int heron)
{
    for (Link &link : mLinks){
        if (link.mRecever->mId == heron
                && link.mRecever->mIdLayer ==layer){
            return link;
        }
    }
}

void Heron::addLink(Heron* heron, double weight)
{
    mLinks.append(Link(this,heron,weight));
}

double Link::weight() const
{
    return mWeight;
}

Link::Link(Heron *sender, Heron *recever, double weight):
    mSender(sender),mRecever(recever),mWeight(weight)
{
//constructor
}

HeronData::HeronData(int id, int layer, QList<double> weights, double basis):mId(id), mLayer(layer), mWeights(weights), mBasis(basis)
{

}

QDebug operator<<(QDebug debug, const HeronData &data)
{

    debug << "Heron(" <<data.mLayer<<"," << data.mId << ") basis = " << data.mBasis << " weigts = "<<data.mWeights ;
    return debug;
}
