#include "resultviewer.h"
#include <QGridLayout>
#include <QDebug>
Widget::Widget():QWidget()
{
    mIterationCount = new QLineEdit("0 iteratoin",this);
    mIterationCount->setReadOnly(true);

    //_infoText = new QLineEdit("tadam", this);

    _infoLayout = new QGridLayout();
    //_infoLayout->addWidget(_infoText,01,2);

    _markedColor.setColor(QPalette::Base,Qt::yellow);
    _markedColor.setColor(QPalette::Text,Qt::black);

    _secondMarkedColor.setColor(QPalette::Base,QColor(255, 218, 185));
    _secondMarkedColor.setColor(QPalette::Text,Qt::black);

    _unMarkedColor.setColor(QPalette::Base,Qt::white);
    _unMarkedColor.setColor(QPalette::Text,Qt::black);


    _correctNumColor.setColor(QPalette::Base,Qt::green);
    _correctNumColor.setColor(QPalette::Text,Qt::red);

    _layout = new QVBoxLayout();
    _layout->addWidget(mIterationCount);
    _layout->addLayout(_infoLayout);

    this->setLayout(_layout);
}

int Widget::column()
{
    return _infoLayout->columnCount();
}

void Widget::markerTextInfo(int row, int column)
{
    mData[row][column]->setPalette(_markedColor);
}

void Widget::markerTextInfoSecond(int row, int column)
{
    mData[row][column]->setPalette(_secondMarkedColor);
}
void Widget::markerFirstColumnForRow(int row){
    mData[row][0]->setPalette(_correctNumColor);
}
void Widget::unMarkerTextInfo(int row, int column){
    mData[row][column]->setPalette(_unMarkedColor);
}

int Widget::row(){
    return _infoLayout->rowCount();
}
void Widget::insertTextEdit(QLineEdit *text, int row, int column){
    _infoLayout->addWidget(text, row, column);
    text->setReadOnly(true);
}
void Widget::changeTextInInfo(QString newText, int row, int column){
    mData[row][column]->setText(newText);
}
int getMaxIdFormList(QList<double> &list){
    int max = 0;
    for (int i = 0; i < list.size(); i++){
        if (list[i] > list[max]){
            max = i;
        }
    }
    return max+1;
}
int getSecondMaxIdFormList(QList<double> list){
    list.removeAt(getMaxIdFormList(list)-1);
    return getMaxIdFormList(list);
}
void ResultViewer::upDate(int iteration){


    mWidget->mIterationCount->setText(QString("Iteration: " + QString::number(iteration)));

    mWidget->update();
}
void ResultViewer::upDateRow(QList<double> list, int row){
    if (list.size() != mWidget->column()-1){
        qDebug() << "void ResultViewer::upDateRow(...): Error! bad column"
                 << list.size() <<"!=" << mWidget->column();
        return;
    }
    for (int c = 0; c < list.size(); c++){
        mWidget->changeTextInInfo(QString::number(list[c]),row,c+1);
        mWidget->unMarkerTextInfo(row,c+1);

    }
    //qDebug() << list << getMaxIdFormList(list);
    mWidget->markerTextInfoSecond(row, getSecondMaxIdFormList(list));
    mWidget->markerTextInfo(row,getMaxIdFormList(list));

    if (getMaxIdFormList(list)-1 == row){
        mWidget->markerFirstColumnForRow(row);

    }
    else{
        mWidget->unMarkerTextInfo(row, 0);
    }

}

ResultViewer::ResultViewer()
{
    qDebug() << "created!";
    mWidget = new Widget();
    initData(10,10);
    initData(10,10);
    mWidget->update();

}
void ResultViewer::upDateData(QList<QList<double>> newData){
    if(newData.size() != mWidget->row()){
        qDebug() << "ResultViewer::upDateData(...): Error! badRowsSize:"
                 << newData.size() <<"!=" << mWidget->row();
        return;
    }
    else{
        if(newData.first().size()!= mWidget->column()-1){
            qDebug()<< "ResultViewer::upDateData(...): Error! badColumnsSize: "
                  <<newData.first().size() << "!=" << mWidget->column();
            return;
        }
        else{
            for(int r = 0; r < mWidget->row(); r++){
                for(int c = 1; c < mWidget->column(); c++){
                    mWidget->changeTextInInfo(QString::number(newData[r][c]),r,c);
                }
            }
        }
    }
}

void ResultViewer::initData(int classes, int containers){
    for (int c =0; c < containers; c++) {
        mWidget->mData.append(QList<QLineEdit*>());
        for (int i = 0; i < classes+1; i++){
            if (i == 0){
                mWidget->mData[c].append(new QLineEdit(QString::number(c)));
            }
            else{
                mWidget->mData[c].append(new QLineEdit(QString("udefinded")));
            }
            mWidget->insertTextEdit(mWidget->mData[c][i  ], c, i);


        }
    }
}
