cppshell: main.o
	g++ main.o -o ./../bin/errno_print

main.o: ./../src/main.cpp
	g++ -c ./../src/main.cpp -o main.o

clean:
	rm -rf *.o ./../bin/errno_print
