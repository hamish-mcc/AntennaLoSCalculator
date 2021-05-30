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
    double innerQ = (90 - aob - tilt - (bw / 2)) * (M_PI / 180);
    double outerQ = (90 - aob - tilt + (bw / 2)) * (M_PI / 180);
    // Distance = altitude * tan(antenna down tilt)
    double slantRange = altNm * tan(Q);
    double innerAz = altNm * tan(innerQ);
    double outerAz = altNm * tan(outerQ);

    // Update LCD number display
    ui->slantRangeValue->display(slantRange);
    ui->innerAzValue->display(innerAz);
    ui->outerAzValue->display(outerAz);

    // LoS, i.e. slant range vs altitude
    QLineSeries *los = new QLineSeries();
    los->append(-5, (5/0.00016457883) / tan(Q));
    los->append(0, 0);
    los->setColor(QColor(0, 255, 0, 255));

    // Inner azimuth
    QLineSeries *inner = new QLineSeries();
    inner->append(-slantRange, alt);
    inner->append(innerAz - slantRange, 0);
    inner->setColor(QColor(255, 0, 0, 127));

    // Outer azimuth
    QLineSeries *outer = new QLineSeries();
    outer->append(-slantRange, alt);
    outer->append(outerAz - slantRange, 0);
    outer->setColor(QColor(255, 0, 0, 127));

    // Aircraft marker
    QScatterSeries *ac = new QScatterSeries();
    ac->append(-slantRange, alt);
    ac->setMarkerSize(12);

    // Add data to chart
    QChart *fig = new QChart();
    fig->addSeries(los);
    fig->addSeries(inner);
    fig->addSeries(outer);
    fig->addSeries(ac);

    // Configure chart presentation
    fig->legend()->hide();
    fig->setTitle("Profile");
    // TO DO: bold title

    // Configure axes
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(-5, 5);
    axisX->setTitleText("Distance (NM)");
    fig->addAxis(axisX, Qt::AlignBottom);
    inner->attachAxis(axisX);
    los->attachAxis(axisX);
    outer->attachAxis(axisX);
    ac->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 30000);
    axisY->setTitleText("Altitude (ft)");
    fig->addAxis(axisY, Qt::AlignLeft);
    inner->attachAxis(axisY);
    los->attachAxis(axisY);
    outer->attachAxis(axisY);
    ac->attachAxis(axisY);

    // Remove old chart from layout
    delete ui->figLayout->takeAt(0);
    // Add chart to layout
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


