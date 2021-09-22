#ifndef QDROPDOWN_H
#define QDROPDOWN_H


#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>


enum Justification {
    left,
    center,
    right
};

class QDropDown: public QDialog {
    private:
        int _borderSize,
        _bottomBorderLeft,
        _bottomBorderRight,
        _xPos,
        _yPos,
        _width,
        _secondBorderSize;
        const char *_borderColor,
        *_secondBorderColor;
        Justification _justified;
    public:
        std::string _qss;

    public:
        QDropDown();

        QDropDown(const int, const int, const int, Justification, const char * , const char *, const int, const char *, const int);

        QDropDown(int, char **, QLayout *);

        QDropDown(int, char **);

        void addContent(QLayout *);

    private:
        void init(const int, const int, const int, Justification, const char * , const char *, const int, const char *, const int);

        void paintEvent(QPaintEvent *);

        void reposition();

        

};

#endif // QDROPDOWN_H
