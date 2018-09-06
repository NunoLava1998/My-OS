.extern gdtp
.global gdtldr

gdtldr:
	lgdt gdtp
	ljmp $0x08, $rr
rr:
	mov $0x10, %eax
	mov %eax, %ds
	mov %eax, %es
	mov %eax, %fs 
	mov %eax, %gs
	mov %eax, %ss
	ret
