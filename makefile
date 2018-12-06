plagiarismCatcher: main.o
	g++ -o plagiarismCatcher main.o

main.o: main.cpp collision.h
	g++ -c main.cpp
