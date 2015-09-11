include ../base.mk

target	:= $(shell basename $(CURDIR))
build	:= build
sources	:= . ../lib
incdirs	:= $(build) ../include $(libn64) $(libn64)/include
includes:= $(foreach dir,$(incdirs),-I$(dir))

arch	:= -march=vr4300
ASFLAGS	:= -g $(arch) $(includes)
CFLAGS	:= -g -std=c99 -Wall -Wextra -pedantic -O2 -fno-builtin -nostdinc -mgpopt -G8 -mno-extern-sdata -pipe -flto -ffat-lto-objects $(arch) $(includes)
LDFLAGS	:= -g -L$(libn64) -Wl,-Map=$(target).map -nostdlib -T$(libn64)/rom.ld

libs	:= -ln64

sfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.S)))
cfiles	:= $(foreach dir,$(sources),$(notdir $(wildcard $(dir)/*.c)))

ofiles	:= $(cfiles:%.c=$(build)/%.o) $(sfiles:%.S=$(build)/%.o)
depfiles:= $(ofiles:.o=.d)

VPATH	:= $(foreach dir,$(sources),$(CURDIR)/$(dir))

.PHONY: all clean debug release run

all: release

debug: ASFLAGS	+= -DDEBUG
debug: CFLAGS	+= -DDEBUG
debug: LDFLAGS	+=
debug: $(target).z64

release: ASFLAGS	+=
release: CFLAGS		+=
release: LDFLAGS	+=
release: $(target).z64

$(target).z64: $(target).elf

$(target).elf: $(build) $(ofiles)

$(build):
	@mkdir -p $@

clean:
	rm -rf $(target).z64 $(target).elf $(target).map $(build)

run:
	$(cen64) $(target).z64

dump: $(target).elf
	$(OBJDUMP) -d $(target).elf

-include $(depfiles)

