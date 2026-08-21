NAME      = kernel.bin
ISO       = kernel.iso

CC        = i686-elf-gcc
ASM       = nasm
CFLAGS    = -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs -I include

C_SRCS    =	drivers/vga.c \
			kernel/kmain.c \
			lib/lib.c \

ASM_SRCS  = boot/boot.asm

ASM_OBJ   =	$(addprefix obj/, $(notdir $(ASM_SRCS:.asm=.o)))

C_OBJ     =	$(addprefix obj/, $(notdir $(C_SRCS:.c=.o)))

OBJ       = $(ASM_OBJ) $(C_OBJ)

vpath %.asm boot
vpath %.c drivers kernel lib

all: $(ISO)

$(ISO): $(NAME)
	cp $(NAME) iso/boot/
	grub-mkrescue -o $(ISO) iso/

$(NAME): $(OBJ)
	$(CC) -T linker.ld -o $(NAME) -ffreestanding -nostdlib $(OBJ)

obj/%.o: %.asm | obj
	$(ASM) -f elf32 $< -o $@

obj/%.o: %.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -f $(OBJ)
	rm -rf obj/

fclean: clean
	rm -f $(NAME) $(ISO) iso/boot/kernel.bin

re: fclean all

.PHONY: all run clean fclean re obj