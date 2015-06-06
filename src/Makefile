#CC	    =	gcc
CC	    =	avr-gcc
SAMPLES     =	256
LOG2SAMPLES =	8
#CFLAGS	    =	-O2 -c -Wall -Wstrict-prototypes -DSAMPLE_SIZE=$(SAMPLES) \
		-DLOG2_SAMPLE_SIZE=$(LOG2SAMPLES)
CFLAGS	    =	-O2 -c -Wall -Wstrict-prototypes -DSAMPLE_SIZE=$(SAMPLES) \
		-DLOG2_SAMPLE_SIZE=$(LOG2SAMPLES) -mmcu=avr6
#LDFLAGS     =	-O2
LDFLAGS     =	-O2 -mmcu=avr6
OBJECTS	    =	data.o fft.o proximity.o roots.o

all: ee90-dogbowl

ee90-dogbowl: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o ee90-dogbowl

test-fft: $(OBJECTS) test-fft.o
	$(CC) $(OBJECTS) test-fft.o $(LDFLAGS) -o test-fft

data.o: data.c data.h
	$(CC) $(CFLAGS) data.c

fft.o: fft.c fft.h data.h
	$(CC) $(CFLAGS) fft.c

proximity.o: proximity.c proximity.h
	$(CC) $(CFLAGS) proximity.c

roots.c: genroots.py
	python2 genroots.py $(SAMPLES) > roots.c

roots.o: roots.c data.h
	$(CC) $(CFLAGS) roots.c

test-fft.o: test-fft.c data.h fft.h
	$(CC) $(CFLAGS) test-fft.c

clean:
	rm -rf *.o roots.c ee90-dogbowl test-fft

