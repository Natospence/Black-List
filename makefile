all: dep RBFGen IPCheck

IPCheck: IPCheck.c
	gcc -o IPCheck IPCheck.c hashing.o sha256.o

RBFGen: RBFGen.c
	gcc -o RBFGen -g -Wall RBFGen.c hashing.o sha256.o

dep: sha256.c sha256.h hashing.c hashing.h
	gcc -c sha256.c sha256.h
	gcc -c hashing.c hashing.h

clean:
	rm RBFGen IPCheck sha256.o hashing.o output.txt *.gch
