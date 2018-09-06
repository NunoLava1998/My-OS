#include "main.h"

#define irq_start() __asm__ __volatile__ ("pusha; push %ds; push %es")
#define irq_end() __asm__ __volatile__ ("pop %es; pop %ds; popa; mov $0x20, %al; outb %al, $0x20; iret; ret")
volatile uint64_t SYSTICKS;

void pit_irq(void) {
	irq_start();
	SYSTICKS++;
	irq_end();
}

void sleep(uint64_t TICKS) {
	asm("cli"); uint64_t STOPTICK = SYSTICKS + TICKS; asm("sti"); // Don't want this part to be interrupted.
	while(SYSTICKS < STOPTICK);
}

// This is the PIT. It provides a way to keep track of time.
// We set the PIT divisor to 1193. This lets us keep a very
// accurate track of time. In 24 hours, it is only offset by
// 0.43 seconds, which means that in an entire month it will
// only be offset by a total of 13 seconds, and in an entire
// year only by 2.5 minutes. Even for servers, this is very
// accurate for timekeeping. Unfortunately, the PIC also has
// offsets of it's own (1.73 seconds per day), which means
// that it gets offset by 2.16 total seconds per day. This
// isn't a huge problem, but for things like servers it could
// make a difference (servers are typically on for years at
// a time and would need to reset the time every month or so).
// However, we aren't developing a server operating system,
// and therefore this is fine.

// However, relying on the PIT for long term time is a pretty
// bad idea. A 64bit variable *can* be used in 32bit systems,
// so we decide to use that as a 32bit variable can only hold
// 30 minutes worth of time, but a 64bit variable can hold
// 292,277,266 years of time, which is more than enough.