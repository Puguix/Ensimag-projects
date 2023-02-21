BINS = taille_chaine inverse_chaine tri_min inverse_liste decoupe_liste palin
BINS += struct double_rect

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

inverse_liste: inverse_liste.o fct_inverse_liste.o

decoupe_liste: decoupe_liste.o fct_decoupe_liste.o

palin: palin.o fct_palin.o

taille_chaine: taille_chaine.o fct_taille_chaine.o

inverse_chaine: inverse_chaine.o fct_inverse_chaine.o

struct: struct.o fct_struct.o

double_rect: double_rect.o fct_double_rect.o

tri_min: tri_min.o fct_tri_min.o
