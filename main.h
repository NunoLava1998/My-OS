#include <stdint.h>
#include <stddef.h>

#define CLI() __asm__ __volatile__ ("cli")
#define STI() __asm__ __volatile__ ("sti")
#define STOP() for(;;){ __asm__ __volatile__ ("cli; hlt"); }
#define NOP() asm("nop")
#define GHOSTNOP() asm("")

#ifndef _KERNEL_H_
#define _KERNEL_H_

void kreport(const char*, const char*, int);

void memset(void*, uint8_t, size_t);
void memcpy(void*, void*, size_t);

char* itoa(uint32_t, char*, uint8_t);

volatile uint8_t vx;
volatile uint8_t vy;
void _SCROLL_(void);
void putc(char, uint8_t);
void puts(const char*, uint8_t);

void gdtinit(void);
void idtinit(void);
void picinit(void);

uint8_t inb(uint16_t); 
void outb(uint16_t, uint8_t);

volatile uint64_t SYSTICKS;
void pit_irq(void);
void sleep(uint64_t);

void pgeinit(void);

#endif