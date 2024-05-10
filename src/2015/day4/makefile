all: main_p1 main_p2

main_p1: main_p1.cpp
	g++ -g main_p1.cpp -o main_p1 -lssl -lcrypto

main_p2: main_p2.cpp
	g++ -g main_p2.cpp -o main_p2 -lssl -lcrypto

run: all
	./main_p1 input.txt
	./main_p2 input.txt
