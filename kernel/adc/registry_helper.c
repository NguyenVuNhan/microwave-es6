#include <linux/kernel.h>
#include <mach/hardware.h>
#include <mach/platform.h>

#include "registry_helper.h"

#define _ADCREG(x)         (LPC32XX_ADC_BASE + (x))
#define LPC32XX_ADC_SELECT _ADCREG(0x004)
#define LPC32XX_ADC_CTRL   _ADCREG(0x008)
#define LPC32XX_ADC_VALUE  _ADCREG(0x048)
#define _SIC2REG(x)        (LPC32XX_SIC2_BASE + (x))
#define LPC32XX_SIC2_APR   _ADCREG(0x00C)
#define LPC32XX_SIC2_ATR   _ADCREG(0x010)

//#define ADCLK_CTRL  io_p2v(LPC32XX_CLKPWR_ADC_CLK_CTRL)
#define	ADCLK_CTRL			io_p2v(0x400040B4)
//#define ADCLK_CTRL1 io_p2v(LPC32XX_CLKPWR_ADC_CLK_CTRL_1)
#define	ADCLK_CTRL1			io_p2v(0x40004060)
#define ADC_SELECT  io_p2v(LPC32XX_ADC_SELECT)
#define ADC_CTRL    io_p2v(LPC32XX_ADC_CTRL)
#define ADC_VALUE   io_p2v(LPC32XX_ADC_VALUE)
#define SIC2_APR    io_p2v(LPC32XX_SIC2_APR)
#define SIC2_ATR    io_p2v(LPC32XX_SIC2_ATR)

#define AD_STROBE_POS      1
#define ADC_CRTL_POWER_POS 2
#define SERVICE_N_POS      23

#define READ_REG(a)     (*(volatile unsigned int*) (a))
#define WRITE_REG(b, a) (*(volatile unsigned int*) (a) = (b))

void setClock(void)
{
    unsigned long data;

    data = READ_REG(ADCLK_CTRL);
    data |= 0x1;
    WRITE_REG(data, ADCLK_CTRL);

    data = READ_REG(ADCLK_CTRL1);
    data &= ~0x01ff;
    WRITE_REG(data, ADCLK_CTRL1);
}


void configureForADC(void)
{
    unsigned long data;

    data = READ_REG(ADC_SELECT);
    data &= ~0x03c0;
    data |= 0x0280;
    data &= ~0x0030;
    data |= 0x0020;
    WRITE_REG(data, ADC_SELECT);
}


void startAndResetADC(void)
{
    unsigned long data;

    data = READ_REG(ADC_CTRL);
    data |= (1 << ADC_CRTL_POWER_POS);
    WRITE_REG(data, ADC_CTRL);
}


void raisingEdgeSensitivityOn(void)
{
    unsigned long data = READ_REG(SIC2_APR);
    data |= 1 << SERVICE_N_POS; // check table 62
    WRITE_REG(data, SIC2_APR);

    data = READ_REG(SIC2_ATR);
    data |= 1 << SERVICE_N_POS; // check table 65
    WRITE_REG(data, SIC2_ATR);
}


void selectChannel(unsigned char channel)
{
    unsigned long data;

    data = READ_REG(ADC_SELECT);
    WRITE_REG((data & ~0x0030) | ((channel << 4) & 0x0030), ADC_SELECT);
}


void startConversion(void)
{
    unsigned long data;

    data = READ_REG(ADC_CTRL);
    data |= 1 << AD_STROBE_POS;
    WRITE_REG(data, ADC_CTRL);
}


int getDigitalizedValue(void)
{
    unsigned long data = READ_REG(ADC_VALUE);
    return data & 0x3FF;
}

