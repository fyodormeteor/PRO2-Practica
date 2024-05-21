OPCIONS = 
#-D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

x: program.o Rio.o Ciudad.o Barco.o Producto.o BinTree.o
	g++ -o x program.o Rio.o Ciudad.o Barco.o Producto.o BinTree.o

Rio.o: Rio.cc
	g++ -c Rio.cc $(OPCIONS)

Ciudad.o: Ciudad.cc
	g++ -c Ciudad.cc $(OPCIONS)

Barco.o: Barco.cc
	g++ -c Barco.cc $(OPCIONS)

Producto.o: Producto.cc
	g++ -c Producto.cc $(OPCIONS)

BinTree.o: BinTree.cc
	g++ -c BinTree.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
	
