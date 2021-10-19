echo "[@] Create directories to build"
mkdir -p build/kernel/io
mkdir -p build/drivers/keyboard
mkdir -p build/drivers/vga
mkdir bin
echo "[*] Directories created successfully"

echo "[@] Build a bootloader"
#assemble boot.s file
as --32 boot.s -o ./build/boot.o
echo "[*] build successfully"

echo "[@] Building the project"
#compile files
gcc -m32 -c ./kernel/kernel.c -o ./build/kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra
gcc -m32 -c ./kernel/utils.c -o ./build/kernel/utils.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra
gcc -m32 -c ./kernel/io/io.c -o ./build/kernel/io/io.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra
gcc -m32 -c ./drivers/keyboard/keyboard.c -o ./build/drivers/keyboard/keyboard.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra
gcc -m32 -c ./drivers/vga/console.c -o ./build/drivers/vga/console.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

echo "[*] build successfully"

echo "[@] linking files"
#linking files
ld -m elf_i386 -T linker.ld ./build/boot.o \
        ./build/kernel.o \
        ./build/kernel/utils.o \
        ./build/kernel/io/io.o \
        ./build/drivers/keyboard/keyboard.o \
        ./build/drivers/vga/console.o \
        -o ./bin/Minix.bin -nostdlib

echo "[*] Link successfully"

#check bin file is x86 multiboot file or not
grub-file --is-x86-multiboot ./bin/Minix.bin

echo "[@] building the iso file"
#building the iso file
mkdir -p iso/boot/grub
mkdir -p iso/build

cp ./bin/Minix.bin iso/boot/Minix.bin
cp grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o iso/build/Minix.iso iso
