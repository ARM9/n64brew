include ../base.mk

target	:= $(shell basename $(CURDIR))
build	:= build
sources	:= . ../lib
incdirs	:= $(build) . ../include $(libn64) $(libn64)/include
includes:= $(foreach dir,$(incdirs),-I$(dir))

arch	:= -march=vr4300
asflags	:= -g $(arch) $(includes)
cflags	:= -g -Wall -Wextra -Wpadded -pedantic -O2 -mabi=o64 -mlong32 -fno-builtin -nostdinc -mgpopt -G8 -mno-extern-sdata -pipe $(arch) $(includes)
cxxflags:= $(cflags) -std=c++14 -fno-rtti -fno-exceptions
cflags	+= -std=c99
ldflags	:= -g -L$(libn64) -Wl,-Map=$(target).map -nostdlib -T$(libn64)/rom.ld 

libs	:= -ln64

Sfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.S)))
cfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.c)))
cxxfiles:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.cpp)))

ofiles	:= $(cfiles:%.c=$(build)/%.o) $(cxxfiles:%.cpp=$(build)/%.o) $(Sfiles:%.S=$(build)/%.o)
depfiles:= $(ofiles:.o=.d)

VPATH	:= $(foreach dir,$(sources),$(CURDIR)/$(dir))

.PHONY: all clean debug release run

all: release

debug: asflags	+= -DDEBUG
debug: cflags	+= -DDEBUG
debug: ldflags	+= 
debug: $(target).z64

release: asflags	+=
release: cflags		+= -flto -ffat-lto-objects 
release: ldflags	+= -flto -ffat-lto-objects 
release: $(target).z64

$(target).z64: $(target).elf

$(target).elf: libn64 $(build) $(ofiles)

$(build):
	@mkdir -p $@

clean:
	rm -rf $(build) $(target).elf $(target).z64 $(target).map

run:
	$(cen64) $(CURDIR)/$(target).z64

-include $(depfiles)

