#include "main.h"

volatile uint8_t vx;
volatile uint8_t vy;
uint16_t* vptr = (uint16_t*)0x000B8000;

static int is_special(char c) {
	if ((c == '\n') || (c == '\t')) {
		return 1;
	} else {
		return 0;
	}
}

void _SCROLL_(void) {
	uint8_t scrbuf[4000];
	memset((void*)&scrbuf, 0, 4000);
	memcpy((void*)&scrbuf, (void*)0xB8000, 4000);
	memset((void*)0xB8000, 0, 4000);
	uint32_t sbl = (uint32_t)((void*)&scrbuf); 
	memcpy((void*)0xB8000, (void*)(sbl + 160), 3840);
}

void cls(void) {
	vx = 0; vy = 0; memset((void*)0xB8000, 0, 4000);
}

void putc(char ch, uint8_t cl) {
	
	// Warning: Using a goto in C is highly discouraged.
	
	if (is_special(ch)) {
		goto process_special;
	} else {
		goto process_normal;
	}
	process_special:
		if (ch == '\n') {
			vx = 0;
			++vy;
			int _testvy_ = (vy + 1);
			if (_testvy_ == 25) {
				_SCROLL_();
			}
			return;
		} else if (ch == '\t') {
			for (size_t j = 0; j < 80; j += 4) {
				if (vx < j) {
					vx = j; return;
				}
			}				
		} else {
			return;
		}
		return;
	process_normal:;
		const size_t INDX = vy * 80 + vx;
		vptr[INDX] = (ch | (cl << 8));
		if (++vx == 80) {
			vx = 0;
			if (++vy == 25) {
				_SCROLL_();
			}
		}
		return;
}

void puts(const char* s, uint8_t c) {
	size_t sz = 0;
	while(s[sz])
		sz++;
	for (size_t tring = 0; tring < sz; tring++) {
		putc(s[tring], c);
	}
}
