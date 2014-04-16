PROJ = ass1-52
CC = sdcc
DEVICE = 12f675
COPIMISE = --stack-size 8 --peep-return --opt-code-size
CFLAGS = $(COPIMISE) --use-non-free -mpic14 -p$(DEVICE)
LDFLAGS = 
BUILDDIR = build
SRCDIR = src

SRC := $(shell find ./$(SRCDIR) -name '*.c' )

FLASHER = usb_pickit
SIM = gpsim

.PHONY: clean

all: $(PROJ).hex | clear
%.hex: $(BUILDDIR)/%.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $^ -o $@

$(BUILDDIR):
	mkdir -p $@

$(PROJ).hex: $(addprefix $(BUILDDIR)/,$(notdir $(SRC:.c=.o)))

install:
	$(FLASHER) -p=$(PROJ).hex

sim:
	$(SIM) -p p$(DEVICE) $(PROJ).hex

clear: $(BUILDDIR)
	rm -r $(BUILDDIR) ass1-52.lst ass1-52.cod

clean: $(BUILDDIR)
	rm -r $(BUILDDIR) ass1-52.*