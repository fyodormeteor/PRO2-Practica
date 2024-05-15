OPCIONS = 

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

BinTree.o: BinTree.hh
	g++ -c BinTree.hh $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
