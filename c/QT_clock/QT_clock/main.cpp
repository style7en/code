#include <QApplication>
#include "clock.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Imm32.lib") 
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Clock clock;
    clock.show();
    return app.exec();
}
