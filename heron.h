#ifndef HERON_H
#define HERON_H


#include <QList>
class Link;
class Heron
{
public:
    Heron(int idLayer,int id, double bias);
//    int id;

    bool operator == (const Heron& heron) const;
    bool operator != (const Heron& heron) const;

    //int mLinksOut[];// this may delete
    //int mLinksIn[];// this may delete
//    double mNext, mRealy; // this may delete
//    double l; /// summ for enters l
//    double o;///  heron output
    double mLayerError = 0;

    QString toQString();
    Link getLinkForHeron(int layer, int heron);
    void addLink(Heron *heron, double weight);
    int mIdLayer;
    int mId;
    QList<double> mInputs;
    double mOutput = 0;
    double mBias = 1;

// i coment strings there we dont use now!
//    double lastDWeight; // delta between weights
    QList<Link> mLinks = QList<Link>();// output links (there sender this)
};
class Link
{
public:

    Heron* mSender;
    Heron* mRecever;
    double mWeight = 1;
    double mLastDWeight = 0;
    QString toQString(){
        return QString("Link for Heron {"+QString::number(mSender->mIdLayer)
                       +QString::number(mSender->mId)+"} to {"
                       +QString::number(mRecever->mIdLayer)
                       +QString::number(mRecever->mId)+ "} weight = "
                       +QString::number(mWeight));
    }
    Link(Heron* sender,Heron* recever,double weight);
};
#endif // HERON_H
