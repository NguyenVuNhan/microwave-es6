# MICROWAVE

## Design choices

1. Programming language: C

2. Read buttons state in kernel space
	- Kernal space return a binary value reflect the pin state
3. There are three device drivers:
	- Button

		e.g. Control LED
		e.g. Get button state
	- Pwm

		e.g. control radiator (Simulated by a LED)
	- Potention

		e.g. Read Time Dial
4. One file system
	- Configuring for GPIO

## Questions
- What is the distinction between sysfs and devfs? When to use them?
- Is it possible to setting up time (go to TIME_SETUP state) during setting up memory (from MEMORY_SETUP state)?
- Is it possible to setting up time (go to TIME_SETUP state) while microwave is running (in RUNNING state)?
- Does it good to combine btnState to one byte?
- Open file once for read the btnState and close when the userspace program stopj
- Time in LPC is different from real time. What can we do about that?

## Other

### Notes and Ideas
* Using thread worker to check fo btn press evt
* Kernel module
	* Device driver --> devfs
	* File system --> sysfs
* Keeping the same things for the old assignment


26 - 05
- Split state diagram into multipe interface
	- UI classes
	- Microwave class
- Memory setup is extra feature
- Improve od remark
- Implement reentrancy handler



### Task split
**Phase 1: 18/05 - 22/05**

Lauren

	- Find all possible GPIO  pins for button
	- Find out how to use display
	- Find clock pin (use to control the display) (optional)
	- Knob (Research on reading value ob knob) (from adc assignment)
	- PWD (for LED)
Huy, Nhan

	- Design (activity diagram, class diagram, state machine)
