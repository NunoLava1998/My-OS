#include "main.h"

void memset(void* s, uint8_t c, size_t n) {
	char* l = s;
	while (n > 0) {
		*l = c; l++;
		n--;
	}
}

void memcpy(void* s1, void* s2, size_t n) {
	char* cs1 = (char*)s1;
	char* cs2 = (char*)s2;
	for (size_t i = 0; i < n; i++) {
		cs1[i] = cs2[i];
	}
}