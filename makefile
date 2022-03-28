program: main.cpp reader.cpp graph.cpp
	g++ -o main main.cpp reader.cpp graph.cpp

run: program
	./main