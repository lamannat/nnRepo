CC := g++
CFLAGS := -Wall -g -c -std=c++11

all: tp0

main.o: main.cpp imagen.h cmdline.h vector.h
	$(CC) $(CFLAGS) main.cpp

imagen.o: imagen.cpp imagen.h vector.h
	$(CC) $(CFLAGS) imagen.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CC) $(CFLAGS) cmdline.cpp

tp0: main.o imagen.o cmdline.o
	$(CC) $^ -o tp0

clean:
	rm *.o
