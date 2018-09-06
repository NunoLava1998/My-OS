#include "main.h"

static uint32_t* pagedir = 0;
static uint32_t pagedirl = 0;
static uint32_t* pagelast = 0;

void paging_virtual_to_physical(uint32_t v, uint32_t p) {
	uint16_t ID = v >> 22;
	for(uint32_t i = 0; i < 1024; i++) {
		pagelast[i] = p | 3;
		p += 4096;
	}
	pagedir[ID] = ((uint32_t)pagelast) | 3;
	pagelast = (uint32_t*)(((uint32_t)pagelast) + 4096);
	kreport("Mapped memory", "paging_virtual_to_physical()", 1);
}

void pgeinit(void) {
	kreport("Setting up paging", "pgeinit()", 3);
	pagedir = (uint32_t*)0x4000000;
	pagedirl = (uint32_t)pagedir;
	pagelast = (uint32_t*)0x404000;
	for (uint32_t i = 0; i < 1024; i++) {
		pagedir[i] = 0 | 2;
	}
	paging_virtual_to_physical(0, 0);
	paging_virtual_to_physical(0x4000000, 0x4000000);
	__asm__ __volatile__ ("mov %%eax, %%cr3" : : "a"(pagedirl));
	__asm__ __volatile__ ("mov %cr0, %eax");
	__asm__ __volatile__ ("orl $0x80000000, %eax");
	__asm__ __volatile__ ("mov %eax, %cr0");
	kreport("Paging successfully enabled", "pgeinit()", 3);
}