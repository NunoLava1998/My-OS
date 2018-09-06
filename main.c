#include "main.h"

void kreport(const char* msg, const char* src, int intensity) {
	// msg: Message to be displayed
	// src: File name
	// intensity: Severity of message
	if (intensity > 3) {
		return;
	}
	if (vx != 0) {
		// Newline
		vx = 0;
		++vy;
		int _testvy_ = (vy + 1);
		if (_testvy_ == 25) {
			_SCROLL_();
		}
	}
	puts("Intensity level ", 0x0F);
	switch(intensity) {
		case 0:
			puts("0", 0x09);
			break;
		case 1:
			puts("1", 0x0A);
			break;
		case 2:
			puts("2", 0x06);
			break;
		case 3:
			puts("3", 0x0C);
			break;
	}
	puts(". Message from ", 0x0F);
	puts(src, 0x0F);
	puts(": ", 0x0F);
	puts(msg, 0x0F);
	puts("\n", 0x0F);
}

void kload(void) {
	vx = 0; vy = 0; memset((void*)0xB8000, 0, 4000);
	gdtinit();
	kreport("GDT initialization successful!", "kload()", 2);
	idtinit();
	kreport("IDT initialization successful!", "kload()", 2);
	picinit();
	kreport("PIC initialization successful!", "kload()", 2);
	asm("sti");
	sleep(1); // Sleeps for 1 millisecond
	kreport("PIT initialization successful!", "kload()", 1);
	pgeinit();
	kreport("Paging successfully initialized!", "kload()", 3);
	for(;;);
}
