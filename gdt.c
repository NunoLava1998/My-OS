#include "main.h"

extern void gdtldr(void);

struct gdtt {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t flags;
	uint8_t base_high;
} __attribute__ ((packed));

struct gdtp {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

struct gdtt gdte[5];
struct gdtp gdtp;

void gdtentry(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	gdte[num].limit_low = limit;
	gdte[num].base_low = base;
	gdte[num].base_mid = (base >> 16);
	gdte[num].base_high = (base >> 24);
	gdte[num].flags = ((limit >> 16) & 0x0F) | (flags & 0xF0);
	gdte[num].access = access;
}

void gdtinit(void) {
	gdtp.limit = (sizeof(gdte) * 5) - 1;
	gdtp.base = (uint32_t)&gdte;
	gdtentry(0, 0, 0, 0, 0);
	gdtentry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdtentry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdtentry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdtentry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	gdtldr();
}