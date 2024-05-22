OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o Rio.o Ciudad.o Barco.o Producto.o
	g++ -o program.exe program.o Rio.o Ciudad.o Barco.o Producto.o

Rio.o: Rio.cc
	g++ -c Rio.cc $(OPCIONS)

Ciudad.o: Ciudad.cc
	g++ -c Ciudad.cc $(OPCIONS)

Barco.o: Barco.cc
	g++ -c Barco.cc $(OPCIONS)

Producto.o: Producto.cc
	g++ -c Producto.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.tar
	
tar: Rio.hh Rio.cc Ciudad.hh Ciudad.cc Barco.hh Barco.cc Producto.hh Producto.cc program.cc Makefile
	tar -cvf practica.tar Rio.cc Rio.hh Ciudad.cc Ciudad.hh Barco.cc Barco.hh Producto.cc Producto.hh program.cc Makefile