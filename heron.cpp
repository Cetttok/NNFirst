#include "heron.h"
#include <qDebug>

Heron::Heron(int idLayer, int id):mId(id),mIdLayer(idLayer)
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
QString getQStringFromQList(QList <float> list){
    QString string = QString("(");
    for (float el: list){
        string.append(QString::number(el));
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
    string+=(QString("Links{\n"));
    for (Link &link : mLinks){
        string+= (link.toQString()+QString(";\n"));
    }
    string+=(QString("}\n"));
    string+=(QString("Inputs - ") + getQStringFromQList(mInputs));
    string+=(QString("Output - ")+QString::number(mOutput))+QString("\n}");
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

void Heron::addLink(Heron* heron, float weight)
{
    mLinks.append(Link(this,heron,weight));
}

Link::Link(Heron *sender, Heron *recever, float weight):
    mSender(sender),mRecever(recever),mWeight(weight)
{
//constructor
}
