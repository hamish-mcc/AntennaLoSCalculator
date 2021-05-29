#include "antennacalculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AntennaCalculator w;
    w.show();
    return a.exec();
}
