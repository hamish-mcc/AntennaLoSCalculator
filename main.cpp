#include "antennacalculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AntennaCalculator w;
    w.setWindowTitle("Antenna LoS Calculator");
    w.show();
    return a.exec();
}
