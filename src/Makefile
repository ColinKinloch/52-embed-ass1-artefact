PROJ = ass1-52
CC = sdcc
DEVICE = 12f675
C_FLAGS = --use-non-free -mpic14 -p$(DEVICE)

SRC := $(shell find . -name '*.c')

FLASHER = usb_pickit
SIM = gpsim

.PHONY: clean

all: $(PROJ).hex
	

$(PROJ).hex: $(SRC:.c=.o)
	$(CC) $(C_FLAGS) $^ -o $@

%.o: %.c
	$(CC) $(C_FLAGS) -c $<

install:
	$(FLASHER) -p=$(PROJ).hex

sim:
	$(SIM) -p p$(DEVICE) $(PROJ).hex

clean:
	-rm *.o *.hex *.asm *.lst *.cod