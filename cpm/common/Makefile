# définition de quelques variables
TARGET  := prem
CC      := sdcc
AS	:= sdasz80
LFLAGS  := -Wl-u
MFLAGS  := -mz80 --code-loc 0x0100 --data-loc 0x7000 --vc --verbose


# Tout construire c'est construire prem.bin et prem_padded.bin
all: ${TARGET}.txt

# Assemblage du crt0
crt0.rel: crt0.s
	$(AS) -plosgffw crt0.rel crt0.s

main.rel: main.c
	$(CC) $(MFLAGS) $(LFLAGS) -o main.rel -c main.c

# Compilation de prem.c et édition de liens
${TARGET}.ihx: main.rel crt0.rel
	$(CC) $(MFLAGS) $(LFLAGS) -o ${TARGET}.ihx --no-std-crt0 crt0.rel main.rel

# Conversion de l'Intel Hex en binaire
${TARGET}.bin: ${TARGET}.ihx
	makebin -p < ${TARGET}.ihx > ${TARGET}.bin
	objcopy -I ihex --output-target=binary ${TARGET}.ihx ${TARGET}.com

${TARGET}.txt: ${TARGET}.bin
	./filepack.py ${TARGET}.bin > ${TARGET}.txt


# Désassemblage à l'écran
disasm: ${TARGET}.bin
	z80dasm -a -t -g 0x0 -l ${TARGET}.bin

# Affichage du code machine
dump: ${TARGET}.bin
	/bin/echo -ne "const PROGMEM " > Z80ctl_memRAM/mem.h
	xxd -c 16 -i ${TARGET}.bin >> Z80ctl_memRAM/mem.h

# Affacement des fichiers, nettoyage
clean:
	rm -f *.cdb *.rel *.hex *.ihx *.lst *.map *.o *.rst \
	*.sym *.lnk *.lib *.bin *.mem *.lk *.noi *.asm *.txt *.com
