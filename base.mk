CC		:= mips64-elf-gcc
AS		:= mips64-elf-as
LD		:= mips64-elf-ld
CPP		:= mips64-elf-cpp
OBJCOPY		:= mips64-elf-objcopy
OBJDUMP		:= mips64-elf-objdump
checksum	:= checksum

libn64	:= $(DEVKITMIPS)/n64chain/libn64

emudir	:= $(DEVKITPRO)/emulators
cen64	:= $(emudir)/n64/cen64/cen64 $(emudir)/n64/cen64/pifrom.bin

.DEFAULT_GOAL	:= all

build/%.o : %.S
	$(CC) $(asflags) -MMD -c $< -o $@

build/%.o : %.c
	$(CC) $(cflags) -MMD -c $< -o $@

%.z64 : %.elf
	$(OBJCOPY) -O binary $< $@
	$(checksum) $(libn64)/header.bin $@

%.elf:
	$(CC) $(ldflags) -o $@ $(ofiles) $(libs)

.PHONY: libn64
libn64:
	@$(MAKE) -sC $(libn64)

