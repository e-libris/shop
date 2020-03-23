#
# makefile for main.cpp, item.cpp, item.h 

# Compiler variables
#CCFLAGS = -ansi -Wall -std=c++0x
#CCFLAGS = -ansi -Wall -std=c++17
CCFLAGS = -ansi -Wall -lstdc++fs -std=c++17

# Rule to link object code files to create executable file
shop: shop.o item.o receipt.o procreceipt.o reports.o
	g++ $(CCFLAGS) -o shop shop.o item.o receipt.o procreceipt.o reports.o

# Rules to compile source code files to object code
shop.o: shop.cpp item.h receipt.h procreceipt.h reports.h
	g++ $(CCFLAGS) -c shop.cpp

receipt.o:	receipt.cpp receipt.h
	g++ $(CCFLAGS) -c receipt.cpp

item.o: item.cpp item.h
	g++ $(CCFLAGS) -c item.cpp

procreceipt.o:	procreceipt.cpp procreceipt.h
	g++ $(CCFLAGS) -c procreceipt.cpp
	
reports.o: reports.cpp reports.h
	g++ $(CCFLAGS) -c reports.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o shop
