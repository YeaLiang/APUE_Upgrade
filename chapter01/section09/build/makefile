cppshell_withsignal: main.o
	g++ main.o -o ./../bin/cppshell_withsignal

main.o: ./../src/main.cpp
	g++ -c ./../src/main.cpp -o main.o

clean:
	rm -rf *.o ./../bin/cppshell_withsignal
