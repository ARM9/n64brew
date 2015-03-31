PATH	:= $(PATH):$(DEVKITMIPS)/bin
LIBN64	:= $(DEVKITMIPS)/n64tool/libn64
EMUDIR	:= $(DEVKITPRO)/emulators

AS		= mips64-elf-as
AR		= mips64-elf-gcc-ar
CC		= mips64-elf-gcc
LD		= mips64-elf-ld
OBJCOPY	= mips64-elf-objcopy
OBJDUMP	= mips64-elf-objdump
CHECKSUM	= checksum
cen64	:= $(EMUDIR)/n64/cen64/cen64 $(EMUDIR)/n64/cen64/pifrom.bin
mess		:=	cd $(EMUDIR)/mess && ./mess64 n64 -w -cart

LIBS	= -ln64

ASFLAGS	= -march=vr4300 -Iinclude -I$(LIBN64)/include
CFLAGS	= -Wall -Wextra -pedantic -O2 -std=c99 -fno-builtin -nostdinc -mgpopt -G8 -mno-extern-sdata -march=vr4300 -pipe -flto -ffat-lto-objects -Iinclude -I$(LIBN64)/include -fcall-saved-t2 -fcall-saved-t3 -fcall-saved-t4 -fcall-saved-t5 -fcall-saved-t6 -fcall-saved-t7 -fcall-saved-t8 -fcall-saved-t9

LDFLAGS	= -L$(LIBN64) $(LIBS)

TARGET	= $(shell basename $(CURDIR))

CFILES	:= $(wildcard src/*.c)
SFILES	:= $(wildcard src/*.S)

OFILES	:= $(CFILES:.c=.o) $(SFILES:.S=.o)

DEPFILES	= $(OFILES:.o=.d)

#
# Primary targets.
#
all: $(TARGET).z64

$(TARGET).z64: $(TARGET).elf
	@echo "Building: $@"
	$(OBJCOPY) -O binary $< $@
	$(CHECKSUM) $(LIBN64)/header.bin $@

$(TARGET).elf: $(OFILES)
	@echo "Linking: $@"
	$(CC) -Wl,-Map=$(TARGET).map -nostdlib -T$(LIBN64)/rom.ld -o $@ $(OFILES) $(LDFLAGS)

%.o: %.c
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

%.o: %.S
	@echo "Assembling: $<"
	@$(AS) $(ASFLAGS) $< -o $@

.PHONY: libn64
libn64:
	@$(MAKE) -sC $(LIBN64)

.PHONY: clean debug run
clean:
	@echo "Cleaning..."
	@rm -rf $(OFILES) $(DEPFILES) $(TARGET).map $(TARGET).elf $(TARGET).z64

debug: all
	$(mess) $(CURDIR)/$(TARGET).z64 -d

run: all
	$(cen64) $(CURDIR)/$(TARGET).z64

run2: all
	$(mess) $(CURDIR)/$(TARGET).z64

#-include $(DEPFILES)

