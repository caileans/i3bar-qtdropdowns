#include "QDropDown.h"

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>
#include <iostream>
#include <qlayout.h>


QDropDown::QDropDown(){
    this->init(10, 10, 10, Justification::center, "", "#0000bb", 1, "#aa0000", 1);
}

QDropDown::QDropDown(const int xPos, const int yPos, const int width, Justification justified, const char *qss, const char *borderColor, const int borderSize, const char *secondBorderColor = "", const int secondBorderSize = 1){
    this->init(xPos, yPos, width, justified, qss, borderColor, borderSize, secondBorderColor, secondBorderSize);
}

QDropDown::QDropDown(int argc, char *argv[], QLayout *content) : QDropDown(argc, argv) {
    this -> addContent(content);
}

QDropDown::QDropDown(int argc, char *argv[]) {
    if (argc < 10){
        exit(1);
    }

    const int x = atoi(argv[1]);
    const int y = atoi(argv[2]);
    const int w = atoi(argv[3]);
    const char *just = argv[4];
    // const char just[] = "center";
    Justification justification;
    if (strcmp(just, "left") == 0 || strcmp(just, "0") == 0){
        justification = Justification::left;
    }else if(strcmp(just, "right") == 0 || strcmp(just, "2") == 0){
        justification = Justification::right;
    }else{
        justification = Justification::center;
    }

    const char *qss = argv[5];
    const char *mainBorderColor = argv[6];
    const int mainBorder = atoi(argv[7]);
    const char *secBorderColor = argv[8];
    const int secBorder = atoi(argv[9]);

    this->init(x, y, w, justification, qss, mainBorderColor, mainBorder, secBorderColor, secBorder);
}

void QDropDown::init(const int xPos, const int yPos, const int width, Justification justified, const char *qss, const char *borderColor, const int borderSize, const char *secondBorderColor = "", const int secondBorderSize = 1){
    this -> _xPos = xPos;
    this -> _yPos = yPos;
    this -> _width = width;
    this -> _justified = justified;
    this -> _borderColor = borderColor;
    this -> _borderSize = borderSize;
    this -> _secondBorderColor = secondBorderColor;
    this -> _secondBorderSize = secondBorderSize;
    this -> _qss = qss;


    this -> setWindowFlags(Qt::Popup);
    this -> setStyleSheet(_qss.c_str());
    this -> setModal(true);
}

void QDropDown::paintEvent(QPaintEvent *){
    QPainter qp(this);
    qp.setRenderHints(qp.Antialiasing);

    QRectF rect(this -> rect());
    float half = this->_borderSize / 2.0;
    QPointF btmLft,
        btmRt;

    if (this->_secondBorderColor){
        float mainRectInset = half + this->_secondBorderSize;
        rect.adjust(mainRectInset, mainRectInset, -mainRectInset, -mainRectInset);
        btmLft = QPointF(this->_bottomBorderLeft - half, rect.bottom());
        btmRt = QPointF(this->_bottomBorderRight + half, rect.bottom());

        float secHalf = this->_secondBorderSize / 2.0;
        float secondBorderOffset = half + secHalf;
        QRectF inRect = rect.adjusted(secondBorderOffset, secondBorderOffset, -secondBorderOffset, -secondBorderOffset);
        QRectF outRect = rect.adjusted(-secondBorderOffset, -secondBorderOffset, secondBorderOffset, secondBorderOffset);
        QPointF secInBtmLft(this->_bottomBorderLeft - this->_secondBorderSize, rect.bottom() - secondBorderOffset);
        QPointF secInBtmRt(this->_bottomBorderRight + this->_secondBorderSize, rect.bottom() - secondBorderOffset);
        QPointF secOutBtmLft(this->_bottomBorderLeft - this->_secondBorderSize, rect.bottom() + secondBorderOffset);
        QPointF secOutBtmRt(this->_bottomBorderRight + this->_secondBorderSize, rect.bottom() + secondBorderOffset);

        qp.setPen(QPen(QColor(this->_secondBorderColor), this->_secondBorderSize));


        qp.drawPolyline(QPolygonF({
            secInBtmLft,
            inRect.bottomLeft(),
            inRect.topLeft(),
            inRect.topRight(),
            inRect.bottomRight(),
            secInBtmRt,
            secOutBtmRt,
            outRect.bottomRight(),
            outRect.topRight(),
            outRect.topLeft(),
            outRect.bottomLeft(),
            secOutBtmLft
        }));

    }
    else{
        rect.adjust(half, half, -half, -half);
        btmLft = QPointF(this->_bottomBorderLeft, rect.bottom());
        btmRt = QPointF(this->_bottomBorderRight, rect.bottom());
    }

    qp.setPen(QPen(QColor(this->_borderColor), this->_borderSize));

    qp.drawPolyline(QPolygonF({
        btmLft,
        rect.bottomLeft(),
        rect.topLeft(),
        rect.topRight(),
        rect.bottomRight(),
        btmRt
    }));

    // this->hide()
    // this->setModal(True)
    // this->show()
    this -> clearFocus();
    this -> setFocus();
    this -> grabMouse();
}

void QDropDown::addContent(QLayout *contentLayout){
    this->setLayout(contentLayout);
    this->show();
    this->reposition();
}

void QDropDown::reposition(){
    int x;
    if (this->_justified == Justification::left){
        x = this->_xPos;
        this->_bottomBorderLeft = 0;
        this->_bottomBorderRight = this->_width;
    }
    else if (this->_justified == Justification::right){
        x = this->_xPos - (this->width() - this->_width);
        this->_bottomBorderLeft = this->width() - this->_width;
        this->_bottomBorderRight = this->width();
    }
    else{
        x = this->_xPos - (this->width() - this->_width)/2.0;
        this->_bottomBorderLeft = (this->width() - this->_width)/2.0;
        this->_bottomBorderRight = this->width() - (this->width() - this->_width)/2.0;
    }

    this->move(x, this->_yPos  - this->height());
    this->update();
}

