CC	    =	avr-gcc
SAMPLES     =	64
LOG2SAMPLES =	6
CFLAGS	    =	-O2 -c -Wall -Wstrict-prototypes -DSAMPLE_SIZE=$(SAMPLES) \
		-DLOG2_SAMPLE_SIZE=$(LOG2SAMPLES) -D__AVR_ATmega2560__ \
		-mmcu=avr6
LDFLAGS     =	-O2 -mmcu=avr6 -lm
OBJECTS	    =	adc.o data.o fft.o key.o mainloop.o proximity.o pwm.o roots.o

all: ee90-dogbowl

ee90-dogbowl: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o ee90-dogbowl

test-fft: $(OBJECTS) test-fft.o
	$(CC) $(OBJECTS) test-fft.o $(LDFLAGS) -o test-fft

adc.o: adc.c adc.h data.h
	$(CC) $(CFLAGS) adc.c

data.o: data.c data.h
	$(CC) $(CFLAGS) data.c

fft.o: fft.c fft.h data.h
	$(CC) $(CFLAGS) fft.c

key.o: key.c data.h
	$(CC) $(CFLAGS) key.c

mainloop.o: mainloop.c adc.h data.h fft.h proximity.h pwm.h
	$(CC) $(CFLAGS) mainloop.c

proximity.o: proximity.c proximity.h
	$(CC) $(CFLAGS) proximity.c

pwm.o: pwm.c pwm.h
	$(CC) $(CFLAGS) pwm.c

roots.c: genroots.py
	python2 genroots.py $(SAMPLES) > roots.c

roots.o: roots.c data.h
	$(CC) $(CFLAGS) roots.c

test-fft.o: test-fft.c data.h fft.h
	$(CC) $(CFLAGS) test-fft.c

clean:
	rm -rf *.o roots.c ee90-dogbowl test-fft

