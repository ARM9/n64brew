include ../base.mk

target	:= $(shell basename $(CURDIR))
build	:= build
sources	:= src ../lib
incdirs	:= $(build) include ../include $(libn64)/include
includes:= $(foreach dir,$(incdirs),-I$(dir))

libs	:= -ln64

arch	:= -march=vr4300
ASFLAGS	:= -g $(arch) $(includes)
CFLAGS	:= -g -Wall -Wextra -pedantic -O2 -std=c99 -fno-builtin -nostdinc -mgpopt -G8 -mno-extern-sdata -pipe -flto -ffat-lto-objects $(arch) $(includes)
LDFLAGS	:= -g -L$(libn64) -Wl,-Map=$(target).map -nostdlib -T$(libn64)/rom.ld 

cfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.c)))
sfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.S)))

ofiles		:= $(cfiles:%.c=build/%.o) $(sfiles:%.S=build/%.o)
depfiles	:= $(ofiles:.o=.d)

VPATH	:= $(foreach dir,$(sources),$(CURDIR)/$(dir))

.PHONY: all clean debug release run

all: release

debug: CFLAGS	+= -DDEBUG
debug: ASFLAGS	+= -DDEBUG
debug: LDFLAGS	+= 
debug: $(target).z64

release: CFLAGS		+=
release: ASFLAGS	+=
release: LDFLAGS	+=
release: $(target).z64

$(target).z64: $(target).elf

$(target).elf: $(build) $(ofiles)

$(build):
	@mkdir -p $@

clean:
	rm -rf $(build) $(target).map $(target).elf $(target).z64

run: all
	$(cen64) $(CURDIR)/$(target).z64

-include $(depfiles)

