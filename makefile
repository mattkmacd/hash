plagiarismCatcher: main.o
	g++ -o plagiarismCatcher main.o

main.o: main.cpp
	g++ -c main.cpp
