#include "main.h"

#define isr_start() __asm__ __volatile__ ("pusha; push %ds; push %es")
#define irq_start() __asm__ __volatile__ ("pusha; push %ds; push %es")
#define isr_end() __asm__ __volatile__ ("pop %es; pop %ds; popa; iret; ret")
#define irq_end() __asm__ __volatile__ ("pop %es; pop %ds; popa; mov $0x20, %al; outb %al, $0x20; iret; ret")

void swap(char* a, char* b) {
	char t = *a; *a = *b; *b = t;
}

char* reverse(char* buf, uint32_t i, uint32_t j) {
	while (i > j) {
		swap(&buf[i++], &buf[j--]);
	}
	return buf;
}

char* itoa(uint32_t value, char* buf, uint8_t base) {
	if ((base < 2) || (base > 32)) {
		return buf;
	}
	int n = value;
	int i = 0;
	while(n) {
		int r = n % base;
		if (r >= 10) {
			buf[i++] = 65 + (r - 10);
		} else {
			buf[i++] = 48 + r;
		}
		n = n / base;
	}
	if (i == 0) {
		buf[i++] = '0';
	}
	buf[i] = '\0';
	return reverse(buf, 0, (i - 1));
}

void isr_handler(int errnum) {
	char buf[4];
	buf[0] = 0; buf[1] = 0; buf[2] = 0; buf[3] = 0;
	vx = 0; vy = 0; memset((void*)0xB8000, 0, 4000);
	puts("An error has occured.\n", 0x0F);
	puts("There might be faulty hardware or software causing this error.\n", 0x0F);
	puts("Exception code: 0x", 0x0F);
	const char* errnum_s = itoa(errnum, buf, 16);
	puts(errnum_s, 0x0F);
	puts(". The system will now permanently stop.", 0x0F);
	STOP();
}

// start("wall of text");

void isr0(void) {
	isr_start();
	isr_handler(0);
	isr_end();
}

void isr1(void) {
	isr_start();
	isr_handler(1);
	isr_end();
}

void isr2(void) {
	isr_start();
	isr_handler(2);
	isr_end();
}

void isr5(void) {
	isr_start();
	isr_handler(5);
	isr_end();
}

void isr6(void) {
	isr_start();
	isr_handler(6);
	isr_end();
}

void isr7(void) {
	isr_start();
	isr_handler(7);
	isr_end();
}

void isr8(void) {
	isr_start();
	isr_handler(8);
	isr_end();
}

void isr9(void) {
	isr_start();
	isr_handler(9);
	isr_end();
}

void isr10(void) {
	isr_start();
	isr_handler(10);
	isr_end();
}

void isr11(void) {
	isr_start();
	isr_handler(11);
	isr_end();
}

void isr12(void) {
	isr_start();
	isr_handler(12);
	isr_end();
}

void isr13(void) {
	isr_start();
	isr_handler(13);
	isr_end();
}

void isr14(void) {
	isr_start();
	isr_handler(14);
	isr_end();
}

void isr16(void) {
	isr_start();
	isr_handler(16);
	isr_end();
}

void isr17(void) {
	isr_start();
	isr_handler(17);
	isr_end();
}

void isr19(void) {
	// "it's 0x13" but it's actually SIMD Floating Point Exception not GPF
	isr_start();
	isr_handler(19);
	isr_end();
}

void isr20(void) {
	isr_start();
	isr_handler(20);
	isr_end();
}

void isr30(void) {
	isr_start();
	isr_handler(30);
	isr_end();
}

void isr(void) {
	isr_start();
	isr_end();
}

void irq(void) {
	irq_start();
	irq_end();
}

// end("wall of text");

struct idtt {
	uint16_t base_low;
	uint16_t selector;
	uint8_t null;
	uint8_t flags;
	uint16_t base_high;
} __attribute__ ((packed));

struct idtp {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

struct idtt idte[256];
struct idtp idtp;

void idtentry(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
	idte[num].base_low = base;
	idte[num].base_high = (base >> 16);
	idte[num].selector = selector;
	idte[num].null = 0;
	idte[num].flags = flags;
}

extern void idtldr(void);

void idtinit(void) {
	uint16_t idt_SZ = sizeof(idte);
	idtp.limit = (idt_SZ * 256) - 1;
	idtp.base = (uint32_t)&idte;
	memset(&idte, '\0', 256);
	// start("wall of text 2.0");
	idtentry(0, (unsigned)isr0, 0x08, 0x8E); // ISR0
	idtentry(1, (unsigned)isr1, 0x08, 0x8E); // ISR1
	idtentry(2, (unsigned)isr2, 0x08, 0x8E); // ISR2
	idtentry(3, (unsigned)isr, 0x08, 0x8E); // ISR3
	idtentry(4, (unsigned)isr, 0x08, 0x8E); // ISR4
	idtentry(5, (unsigned)isr5, 0x08, 0x8E); // ISR5
	idtentry(6, (unsigned)isr6, 0x08, 0x8E); // ISR6
	idtentry(7, (unsigned)isr7, 0x08, 0x8E); // ISR7
	idtentry(8, (unsigned)isr8, 0x08, 0x8E); // ISR8
	idtentry(9, (unsigned)isr9, 0x08, 0x8E); // ISR9
	idtentry(10, (unsigned)isr10, 0x08, 0x8E); // ISR10
	idtentry(11, (unsigned)isr11, 0x08, 0x8E); // ISR11
	idtentry(12, (unsigned)isr12, 0x08, 0x8E); // ISR12
	idtentry(13, (unsigned)isr13, 0x08, 0x8E); // ISR13
	idtentry(14, (unsigned)isr14, 0x08, 0x8E); // ISR14
	idtentry(15, (unsigned)isr, 0x08, 0x8E); // ISR15
	idtentry(16, (unsigned)isr16, 0x08, 0x8E); // ISR16
	idtentry(17, (unsigned)isr17, 0x08, 0x8E); // ISR17
	idtentry(18, (unsigned)isr, 0x08, 0x8E); // ISR18
	idtentry(19, (unsigned)isr19, 0x08, 0x8E); // ISR19
	idtentry(20, (unsigned)isr20, 0x08, 0x8E); // ISR20
	idtentry(21, (unsigned)isr, 0x08, 0x8E); // ISR21
	idtentry(22, (unsigned)isr, 0x08, 0x8E); // ISR22
	idtentry(23, (unsigned)isr, 0x08, 0x8E); // ISR23
	idtentry(24, (unsigned)isr, 0x08, 0x8E); // ISR24
	idtentry(25, (unsigned)isr, 0x08, 0x8E); // ISR25
	idtentry(26, (unsigned)isr, 0x08, 0x8E); // ISR26
	idtentry(27, (unsigned)isr, 0x08, 0x8E); // ISR27
	idtentry(28, (unsigned)isr, 0x08, 0x8E); // ISR28
	idtentry(29, (unsigned)isr, 0x08, 0x8E); // ISR29
	idtentry(30, (unsigned)isr30, 0x08, 0x8E); // ISR30
	idtentry(31, (unsigned)isr, 0x08, 0x8E); // ISR31
	idtentry(32, (unsigned)pit_irq, 0x08, 0x8E); // IRQ0
	idtentry(33, (unsigned)irq, 0x08, 0x8E); // IRQ1
	idtentry(34, (unsigned)irq, 0x08, 0x8E); // IRQ2
	idtentry(35, (unsigned)irq, 0x08, 0x8E); // IRQ3
	idtentry(36, (unsigned)irq, 0x08, 0x8E); // IRQ4
	idtentry(37, (unsigned)irq, 0x08, 0x8E); // IRQ5
	idtentry(38, (unsigned)irq, 0x08, 0x8E); // IRQ6
	idtentry(39, (unsigned)irq, 0x08, 0x8E); // IRQ7
	idtentry(40, (unsigned)irq, 0x08, 0x8E); // IRQ8
	idtentry(41, (unsigned)irq, 0x08, 0x8E); // IRQ9
	idtentry(42, (unsigned)irq, 0x08, 0x8E); // IRQ10
	idtentry(43, (unsigned)irq, 0x08, 0x8E); // IRQ11
	idtentry(44, (unsigned)irq, 0x08, 0x8E); // IRQ12
	idtentry(45, (unsigned)irq, 0x08, 0x8E); // IRQ13
	idtentry(46, (unsigned)irq, 0x08, 0x8E); // IRQ14
	idtentry(47, (unsigned)irq, 0x08, 0x8E); // IRQ15
	// end("wall of text 2.0");
	kreport("Initialized IDT entries", "idtinit()", 1);
	SYSTICKS = 0; // SYSTICKS is uninitialized by default
	outb(0x43, 0x36); // Command to set PIT frequency
	outb(0x40, (1193 & 0xFF)); // Lower byte
	outb(0x40, (1193 >> 8)); // Higher byte
	kreport("Initialized PIT, but not ready", "idtinit()", 1);
	idtldr(); // Load the IDT itself
	// Done! 
}

