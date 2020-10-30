#include <linux/kernel.h>
#include <linux/module.h>
#include <mach/hardware.h>

#include "gpio_driver.h"
#include "include/common.h"

#define NO_REG 		NULL

#define P0_OUTP_SET		0x40028044
#define P1_OUTP_SET		0x40028064
#define P2_OUTP_SET		0x40028020
#define P3_OUTP_SET		0x40028004

#define P0_OUTP_CLR		0x40028048
#define P1_OUTP_CLR		0x40028068
#define P2_OUTP_CLR		0x40028024
#define P3_OUTP_CLR		0x40028008

#define P0_DIR_STATE		0x40028058
#define P1_DIR_STATE		0x40028078
#define P2_DIR_STATE		0x40028018
#define P3_DIR_STATE		P2_DIR_STATE

#define P0_INP_STATE		0x40028040
#define P1_INP_STATE		0x40028060
#define P2_INP_STATE		0x4002801C
#define P3_INP_STATE		0x40028000

#define P0_OUTP_STATE		0x4002804C
#define P1_OUTP_STATE		0x4002806C
#define P2_OUTP_STATE		NO_REG
#define P3_OUTP_STATE		0x4002800C

#define P0_DIR_SET		0x40028050
#define P1_DIR_SET		0x40028070
#define P2_DIR_SET		0x40028010
#define P3_DIR_SET		P2_DIR_SET

#define P0_DIR_CLR		0x40028054
#define P1_DIR_CLR		0x40028074
#define P2_DIR_CLR		0x40028014
#define P3_DIR_CLR		P2_DIR_CLR

#define P0_MUX_STATE		0x40028058
#define P1_MUX_STATE		0x40028138
#define P2_MUX_STATE		0x40028030
#define P3_MUX_STATE		0x40028118

#define P0_MUX_SET	    	0x40028058
#define P1_MUX_SET	    	0x40028130
#define P2_MUX_SET		0x40028028
#define P3_MUX_SET		P2_MUX_SET

#define P0_MUX_CLR  		0x40028058
#define P1_MUX_CLR  		0x40028134
#define P2_MUX_CLR		0x4002802C
#define P3_MUX_CLR		P2_MUX_CLR

#define NULL_PIN            255

int setGpioOutput(uint8_t port,
		uint8_t pin,
		uint8_t value)
{
	unsigned int* setOutpAddr[NR_OF_MODES][NR_PORTS] = 
	{	
		{io_p2v(P0_OUTP_CLR), io_p2v(P1_OUTP_CLR), io_p2v(P2_OUTP_CLR), io_p2v(P3_OUTP_CLR)},
		{io_p2v(P0_OUTP_SET), io_p2v(P1_OUTP_SET), io_p2v(P2_OUTP_SET), io_p2v(P3_OUTP_SET)}
	};
	
	int errorCode = checkValidDir(port, pin, value);
	if (errorCode != 0)
		return errorCode;
	else if (port == 3)
		pin += P3_PIN_SHIFT;

	*setOutpAddr[value][port] |= 1 << (pin);

	return 0;
}

int getGpioState(uint8_t port, uint8_t pin)
{	
	unsigned int* readDirAddr[NR_PORTS] =	{io_p2v(P0_DIR_STATE), 
					 		io_p2v(P1_DIR_STATE), 
					 		io_p2v(P2_DIR_STATE), 
					 		io_p2v(P3_DIR_STATE)};
	
	unsigned int* readStateAddr[NR_OF_MODES][NR_PORTS] =
	{
		{io_p2v(P0_INP_STATE),	io_p2v(P1_INP_STATE),	io_p2v(P2_INP_STATE),	io_p2v(P3_INP_STATE)},
		{io_p2v(P0_OUTP_STATE), io_p2v(P1_OUTP_STATE),	NO_REG, 		io_p2v(P3_OUTP_STATE)}
	};

    	uint8_t mode;

	int errorCode = checkValid(port, pin);
	if (errorCode != 0)
		return -2;
	else if (port == 3)
		pin += P3_PIN_SHIFT;

	mode = (*readDirAddr[port] >> pin) & 0x1;
	
	if(mode == Output && port == 2)
	{
		printk(KERN_ERR "No registry exists for reading the output state on port 2");
		return -3;
	}

	return (*readStateAddr[Input][port] >> pin) & 0x1;
}

ssize_t setMux(uint8_t port, uint8_t pin, uint8_t value)
{
    uint8_t P3_GPIO_MUX_PIN[] = {NULL_PIN, NULL_PIN, 0, 1, 4, 5};

    unsigned int* setMuxAddr[NR_OF_STATE][NR_PORTS] =
            {
                    {io_p2v(P0_MUX_CLR), io_p2v(P1_MUX_CLR), io_p2v(P2_MUX_CLR), io_p2v(P3_MUX_CLR)},
                    {io_p2v(P0_MUX_SET), io_p2v(P1_MUX_SET), io_p2v(P2_MUX_SET), io_p2v(P3_MUX_SET)}
            };
    int errorCode;
    errorCode = checkValidState(port, pin, value);
    if (errorCode != 0)
        return errorCode;
    if (port == 3)
    {
        pin = P3_GPIO_MUX_PIN[pin];
    }
    *setMuxAddr[value][port] |= 1 << pin;
    return 0;
}

ssize_t setDirection(uint8_t port, uint8_t pin, uint8_t direction)
{
    unsigned int* setDirAddr[NR_OF_MODES][NR_PORTS] =
            {
                    {io_p2v(P0_DIR_CLR), io_p2v(P1_DIR_CLR), io_p2v(P2_DIR_CLR), io_p2v(P3_DIR_CLR)},
                    {io_p2v(P0_DIR_SET), io_p2v(P1_DIR_SET), io_p2v(P2_DIR_SET), io_p2v(P3_DIR_SET)}
            };

    int errorCode = checkValidDir(port, pin, direction);
    if (errorCode != 0)
        return errorCode;
    else if (port == 3)
        pin += P3_PIN_SHIFT;

    *setDirAddr[direction][port] |= 1 << pin;
    return 0;
}