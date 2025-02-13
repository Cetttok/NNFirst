#ifndef RESULTCHECKER_H
#define RESULTCHECKER_H
#include "numberrecognizer.h"

//#include <QFrame>
#include <QWidget>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtextedit.h>
class ResultView : public QWidget
{
public:
    ResultView(int countClasses);
    void upDateResult(QList<double> data);
    int getMaxIdFormList(QList<double> &list);
protected:
    QList<QLabel*> _labels;
    QVBoxLayout* _layout;

};
class Pixel : public QRect
{
public:
    int mX;
    int mY;
    bool isColored = false;
    QRect mRect;

    Pixel(QRect rect, int x, int y);

    void paint(QPainter &painter);
    void color();
    void unColor();


    void setRect(const QRect &rect);
};
class PixelFrame: public QWidget
{
public:
    static QColor mColoredPixelColor;
    static QColor mUnColoredPixelColor;

    void paintEvent(QPaintEvent *event);
    PixelFrame(QWidget * parent, int width, int height);
    void updateRects();
    QList<QList<double> > getMatrix();
protected:
    bool isPressed =false;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QList<Pixel> _pixels;

    int _sizeX;
    int _sizeY;
    QWidget *_parent = nullptr;
    int _lastWidth = 0;
    int _lastHeight = 0;
};

class ResultChecker : public QWidget
{
    Q_OBJECT
public:
    ResultChecker(NumberRecognizer *network);
    void paintEvent(QPaintEvent *event);
//    int getMaxIdFormList(QList<double> &list);
    NumberRecognizer *network() const;
    static QColor mResultPersendTextColor;
protected:
    NumberRecognizer * _network;
    QHBoxLayout *_layout;
    PixelFrame * _pixelFrame;
    //QTextEdit * _resultPersent;
    QPushButton *_calculateButton;
    QWidget *_toolPanel;
    QVBoxLayout *_toolPanelLayout;
    ResultView * _result;
    int getMaxIdFromList(QList<double> &list);
    double getPersentForMaxId(QList<double> &data);
public slots:
    void onCalculateButton();

};

#endif // RESULTCHECKER_H
