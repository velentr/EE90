CC	?=	gcc
SAMPLES =	256
CFLAGS	=	-O2 -c -Wall -Wstrict-prototypes -pedantic -DSAMPLE_SIZE=$(SAMPLES)
LDFLAGS =	-O2
OBJECTS	=	data.o fft.o roots.o

all: ee90-dogbowl

ee90-dogbowl: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o ee90-dogbowl

test-fft: $(OBJECTS) test-fft.o
	$(CC) $(OBJECTS) test-fft.o $(LDFLAGS) -o test-fft

data.o: data.c data.h
	$(CC) $(CFLAGS) data.c

fft.o: fft.c fft.h data.h
	$(CC) $(CFLAGS) fft.c

roots.c: genroots.py
	python2 genroots.py $(SAMPLES) > roots.c

roots.o: roots.c data.h
	$(CC) $(CFLAGS) roots.c

test-fft.o: test-fft.c data.h fft.h
	$(CC) $(CFLAGS) test-fft.c

clean:
	rm -rf *.o roots.c ee90-dogbowl test-fft

