BINS = abr_est_present abr_est_present_tail_call abr_vers_tab tri_nain tri_nain_opt
BINS += tri_nain_superopt comparer_nains

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
CFLAGS += -O3

abr_est_present: abr_est_present.o fct_abr_est_present.o

abr_est_present_tail_call: abr_est_present_tail_call.o fct_abr_est_present_tail_call.o

abr_vers_tab: abr_vers_tab.o fct_abr_vers_tab.o

tri_nain: tri_nain.o fct_tri_nain.o

tri_nain_opt: tri_nain_opt.o fct_tri_nain_opt.o

tri_nain_superopt: tri_nain_superopt.o fct_tri_nain_superopt.o

comparer_nains: comparer_nains.o fct_tri_nain.o fct_tri_nain_opt.o fct_tri_nain_superopt.o
