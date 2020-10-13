ls: main.o
	g++ main.o -o ./../bin/ls

main.o: ./../src/main.cpp
	g++ -c ./../src/main.cpp -o main.o

clean:
	rm -rf *.o ./../bin/ls
