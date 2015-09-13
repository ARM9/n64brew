include ../base.mk

target	:= $(shell basename $(CURDIR))
build	:= build
sources	:= src ../lib
incdirs	:= $(build) include ../include $(libn64) $(libn64)/include
includes:= $(foreach dir,$(incdirs),-I$(dir))

arch	:= -march=vr4300
asflags	:= -g $(arch) $(includes)
cflags	:= -g -Wall -Wextra -pedantic -O2 -std=c99 -fno-builtin -nostdinc -mgpopt -G8 -mno-extern-sdata -pipe -flto -ffat-lto-objects $(arch) $(includes)
ldflags	:= -g -L$(libn64) -Wl,-Map=$(target).map -nostdlib -T$(libn64)/rom.ld 

libs	:= -ln64

sfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.S)))
cfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.c)))

ofiles	:= $(cfiles:%.c=$(build)/%.o) $(sfiles:%.S=$(build)/%.o)
depfiles:= $(ofiles:.o=.d)

VPATH	:= $(foreach dir,$(sources),$(CURDIR)/$(dir))

.PHONY: all clean debug release run

all: release

debug: asflags	+= -DDEBUG
debug: cflags	+= -DDEBUG
debug: ldflags	+= 
debug: $(target).z64

release: asflags	+=
release: cflags		+=
release: ldflags	+=
release: $(target).z64

$(target).z64: $(target).elf

$(target).elf: $(build) $(ofiles)

$(build):
	@mkdir -p $@

clean:
	rm -rf $(build) $(target).elf $(target).z64 $(target).map

run:
	$(cen64) $(CURDIR)/$(target).z64

-include $(depfiles)

