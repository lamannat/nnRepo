CC := g++
CFLAGS := -Wall -g -c -std=c++11

all: tp1

main.o: main.cpp imagen.h cmdline.h vector.h modulo_funcion_compleja.h
	$(CC) $(CFLAGS) main.cpp

imagen.o: imagen.cpp imagen.h
	$(CC) $(CFLAGS) imagen.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CC) $(CFLAGS) cmdline.cpp

modulo_funcion_compleja.o: modulo_funcion_compleja.h modulo_funcion_compleja.cpp
	$(CC) $(CFLAGS) modulo_funcion_compleja.cpp

tp1: main.o imagen.o cmdline.o modulo_funcion_compleja.o
	$(CC) $^ -o tp1

clean:
	rm *.o
