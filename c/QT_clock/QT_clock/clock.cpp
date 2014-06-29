#include <QtGui>
#include "clock.h"

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    setWindowTitle("Clock");
    resize(200, 200);
}

void Clock::paintEvent(QPaintEvent *)
{
    static const QPoint hourHand[3] = {
        QPoint(7, 8), QPoint(-7, 8), QPoint(0, -40)};
    static const QPoint minuteHand[3] = {
        QPoint(7, 8), QPoint(-7, 8), QPoint(0, -70)};
    static const QPoint secondHand[3] = {
        QPoint(7, 8), QPoint(-7, 8), QPoint(0, -87)};
    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127);
    QColor secondColor(127, 127, 0);
    int side = qMin(width(), height());
    QTime time = QTime::currentTime();
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    painter.setPen(Qt::NoPen);

    painter.save();
    painter.setBrush(hourColor);
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.save();
    painter.setBrush(minuteColor);
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.save();
    painter.setBrush(secondColor);
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();

    painter.setPen(minuteColor);
    for (int i = 0; i < 60; i++)
    {
        if (i % 5 != 0)
        {
            painter.drawLine(92, 0, 96, 0);
        }
        painter.rotate(6.0);
    }

    painter.setPen(hourColor);
    for (int i = 0; i < 12; i++)
    {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }
}
