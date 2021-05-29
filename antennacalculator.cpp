#include "antennacalculator.h"
#include "ui_antennacalculator.h"
#include <math.h>
#include <QtCharts>
#include <QColor>

AntennaCalculator::AntennaCalculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AntennaCalculator)
{
    ui->setupUi(this);
}

AntennaCalculator::~AntennaCalculator()
{
    delete ui;
}

void AntennaCalculator::updateDisplay()
{
    // Get values
    int tilt = ui->downTiltInput->value();
    int bw = ui->beamWidthInput->value();
    int aob = ui->aobInput->value();
    int alt = ui->altitudeInput->value();

    // Convert altitude to NM
    double altNm = (alt * 0.00016457883);
    // Convert degrees to radians
    double Q = (90 - aob - tilt) * (M_PI / 180);
    // Stand off = altitude * tan(antenna down tilt)
    double stoff = altNm * tan(Q);

    // Update display
    ui->standOffValue->display(stoff);

    // Stand off vs Altitude
    QLineSeries *los = new QLineSeries();
    los->append(0, alt);
    los->append(stoff, 0);
    los->setColor(QColor(0, 255, 0, 255));

    // Inner azimuth
    double innerQ = (90 - aob - tilt - (bw / 2)) * (M_PI / 180);
    double innerAz = altNm * tan(innerQ);
    QLineSeries *inner = new QLineSeries();
    inner->append(0, alt);
    inner->append(innerAz, 0);
    inner->setColor(QColor(255, 0, 0, 127));

    // Outer azimuth
    double outerQ = (90 - aob - tilt + (bw / 2)) * (M_PI / 180);
    double outerAz = altNm * tan(outerQ);
    QLineSeries *outer = new QLineSeries();
    outer->append(0, alt);
    outer->append(outerAz, 0);
    outer->setColor(QColor(255, 0, 0, 127));

    // Add data to chart
    QChart *fig = new QChart();
    fig->addSeries(los);
    fig->addSeries(inner);
    fig->addSeries(outer);
    fig->legend()->hide();
    fig->createDefaultAxes();
    fig->setTitle("LoS Profile");

    // Add chart to layout
    delete ui->figLayout->takeAt(0);
    QChartView *figView = new QChartView(fig);

    ui->figLayout->addWidget(figView);
}


void AntennaCalculator::on_downTiltInput_valueChanged()
{
    updateDisplay();
}


void AntennaCalculator::on_beamWidthInput_valueChanged()
{
    updateDisplay();
}


void AntennaCalculator::on_aobInput_valueChanged()
{
    updateDisplay();
}


void AntennaCalculator::on_altitudeInput_valueChanged()
{
    updateDisplay();
}


