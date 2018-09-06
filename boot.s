.set ALIGN,		1<<0
.set MEM,		1<<1
.set FLAGS,		ALIGN | MEM
.set MAGIC,		0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot

.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss

.align 16
stack_bottom:
.skip 16384

stack_top:
.section .text
.global _load
.type _load, @function
_load:
	mov $stack_top, %esp
	call kload
	cli
1:	hlt
	jmp 1b
	
.size _load, . - _load
