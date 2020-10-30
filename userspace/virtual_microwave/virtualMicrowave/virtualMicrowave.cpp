#include "virtualMicrowave.h"
#include "ui_virtualMicrowave.h"

#include "../../src/microwave/microwave.h"
#include "../../src/states/init.h"


void VirtualMicrowave::displayNumber(long value)
{
    this->ui->DisplayLabel->setText(QString::number(value));
}

void VirtualMicrowave::displayTime(long t)
{
    unsigned int value = ((long) t) % 10000;
    unsigned int time = value % 60;
    value /= 60;
    time += 100 * value;

    this->displayNumber(time);
}

void VirtualMicrowave::run()
{
    Microwave microwave = Microwave(new MStateContext(new Init(), this, this), this);
    while(1)
    {
        microwave.run();
    }
}

VirtualMicrowave::VirtualMicrowave(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VirtualMicrowave)
{
    ui->setupUi(this);
    this->m_duration = 30;
    this->m_power = 900;

    this->run();
}

VirtualMicrowave::~VirtualMicrowave()
{
    delete ui;
}

void VirtualMicrowave::display(long t, DISPLAY_TYPE type)
{
    switch(type)
    {
    case TIME:
        this->displayTime(t);
        break;
    case NUMBER:
        this->displayNumber(t);
        break;
    }
}

void VirtualMicrowave::displayOSTime()
{
    time_t       now   = time(NULL);
    tm*          gmnow = gmtime(&now);
    unsigned int value = gmnow->tm_hour * 100 + gmnow->tm_min;

    displayNumber(value);
}

void VirtualMicrowave::setRadiator(unsigned int value)
{
    this->ui->RadiatorLEDlbl->setText(QString::number(value));
}

void VirtualMicrowave::setOvenLED(PIN_STATE state)
{
    this->ui->MicrowaveLEDlbl->setText(state == HIGH ? "ON" : "OFF");
}

void VirtualMicrowave::setMemoryLED(PIN_STATE state)
{
    this->ui->MemorLEDlbl->setText(state == HIGH ? "ON" : "OFF");
}

time_t VirtualMicrowave::getDuration()
{
    return this->m_duration;
}

int VirtualMicrowave::getPower()
{
    return this->m_power;
}

void VirtualMicrowave::save(unsigned int power, time_t duration)
{
    this->ui->loggingInfo->appendPlainText("Update power and Duration");
    this->ui->loggingInfo->appendPlainText(QString::number(power));
    this->ui->loggingInfo->appendPlainText(QString::number(duration));
}

int VirtualMicrowave::getTimeDial()
{
    return this->timeDialState;
}

int VirtualMicrowave::getButtons()
{
    return this->btnState;
}


