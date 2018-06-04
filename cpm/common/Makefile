# définition de quelques variables
TARGET  := out
CC      := sdcc
AS	:= sdasz80
LFLAGS  := -Wl-u
MFLAGS  := -mz80 --code-loc 0x0200 --data-loc 0 --vc

SRCS=${wildcard *.c}
ASMS=${wildcard *.s}
RELS=${ASMS:.s=.rel} ${SRCS:.c=.rel}

all: ${TARGET}.txt

%.rel:%.s
	@echo " [AS] $<"
	@$(AS) -plosgffw $@ $<

%.rel:%.c
	@echo " [CC] $<"
	@$(CC) $(MFLAGS) $(LFLAGS) -o $@ -c $<

${TARGET}.ihx: ${RELS}
	@echo " [LD] $@"
	@$(CC) $(MFLAGS) $(LFLAGS) -o $@ --no-std-crt0 ${RELS}

${TARGET}.bin: ${TARGET}.ihx
	@echo " [BIN] $<"
	@objcopy -I ihex --output-target=binary $< $@

${TARGET}.com: ${TARGET}.bin
	@echo " [COM] $<"
	@cp $< $@


${TARGET}.txt: ${TARGET}.com
	@echo " [TXT] $<"
	@./filepack.py $< > $@


clean:
	@echo " [RM] $@"
	@rm -f *.cdb *.rel *.hex *.ihx *.lst *.map *.o *.rst \
	*.sym *.lnk *.lib *.bin *.mem *.lk *.noi *.asm *.txt *.com

print-%:
	@echo "$* = ${$*}"

