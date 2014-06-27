# -*- coding:utf-8 -*-

import sys
from PyQt4 import QtGui
from PyQt4 import QtCore


class Clock(QtGui.QWidget):
    hour_point = QtGui.QPolygon([QtCore.QPoint(6, 8),
                                 QtCore.QPoint(0, 4),
                                 QtCore.QPoint(-6, 8),
                                 QtCore.QPoint(0, -50)])
    minute_point = QtGui.QPolygon([QtCore.QPoint(5, 10),
                                   QtCore.QPoint(0, 6),
                                   QtCore.QPoint(-5, 10),
                                   QtCore.QPoint(0, -70)])
    second_point = QtGui.QPolygon([QtCore.QPoint(3, 12),
                                   QtCore.QPoint(0, 8),
                                   QtCore.QPoint(-3, 12),
                                   QtCore.QPoint(0, -90)])
    hour_color = QtGui.QColor(0, 0, 255)
    minute_color = QtGui.QColor(0, 255, 0)
    second_color = QtGui.QColor(255, 0, 0)

    def __init__(self):
        super(Clock, self).__init__()

        self.setWindowFlags(QtCore.Qt.FramelessWindowHint | QtCore.Qt.WindowStaysOnTopHint | QtCore.Qt.SubWindow)
        self.setAttribute(QtCore.Qt.WA_TranslucentBackground, True)

        timer = QtCore.QTimer(self)
        timer.timeout.connect(self.update)
        timer.start(1000)

        quit_action = QtGui.QAction(u"退出", self, shortcut="Ctrl+Q", triggered=QtGui.qApp.quit)
        self.addAction(quit_action)
        self.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)

        self.setToolTip(u"这是一个闹钟")
        self.resize(250, 250)

        self.drag_position = 0
        self.show()

    def mousePressEvent(self, e):
        if e.button() == QtCore.Qt.LeftButton:
            self.drag_position = e.globalPos() - self.frameGeometry().topLeft()
            e.accept()

    def mouseMoveEvent(self, e):
        if e.buttons() == QtCore.Qt.LeftButton:
            self.move(e.globalPos() - self.drag_position)
            e.accept()

    def paintEvent(self, e):
        side = min(self.width(), self.height())
        current_time = QtCore.QTime.currentTime()

        qp = QtGui.QPainter(self)
        qp.setRenderHint(QtGui.QPainter.Antialiasing)
        qp.translate(self.width() / 2, self.height() / 2)
        qp.scale(side / 200.0, side / 200.0)
        
        #时针
        qp.setPen(QtCore.Qt.NoPen)
        qp.setBrush(Clock.hour_color)
        qp.save()

        qp.rotate(30.0 * (current_time.hour() + current_time.minute() / 60.0))
        qp.drawConvexPolygon(Clock.hour_point)
        qp.restore()

        qp.setPen(Clock.hour_color)
        for i in range(12):
            qp.drawLine(88, 0, 96, 0)
            qp.rotate(30.0)

        #分针
        qp.setPen(QtCore.Qt.NoPen)
        qp.setBrush(Clock.minute_color)
        qp.save()

        qp.rotate(6.0 * (current_time.minute() + current_time.second() / 60.0))
        qp.drawConvexPolygon(Clock.minute_point)
        qp.restore()

        qp.setPen(Clock.minute_color)
        for i in range(60):
            if i % 5 != 0:
                qp.drawLine(92, 0, 96, 0)
            qp.rotate(6.0)

        #秒针
        qp.setPen(QtCore.Qt.NoPen)
        qp.setBrush(Clock.second_color)
        qp.save()

        qp.rotate(6.0 * current_time.second())
        qp.drawConvexPolygon(Clock.second_point)
        qp.restore()


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    clock = Clock()
    sys.exit(app.exec_())
