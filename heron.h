#ifndef HERON_H
#define HERON_H

#include <QList>
class Link;
class Heron
{
public:
    Heron(int idLayer,int id);
//    int id;

    bool operator == (const Heron& heron) const;
    bool operator != (const Heron& heron) const;
    //int mLinksOut[];// this may delete
    //int mLinksIn[];// this may delete
//    float mNext, mRealy; // this may delete
//    float l; /// summ for enters l
//    float o;///  heron output



    void addLink(Heron *heron, float weight);
    int mIdLayer;
    int mId;

// i coment strings there we dont use now!
//    float lastDWeight; // delta between weights
    QList<Link> mLinks = QList<Link>();// output links (there sender this)
};
class Link
{
public:
    Heron* mSender;
    Heron* mRecever;
    float mWeight = 1;
    float mError = 0; //q (s-r)
    Link(Heron* sender,Heron* recever,float weight);
};
#endif // HERON_H
