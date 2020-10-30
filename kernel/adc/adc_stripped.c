#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include <mach/hardware.h>

#include "adc_stripped.h"
#include "registry_helper.h"

#define DEVICE_NAME     "adc"
#define ADC_NUMCHANNELS 3

// Interrupt line
// Check file ~/felabs/sysdev/tinysystem/linux-2.6.34/arch/arm/mach-lpc32xx/include/mach/irqs.h
#define ADC_IRQ IRQ_LPC32XX_TS_IRQ


struct task_struct*     interruptedProcess;
static unsigned char    adc_channel = 0;
static int              adc_values[ADC_NUMCHANNELS] = {0, 0, 0};
static irqreturn_t      adc_interrupt (int irq, void * dev_id);


static void adc_init (void)
{
	setClock();

	configureForADC();

    startAndResetADC();

    raisingEdgeSensitivityOn();

	//IRQ init
    if (request_irq(ADC_IRQ, adc_interrupt, IRQF_DISABLED, "ADC_IRQ", NULL) != 0)
    {
        printk(KERN_ALERT "ADC IRQ request failed\n");
    }
}


static void adc_start (unsigned char channel)
{
    if (channel >= ADC_NUMCHANNELS)
    {
        channel = 0;
    }

    selectChannel(channel);

    adc_channel = channel;

    startConversion();
}


static irqreturn_t adc_interrupt (int irq, void * dev_id)
{
    adc_values[adc_channel] = getDigitalizedValue();


    // start the next channel:
    adc_channel++;
    if (adc_channel < ADC_NUMCHANNELS)
    {
        adc_start (adc_channel);
    }
    else
    {
        wake_up_process(interruptedProcess);
    }

    return (IRQ_HANDLED);
}


static void adc_exit (void)
{
    free_irq(ADC_IRQ, NULL);

}


static ssize_t device_read (struct file * file, char __user * buf, size_t length, loff_t * f_pos)
{
    char* Message_Ptr = "0000";

    adc_start (0);

    interruptedProcess = current;
    set_current_state(TASK_INTERRUPTIBLE);
    schedule();

    sprintf(Message_Ptr, "%d", adc_values[2]);

    return simple_read_from_buffer(buf, length, f_pos, Message_Ptr, 4);

}


static int device_open (struct inode * inode, struct file * file)
{
    // get channel from 'inode'
    file->private_data = (void *)(long) iminor(inode);

    try_module_get(THIS_MODULE);

    return 0;
}


static int device_release (struct inode * inode, struct file * file)
{
    module_put(THIS_MODULE);
	return 0;
}


static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .read = device_read,
    .open = device_open,
    .release = device_release
};


static struct chardev
{
    dev_t       dev;
    struct cdev cdev;
} adcdev;


int adcdev_init (void)
{
    // try to get a dynamically allocated major number
    int error;
    int* registry = io_p2v(0x40048004);
	error = alloc_chrdev_region(&adcdev.dev, 0, ADC_NUMCHANNELS, DEVICE_NAME);;

    *registry &=  0xFFF0;
	if(error < 0)
	{
		// failed to get major number for our device.
		printk(KERN_WARNING DEVICE_NAME ": dynamic allocation of major number failed, error=%d\n", error);
		return error;
	}

	printk(KERN_INFO DEVICE_NAME ": major number=%d\n", MAJOR(adcdev.dev));

	cdev_init(&adcdev.cdev, &fops);
	adcdev.cdev.owner = THIS_MODULE;
	adcdev.cdev.ops = &fops;

	error = cdev_add(&adcdev.cdev, adcdev.dev, ADC_NUMCHANNELS);
	if(error < 0)
	{
		// failed to add our character device to the system
		printk(KERN_WARNING DEVICE_NAME ": unable to add device, error=%d\n", error);
		return error;
	}

	adc_init();

	return 0;
}


/*
 * Cleanup - unregister the appropriate file from /dev
 */
void cleanup_module()
{
	cdev_del(&adcdev.cdev);
	unregister_chrdev_region(adcdev.dev, ADC_NUMCHANNELS);

	adc_exit();
}


module_init(adcdev_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nhan Nguyen, Huy Nguyen & Laurens Schaap");
MODULE_DESCRIPTION("ADC Driver");
