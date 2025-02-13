#include "resultchecker.h"
#include <QDebug>
#include <qevent.h>
#include <qpainter.h>

QColor PixelFrame::mColoredPixelColor = Qt::black;
QColor PixelFrame::mUnColoredPixelColor = Qt::white;
QColor ResultChecker::mResultPersendTextColor = Qt::green;

int ResultView::getMaxIdFormList(QList<double> &list){
    int max = 0;
    for (int i = 0; i < list.size(); i++){
        if (list[i] > list[max]){
            max = i;
        }
    }
    return max;
}
int ResultChecker::getMaxIdFromList(QList<double> &list){
    int max = 0;
    for (int i = 0; i < list.size(); i++){
        if (list[i] > list[max]){
            max = i;
        }
    }
    return max;
}
double ResultChecker::getPersentForMaxId(QList<double> &data){
    double sum  = 0;
    for (double element : data){
//        if (element <= 0){
//            continue;
//        }
//        else{
            sum+=fabs(element);
        //}
    }
    return (fabs(data[getMaxIdFromList(data)])/sum)*100.0;
}
ResultChecker::ResultChecker(NumberRecognizer *network):QWidget()
{
    _network = network;
    resize(800,600);
    _pixelFrame = new PixelFrame(this,network->getHerons()->getLayers().first()->getInputSize().width,
                                 network->getHerons()->getLayers().first()->getInputSize().height);
    _layout = new QHBoxLayout();
    _layout->addWidget(_pixelFrame);
    _layout->setStretchFactor(_pixelFrame,10);
    _toolPanel = new QWidget();
    _toolPanelLayout = new QVBoxLayout();

    _calculateButton = new QPushButton("Get result");

    QObject::connect(_calculateButton,SIGNAL(clicked()),this,SLOT(onCalculateButton()));
    //_calculateButton->setMaximumSize(QSize(100,100));
    _toolPanelLayout->addWidget(_calculateButton);
    _result = new ResultView(10);

//    _resultPersent = new QTextEdit("Udefinded");
//    _resultPersent->setReadOnly(true);
//    _resultPersent->setTextColor(mResultPersendTextColor);
//    _resultPersent->setFont(QFont("Arial Black", 13));

    _toolPanelLayout->addWidget(_result);
    //_toolPanelLayout->addWidget(_resultPersent);
    _toolPanel->setLayout(_toolPanelLayout);


    _layout->addWidget(_toolPanel);
    _layout->setStretchFactor(_toolPanel,2);
    //_layout->addWidget(_resultPersent);
    setLayout(_layout);
    _pixelFrame->setFocus();
    show();
}

void ResultChecker::paintEvent(QPaintEvent *event)
{
}

NumberRecognizer *ResultChecker::network() const
{
    return _network;
}

void ResultChecker::onCalculateButton()
{
    QList<double> result = _network->recognize(_pixelFrame->getMatrix());
    _result->upDateResult(result);
//    _resultPersent->setText(QString::number(getMaxIdFromList(result))+ " "  + QString::number(getPersentForMaxId(result))+ "%");
}

void PixelFrame::paintEvent(QPaintEvent *event)
{
    updateRects();
    QPainter painter;
    painter.begin(this);
    QBrush brush();

    painter.setPen(Qt::white);
    painter.setBrush(Qt::black);
    for (Pixel pixel :_pixels){
        pixel.paint(painter);
    }
    //painter.drawRect(0,0,width(),height());
    painter.end();

}

PixelFrame::PixelFrame(QWidget *parent, int width, int height):QWidget(),_parent(parent), _sizeX(width), _sizeY(height)
{
    //resize(parent->height(),parent->height());
}

void PixelFrame::updateRects()
{
    QSize cellSize = QSize(width()/_sizeX,height()/ _sizeY);
    if (_pixels.size() == 0){
        for (int y = 0; y < _sizeY ; y++){
            for (int x = 0; x < _sizeX; x++){
                _pixels.append(Pixel(QRect(QPoint(x*cellSize.width(),y*cellSize.height()), cellSize),x,y));
            }
        }
        _lastHeight = height();
        _lastWidth = width();

    }
    else{
        if (width() != _lastWidth || height() != _lastHeight){
            //_pixels.clear();
            //qDebug() << _pixels.size();
            for (int y = 0; y < _sizeY ; y++){
                for (int x = 0; x < _sizeX; x++){
                    //qDebug() << x*y;
                    _pixels[x+y*_sizeX].setRect(QRect(QPoint(x*cellSize.width(),y*cellSize.height()), cellSize));
                }
            }
            _lastHeight = height();
            _lastWidth = width();
        }
    }
}

QList<QList<double>> PixelFrame::getMatrix()
{
    QList<QList<double>> result;
    for (int y = 0; y < _sizeY; y++){
        result.append(QList<double>());
        for (int x =0; x < _sizeX; x++){
            result.last().append((int)_pixels[y+x*_sizeY].isColored);
        }
    }
    return result;
}

void PixelFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressed){
        QPoint point = mapFromGlobal(QCursor::pos());
        //qDebug() << "pressed" << point;
        //isPressed = true;
        for (Pixel &pixel : _pixels){
            if (pixel.mRect.contains(point)){
                if (event->buttons() == Qt::RightButton){
                    pixel.unColor();
                    break;

                }
                if (event->buttons() == Qt::LeftButton){
                    pixel.color();
                    break;
                }
            }
        }
        update();
    }
}

void PixelFrame::mousePressEvent(QMouseEvent *event)
{
    QPoint point = mapFromGlobal(QCursor::pos());
    //qDebug() << "pressed" << point;
    isPressed = true;
    for (Pixel &pixel : _pixels){
        if (pixel.mRect.contains(point)){

            if (event->button()== Qt::RightButton){
                pixel.unColor();
                break;

            }
            if (event->button() == Qt::LeftButton){
                pixel.color();
                break;
            }
        }
    }
    update();
}

void PixelFrame::mouseReleaseEvent(QMouseEvent *event)
{
    isPressed = false;
}


void Pixel::setRect(const QRect &rect)
{
    mRect = rect;
}

Pixel::Pixel(QRect rect, int x, int y):mRect(rect),mX(x), mY(y)
{

}

void Pixel::paint(QPainter &painter)
{
    if (isColored){
        painter.setBrush(QBrush(PixelFrame::mColoredPixelColor));
    }
    else{
        painter.setBrush(QBrush(PixelFrame::mUnColoredPixelColor));
    }
    painter.drawRect(mRect);

}

void Pixel::color()
{
    isColored = true;
}

void Pixel::unColor()
{
    isColored = false;
}

ResultView::ResultView(int countClasses)
{
    _layout = new QVBoxLayout();
    for (int i = 0; i < countClasses; i++){
        _labels.append(new QLabel("udefinded"));
        _layout->addWidget(_labels[i]);
    }
    setLayout(_layout);



}

void ResultView::upDateResult(QList<double> data)
{
    if (data.size() != _labels.size()){
        qDebug() << "ResultView::upDateResult(QList<double> data): badData.";
    }
    for (int i =0 ; i < data.size(); i++){
        _labels[i]->setText(QString::number(data[i]));
    }
    _labels[getMaxIdFormList(data)]->setText(QString::number(getMaxIdFormList(data)) + " max " + QString::number(data[getMaxIdFormList(data)]));
    update();

}
