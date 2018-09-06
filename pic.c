#include "main.h"

uint8_t inb(uint16_t port) {
	uint8_t r; __asm__ __volatile__ ("inb %1, %0" : "=a"(r) : "Nd"(port)); return r;
}

void outb(uint16_t port, uint8_t value) {
	__asm__ __volatile__ ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void hwait(void) {
	__asm__ __volatile__ ("jmp 1f\n\t"
						  "1: jmp 2f\n\t"
						  "2: " );
}

void picinit(void) {
	uint8_t m1 = inb(0x21); uint8_t m2 = inb(0xA1);
	outb(0x20, 0x11);
	hwait();
	outb(0xA0, 0x11);
	hwait();
	outb(0x21, 0x20);
	hwait();
	outb(0xA1, 0x28);
	hwait();
	outb(0x21, 4);
	hwait();
	outb(0xA1, 2);
	hwait();
	outb(0x21, 0x01);
	hwait();
	outb(0xA1, 0x01);
	hwait();
	outb(0x21, m1);
	outb(0x21, m2);
	uint16_t p = 0x21;
	uint8_t v = inb(0x21) & ~(1 << 0);
	outb(p, v);
	v = inb(0x21) & ~(1 << 1);
	outb(p, v);
}