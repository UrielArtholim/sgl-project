# Makefile Práctica 0
# Copyright 2017
# Alejandro Muñoz Del Álamo


CXX = clang++
CPPFLAGS = -DP0 -I../Tests-auto -I.
CXXFLAGS = -std= C++14 -Wall -pedantic -g

# Indica los directorios donde debe buscar ficheros
VPATH =../Tests-auto:.
#Warning all
#pedantic: Sigue estandar estrictamente

all: test-P0-consola test-P0-auto

test-P0-consola: test-P0-consola.o fecha.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-P0-auto: test-auto.o test-caso0-fecha-auto.o test-caso0-cadena-auto.o fecha.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) $^

test-P0-consola.o: fecha.hpp cadena.hpp

test-auto.o: test-auto.hpp fecha.hpp cadena.hpp fct.h

test-caso0-fecha-auto.o test-caso0-cadena-auto.o: test-auto.hpp 

fecha.o: fecha.hpp

cadena.o: cadena.hpp

clean:
	rm -f fecha.o cadena.o test-auto.o test-P0-consola test-P0-auto test-P0-*.0 *~

# touch fichero modifica la fecha de modificación del fichero

# Opcion para cambiar compilador desde terminal:
# make CXX = g++
# para varias opciones usar ""
# make CXXFLAGS = "-std=c++11 -O"

#make -n test
# Muestra lo que haría sin realizar su ejecución

# Para ejecutar programas
# ./test-P0-consola

# make test-consola: test-P0-consola
#	./test-P0-consola 
# Tambien se puede usar ./$<
