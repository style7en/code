#include <QApplication>
#include "test.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Test test;
    test.show();
    return app.exec();
}
