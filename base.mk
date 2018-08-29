CC		:= mips64-elf-gcc
CXX		:= mips64-elf-g++
AS		:= mips64-elf-as
LD		:= mips64-elf-ld
CPP		:= mips64-elf-cpp
OBJCOPY		:= mips64-elf-objcopy
OBJDUMP		:= mips64-elf-objdump
checksum	:= checksum

libn64	:= $(DEVKITMIPS)/n64chain/libn64

cen64	:= ~/src/cen64/build/cen64 ~/src/cen64/pifrom.bin

.DEFAULT_GOAL	:= all

build := build

$(build):
	@mkdir -p $@

build/%.o : %.c
	$(CC) $(cflags) -MMD -c $< -o $@

build/%.o : %.cpp
	$(CXX) $(cxxflags) -MMD -c $< -o $@

build/%.o : %.cxx
	$(CXX) $(cxxflags) -MMD -c $< -o $@

build/%.o : %.cc
	$(CXX) $(cxxflags) -MMD -c $< -o $@

build/%.o : %.S
	$(CC) $(asflags) -MMD -c $< -o $@

%.z64 : %.elf
	$(OBJCOPY) -O binary $< $@
	$(checksum) $(libn64)/header.bin $@

# TODO linking c++ projects with gcc should be fine
%.elf:
	$(CC) $(ldflags) -o $@ $(ofiles) $(libs)

.PHONY: libn64
libn64:
	@$(MAKE) -sC $(libn64)

.PHONY: debug dis
debug:
	mess n64 -cart $(target).z64 -d

dis:
	$(OBJDUMP) -b binary -mmips:4300 -EB -D $(target).z64 > _dis.asm

