#ifndef VIRTUALMICROWAVE_H
#define VIRTUALMICROWAVE_H

#include <QMainWindow>
#include "../../src/hardware/display_abstraction.h"
#include "../../src/hardware/memory_abstraction.h"
#include "../../src/hardware/statusChecker_abstraction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VirtualMicrowave; }
QT_END_NAMESPACE

class VirtualMicrowave : public QMainWindow
                       , public IDisplayControl
                       , public IStatusChecker
                       , public IMemoryHandler
{
    Q_OBJECT
private:
    void displayNumber(long value);
    void displayTime(long t);
    void run();
public:
    VirtualMicrowave(QWidget *parent = nullptr);
    ~VirtualMicrowave();

    void display(long t, DISPLAY_TYPE type);
    void displayOSTime();
    void setRadiator(unsigned int value);
    void setOvenLED(PIN_STATE state);
    void setMemoryLED(PIN_STATE state);

    time_t getDuration();
    int    getPower();
    void   save(unsigned int power, time_t duration);

    virtual int getTimeDial();
    virtual int getButtons();

private:
    Ui::VirtualMicrowave *ui;
    time_t m_duration;
    int m_power;
    int btnState;
    int timeDialState;
};
#endif // VIRTUALMICROWAVE_H
