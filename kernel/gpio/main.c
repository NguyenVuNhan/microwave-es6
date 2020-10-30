#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <mach/hardware.h>
#include <asm/uaccess.h>

#include "displayHandler/displayHandler.h"
#include "init/startup.h"
#include "gpio/gpio_driver.h"

#define OVEN_LED        0
#define MEM_LED         1
#define sysfs_dir       "microwave"

enum nodeMinors
{
    DISPLAY_CTRL,
    READ_BTNS,
    OVEN_LIGHT,
};

static int device_Open = 0;
static int device_file_major_number = 0;
static const char device_name[] = "microwave-gpio-driver";

static struct kobject *hello_obj = NULL;


ssize_t microWave_write(struct file *file, const char __user *user_buffer,
size_t count, loff_t *offset)
{
    int minor =	(int)(long) file->private_data;

    switch (minor)
    {
        case DISPLAY_CTRL:
        {
            int digitLocation;
            int value;

            if (sscanf(user_buffer, "%d %d", &digitLocation, &value) == -1)
                return -EINVAL;

            setNumber(digitLocation, value);
            return count;
        }

        case OVEN_LIGHT:
        {
            int LED, state;

            if (sscanf(user_buffer, "%d %d", &LED, &state) == -1)
                return -EINVAL;

            if(LED == OVEN_LED)
                setGpioOutput(3, 0, state);
            else if(LED == MEM_LED)
                setGpioOutput(3, 1, state);

            return count;
        }
        default:
        {
            return -EINVAL;
        }
    }
    return count;
}

static int microWave_read(struct file *file,	char __user *user_buffer,
size_t count, loff_t *position)
{
    int minor;
    char* Message_Ptr = "00000000000";

    minor = (int) (long) file->private_data;
    switch (minor)
    {
        case READ_BTNS:
        {
            int8_t timeBtn, stopBtn, startBtn, btn90, btn180, btn360, btn600, btn900, doorState, mBtn;
            int data;
            timeBtn = getGpioState(0, 0);
            data = timeBtn << 9;
            stopBtn = getGpioState(0, 1);
            data += stopBtn << 8;
            startBtn = getGpioState(0, 2);
            data += startBtn << 7;
            btn90 = !getGpioState(2, 0);
            data += btn90 << 6;
            btn180 = getGpioState(0, 5);
            data += btn180 << 5;
            btn360 = getGpioState(0, 6);
            data += btn360 << 4;
            btn600 = getGpioState(0, 3);
            data += btn600 << 3;
            btn900 = getGpioState(0, 4);
            data += btn900 << 2;         
            doorState = !getGpioState(2, 1);
            data += doorState << 1;
            mBtn = !getGpioState(2, 2);
            data += mBtn;
            
            sprintf(Message_Ptr, "%04d", data);

            return simple_read_from_buffer(user_buffer, count, position, Message_Ptr, 4);
        }
        default:
        {
            return -EINVAL;
        }
    }
}

static int microWave_open(struct inode *inode, struct file *file)
{
    if (device_Open)
        return -EBUSY;

    device_Open++;
    try_module_get(THIS_MODULE);

    file->private_data = (void *)(long) iminor(inode);
    return 0;
}

static int microWave_release(struct inode *inode, struct file *file)
{
    device_Open--;

    module_put(THIS_MODULE);

    return 0;
}

static struct file_operations simple_driver_fops =
{
        .owner = THIS_MODULE,
        .open = microWave_open,
        .release = microWave_release,
        .write = microWave_write,
        .read = microWave_read
};

static int register_device(void)
{
    int result = 0;
    result = register_chrdev( device_file_major_number, device_name, &simple_driver_fops );
    if( result < 0 )
    {
        printk(KERN_WARNING "microwave-gpio-driver:  can\'t register character device with errorcode = %i\n", result );
        return result;
    }
    device_file_major_number = result;
    printk( KERN_NOTICE "microwave-gpio-driver: registered character device with major number = %i and minor numbers 0...255\n", device_file_major_number );
    return 0;
}

void unregister_device(void)
{
    if(device_file_major_number != 0)
    {
        unregister_chrdev(device_file_major_number, device_name);
    }
}



static int microWave_init(void)
{
    int result = 0;


    hello_obj = kobject_create_and_add(sysfs_dir, kernel_kobj);
    if (hello_obj == NULL)
    {
        printk (KERN_ERR "microwave-gpio kernel module failed to load: kobject_create_and_add failed\n");
        return -ENOMEM;
    }

    register_device();

    lcdOff();
    initPins();

    return result;
}

static void microWave_exit(void)
{
    kobject_put(hello_obj);
    unregister_device();
    return;
}

module_init(microWave_init);
module_exit(microWave_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huy Laurens Nhan");
MODULE_DESCRIPTION("Microwave driver");