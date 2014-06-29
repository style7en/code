#ifndef CLOCK_H_INCLUDED
#define CLOCK_H_INCLUDED

#include <QWidget>

class Clock: public QWidget
{
    Q_OBJECT
public:
    Clock(QWidget *parent=0);
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CLOCK_H_INCLUDED
