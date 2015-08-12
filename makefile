PATH	:= $(PATH):$(DEVKITMIPS)/bin
LIBN64	:= $(DEVKITMIPS)/n64tool/libn64
EMUDIR	:= $(DEVKITPRO)/emulators

AS		:= mips64-elf-as
AR		:= mips64-elf-gcc-ar
CC		:= mips64-elf-gcc
OBJCOPY		:= mips64-elf-objcopy
OBJDUMP		:= mips64-elf-objdump
CHECKSUM	:= checksum
CEN64		:= $(EMUDIR)/n64/cen64/cen64 $(EMUDIR)/n64/cen64/pifrom.bin

TARGET	:= $(shell basename $(CURDIR))
BUILD	:= build
SOURCES	:= src

LIBS	:= -ln64

ASFLAGS	:= -march=vr4300 -Iinclude -I$(LIBN64)/include
CFLAGS	:= -Wall -Wextra -pedantic -O2 -std=c99 -fno-builtin -nostdinc -mgpopt -G8 -mno-extern-sdata -march=vr4300 -pipe -flto -ffat-lto-objects -Iinclude -I$(LIBN64)/include

LDFLAGS	:= -L$(LIBN64) -Wl,-Map=$(TARGET).map -nostdlib -T$(LIBN64)/rom.ld 

CFILES	:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES	:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))

OFILES		:= $(CFILES:%.c=build/%.o) $(SFILES:%.S=build/%.o)
DEPFILES	:= $(OFILES:.o=.d)

export VPATH	:= $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

.PHONY: all clean debug release run

all: release

debug: CFLAGS	+= -g -DDEBUG
debug: ASFLAGS	+= -g --defsym DEBUG=1
debug: LDFLAGS	+= -g
debug: $(TARGET).z64

release: CFLAGS		+= 
release: ASFLAGS	+= 
release: LDFLAGS	+= 
release: $(TARGET).z64

$(BUILD):
	@mkdir -p $@

$(TARGET).z64: $(TARGET).elf
	@echo "Building: $@"
	$(OBJCOPY) -O binary $< $@
	$(CHECKSUM) $(LIBN64)/header.bin $@

$(TARGET).elf: $(BUILD) $(OFILES)
	@echo "Linking: $@"
	$(CC) $(LDFLAGS) -o $@ $(OFILES) $(LIBS) 

build/%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

build/%.o: %.S
	$(CC) $(ASFLAGS) -MMD -c $< -o $@

clean:
	rm -rf $(BUILD) $(TARGET).map $(TARGET).elf $(TARGET).z64

run: all
	$(CEN64) $(CURDIR)/$(TARGET).z64

.PHONY: libn64
libn64:
	@$(MAKE) -sC $(LIBN64)

-include $(DEPFILES)

