#ifndef ANTENNACALCULATOR_H
#define ANTENNACALCULATOR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AntennaCalculator; }
QT_END_NAMESPACE

class AntennaCalculator : public QWidget
{
    Q_OBJECT

public:
    AntennaCalculator(QWidget *parent = nullptr);
    ~AntennaCalculator();

private slots:
    void on_downTiltInput_valueChanged();

    void on_beamWidthInput_valueChanged();

    void on_aobInput_valueChanged();

    void on_altitudeInput_valueChanged();

private:
    Ui::AntennaCalculator *ui;
    void updateDisplay();
};
#endif // ANTENNACALCULATOR_H
