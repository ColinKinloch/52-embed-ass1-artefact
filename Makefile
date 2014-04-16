PROJ = ass1-52
CC = sdcc
DEVICE = 12f675
COPIMISE = 
CFLAGS = $(C_OPIMISE) --use-non-free -mpic14 -p$(DEVICE)
LDFLAGS = 
BUILDDIR = build
SRCDIR = src

SRC := $(shell find ./$(SRCDIR) -name '*.c' )

FLASHER = usb_pickit
SIM = gpsim

.PHONY: clean

all: $(PROJ).hex
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

clean: $(BUILDDIR)
	rm -r $(BUILDDIR)