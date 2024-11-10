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

void Heron::addLink(Heron* heron, float weight)
{
    mLinks.append(Link(this,heron,weight));
}

Link::Link(Heron *sender, Heron *recever, float weight):
    mSender(sender),mRecever(recever),mWeight(weight)
{
//constructor
}
