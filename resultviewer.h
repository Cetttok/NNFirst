#ifndef RESULTVIEWER_H
#define RESULTVIEWER_H
#include <QSize>
//#include <QTextBlock>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>
class Widget : public QWidget
{
public:
    Widget();
    QLineEdit * mIterationCount;
    QGridLayout * _infoLayout;
    QVBoxLayout * _layout;
    QList<QList<QLineEdit*>> mData;
    void insertTextEdit(QTextEdit * text);
    int column();
    void markerTextInfo(int row, int column);
    void markerTextInfoSecond(int row, int column);

    int row();
    QPalette _markedColor;
    QPalette _secondMarkedColor;

    QPalette _correctNumColor;

    QPalette _unMarkedColor;
    void changeTextInInfo(QString newText, int row, int column);
    void insertTextEdit(QLineEdit *text, int row, int column);
    void unMarkerTextInfo(int row, int column);

    void markerFirstColumnForRow(int row);
};
class ResultViewer
{
public:
    ResultViewer();
    Widget * mWidget =nullptr;
    //QList<QList<double>> values;
    //void addValue(QList<double> &value);
    //QWidget*  mWidget;
    //QTextEdit *mIterationCountText;

    void initData(int classes, int containers);
    void upDateData(QList<QList<double> > newData);
    void upDateRow(QList<double> list, int row);
    void upDate(int iteration);
};

#endif // RESULTVIEWER_H
