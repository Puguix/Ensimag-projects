BINS = pgcd somme sommeMem mult_simple mult_egypt mult_native somme8
BINS += put

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

pgcd: pgcd.o fct_pgcd.o

somme: somme.o fct_somme.o

sommeMem: sommeMem.o fct_sommeMem.o

somme8: somme8.o fct_somme8.o

mult_simple: ASFLAGS += -march=rv32im
mult_simple: CFLAGS += -march=rv32im
mult_simple: mult_simple.o fct_mult_simple.o

mult_egypt: ASFLAGS += -march=rv32im
mult_egypt: CFLAGS += -march=rv32im
mult_egypt: mult_egypt.o fct_mult_egypt.o

mult_native: ASFLAGS += -march=rv32im
mult_native: CFLAGS += -march=rv32im
mult_native: mult_native.o fct_mult_native.o

put_error : put.c
	$(CC) -DCODE_FAUX -fsyntax-only $<

