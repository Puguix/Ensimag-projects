BINS = it timer
BINS += it_incr_decr timer_raz timer_raz_btn0 timer_papl
TMPOBJS = crt.o cep_excp.o


RVDIR ?= /matieres/3MMCEP/riscv
AS = $(RVDIR)/bin/riscv32-unknown-elf-gcc
ASFLAGS = -g -c
CC = $(AS)
CFLAGS = -nostdinc -Wall -Wextra -g -std=c99 -mabi=ilp32 -mcmodel=medany -ffunction-sections -fdata-sections -g
CFLAGS += -I$(RVDIR)/include
LD = $(AS)
LDFLAGS = -L$(RVDIR)/lib -L$(RVDIR)/lib/cep_riscv_no_it
LDFLAGS += -T cep.ld -nostartfiles -nostdlib -static -Wl,--nmagic -Wl,--gc-sections

.PHONY: all
all: $(BINS)


%.o: %.S
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.stxetd: fct_%.s
	fonction=$$(basename $@ .stxetd);awk -f test/syntaxe_etd.awk -v fonction=$$fonction $< > $@;cat $@

STXETDOUTS = $(foreach f, $(BINS),  $(addsuffix .stxetd, $f))
SORTIES = $(foreach f, $(BINS), $(addsuffix .sortie, $f))
OBJS = $(foreach f, $(BINS), $(addsuffix .o, $f)) \
	$(foreach f, $(BINS), $(addprefix fct_, $(addsuffix .o, $f)))

.PHONY: clean
clean:
	$(RM) $(BINS) $(OBJS) $(TMPOBJS) $(STXETDOUTS) $(SORTIES)
ASFLAGS += -x assembler-with-cpp


crt.o : crt.s cep_platform.h

it.o : cep_platform.h crt.o

fct_it.o : cep_platform.h
it: it.o fct_it.o

fct_it_incr_decr.o : cep_platform.h crt.o
it_incr_decr: it_incr_decr.o fct_it_incr_decr.o

fct_timer.o : cep_platform.h
timer: timer.o fct_timer.o cep_excp.o

fct_timer_raz.o : cep_platform.h
timer_raz: timer_raz.o fct_timer_raz.o cep_excp.o

fct_timer_raz_btn0.o : cep_platform.h
timer_raz_btn0: timer_raz_btn0.o fct_timer_raz_btn0.o cep_excp.o

fct_timer_papl.o : cep_platform.h
timer_papl: timer_papl.o fct_timer_papl.o cep_excp.o
