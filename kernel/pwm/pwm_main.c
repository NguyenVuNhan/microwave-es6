#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <mach/hardware.h>

#define PWM_CTRL		0x4005c000
#define PWMCLK_CTRL		0x400040b8

#define PWM_EN	31
#define PWM_RELOADV		8
#define PWM_DUTY		0

#define PWMCLK_FREQ  		4
#define PWMCLK_SOURCE		1
#define PWMCLK_ENABLE		0


#define RTC_CLK_SPEED		32000
#define PERIPH_CLK_SPEED	13000000


volatile unsigned int *pwmAddress = io_p2v(PWM_CTRL);
volatile unsigned int *clockAddress = io_p2v(PWMCLK_CTRL);

static int device_Open = 0;

ssize_t pwm_write(struct file *file, const char __user *user_buffer,
		       size_t count, loff_t *offset)
{
	int minor;
	minor =	(int)(long) file->private_data;

	switch (minor)
	{
		case 0:
		{
            ssize_t mask;

            int duty, power;

            if(sscanf(user_buffer, "%d", &power) != 1)
            {
                printk("invalid power value\n");
            }
            if (power < 0 || power > 900 )
			{
				pr_info("PWM Error: Invalid value, expected 0-900, got: %d\n", power);
				return EINVAL;
			}
            duty = 255 - (((power * 100) / 900 * 254) / 100);

            mask = 0xFF << PWM_DUTY;
            *pwmAddress = ((*pwmAddress) & ~(mask)) | (duty << PWM_DUTY);
			break;
		}
		default:
		{
			return -EINVAL;
		}
	}
	return count;
}

static int pwm_open(struct inode *inode, struct file *file)
{
	if (device_Open)
		return -EBUSY;

	device_Open++;
	try_module_get(THIS_MODULE);

	file->private_data = (void *)(long) iminor(inode);
	return 0;
}

static int pwm_release(struct inode *inode, struct file *file)
{
	device_Open--;

	module_put(THIS_MODULE);

	return 0;
}

static struct file_operations simple_driver_fops =
{
	.owner = THIS_MODULE,
	.open = pwm_open,
	.release = pwm_release,
	.write = pwm_write
};

static int device_file_major_number = 0;
static const char device_name[] = "pwm-driver";
static int register_device(void)
{
	int result = 0;
	printk( KERN_NOTICE "pwm-driver: register_device() is called." );
	result = register_chrdev( device_file_major_number, device_name, &simple_driver_fops );
	if( result < 0 )
	{
		printk( KERN_WARNING "pwm-driver:  can\'t register character device with errorcode = %i", result );
		return result;
	}
	device_file_major_number = result;
	printk( KERN_NOTICE "pwm-driver: registered character device with major number = %i and minor numbers 0...255", device_file_major_number );
	return 0;
}

void unregister_device(void)
{
	printk( KERN_NOTICE "pwm-driver: unregister_device() is called" );
	if(device_file_major_number != 0)
	{
		unregister_chrdev(device_file_major_number, device_name);
	}
}

static int pwm_init(void)
{
    ssize_t mask;

    register_device();

    mask = 0xFF << PWM_RELOADV;
    *pwmAddress = ((*pwmAddress) & ~(mask)) | (1 << PWM_RELOADV);

    mask = 1 << PWM_EN;
    *pwmAddress = (*pwmAddress & ~(mask)) | (1 << PWM_EN);

    mask = 0xFF << PWM_DUTY;
    *pwmAddress = ((*pwmAddress) & ~(mask)) | (0xFF << PWM_DUTY);

    mask = 0xF << PWMCLK_FREQ;
    *clockAddress = ((*clockAddress) & ~(mask)) | (1 << PWMCLK_FREQ);

    mask = 1 << PWMCLK_SOURCE;
    *clockAddress = ((*clockAddress) & ~(mask)) | (0 << PWMCLK_SOURCE);

    mask = 1 << PWMCLK_ENABLE;
    *clockAddress = ((*clockAddress) & ~(mask)) | (1 << PWMCLK_ENABLE);

	return  0;
}

static void pwm_exit(void)
{
	unregister_device();
	return;
}

module_init(pwm_init);
module_exit(pwm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huy Laurens Nhan");
MODULE_DESCRIPTION("PWM driver");
