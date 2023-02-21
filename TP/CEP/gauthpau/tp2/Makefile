BINS = age hello affine fact fact_papl val_binaire
BINS += pgcd mult fibo
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

fact: ASFLAGS += -march=rv32im
fact: fact.o fct_fact.o

fact_papl: ASFLAGS += -march=rv32im
fact_papl: fact_papl.o fct_fact_papl.o

age: age.o fct_age.o

hello: hello.o fct_hello.o

affine: affine.o fct_affine.o fct_mult.o

fibo: fibo.o fct_fibo.o

val_binaire: val_binaire.o fct_val_binaire.o

mult: mult.o fct_mult.o
