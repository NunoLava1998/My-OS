#include "main.h"

static void putsd(const char* s, uint64_t delay, uint8_t c) {
	size_t sz = 0;
	while(s[sz])
		sz++;
	for (size_t tring = 0; tring < sz; tring++) {
		sleep(delay);
		putc(s[tring], c);
	}
}

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

void gnumsg(void) {
	puts("\nNOTICE:", 0xF0);
	puts("\nRingfire OS\n", 0x0F);
	puts("Copyright (C) 2018 NunoLava1998\n", 0x0F);
	puts("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n", 0x0F);
	puts("This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n", 0x0F);
	puts("You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.\n", 0x0F);
	puts("If needed, please contact me at my GitHub account \"NunoLava1998\"\n", 0x0F);
}

void kstart(void) {
	const char* this = "kstart()";
	cls();
	gdtinit();
	kreport("GDT initialization successful!", this, 2);
	idtinit();
	kreport("IDT initialization successful!", this, 2);
	picinit();
	kreport("PIC initialization successful!", this, 2);
	STI();
	kreport("PIT initialization successful!", this, 1);
}

void kload(void) {
	kstart(); cls(); gnumsg();
	putsd("\n\nWelcome to Ringfire.", 25, 0x0F);
	for(;;);
}
