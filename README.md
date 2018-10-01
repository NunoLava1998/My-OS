# Ringfire OS
My operating system.

There is already a .bin file out in the releases section of this. To build it yourself, you will need the following:
A Linux distro;
A 32bit ELF compiler for x86;

To run it, you either need:
A compiler that can boot ELF .bin files, or GRUB (grub-mkrescue requires xorriso). You can theoretically use any multiboot-compliant bootloader, but this is untested.

To compile it:
Compile each .c file and .s file;
Link it with linker.ld;
Run it.

To run it, it should be dependent on the compiler or bootloader on how to make it.

**Downloads for BIN files are available on the "Releases" section of this project.**

![Ringfire logo](https://i.imgur.com/Z13kQy8.png)
