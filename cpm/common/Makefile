# définition de quelques variables
TARGET  := out
CC      := sdcc
AS	:= sdasz80
LFLAGS  := -Wl-u
MFLAGS  := -mz80 --code-loc 0x0110 --data-loc 0 --vc

SRCS=${wildcard *.c}
ASMS=${wildcard *.s}
RELS=${ASMS:.s=.rel} ${SRCS:.c=.rel}

all: ${TARGET}.txt

%.rel:%.s
	@echo "AS $@"
	@$(AS) -plosgffw $@ $<

%.rel:%.c
	@echo "CC $@"
	@$(CC) $(MFLAGS) $(LFLAGS) -o $@ -c $<

# Compilation de prem.c et édition de liens
${TARGET}.ihx: ${RELS}
	@echo "LD $@"
	@$(CC) $(MFLAGS) $(LFLAGS) -o ${TARGET}.ihx --no-std-crt0 ${RELS}

# Conversion de l'Intel Hex en binaire
${TARGET}.bin: ${TARGET}.ihx
	@echo "BIN $@"
	@makebin -p < ${TARGET}.ihx > tmp.bin
	@dd if=tmp.bin of=${TARGET}.bin bs=1 skip=256
	@objcopy -I ihex --output-target=binary ${TARGET}.ihx ${TARGET}.com

${TARGET}.txt: ${TARGET}.bin
	@echo "TXT $@"
	@mv ${TARGET}.bin ${TARGET}.com
	@./filepack.py ${TARGET}.com > ${TARGET}.txt

# Désassemblage à l'écran
disasm: ${TARGET}.bin
	z80dasm -a -t -g 0x0 -l ${TARGET}.bin

# Affacement des fichiers, nettoyage
clean:
	@echo "RM $@"
	@rm -f *.cdb *.rel *.hex *.ihx *.lst *.map *.o *.rst \
	*.sym *.lnk *.lib *.bin *.mem *.lk *.noi *.asm *.txt *.com

print-%:
	@echo "$* = ${$*}"

.SUFFIXES: .rel