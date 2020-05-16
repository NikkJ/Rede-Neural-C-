parametrosCompilacao=-Wall #-Wshadow

all: ann

ann: main.o Layer.o Matrix.o Neuron.o NeuralNet.o
	g++ -o ann main.o Layer.o Matrix.o Neuron.o NeuralNet.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Matrix.o: Layer.hpp Matrix.cpp Neuron.hpp NeuralNet.hpp
	g++ -c Matrix.cpp $(parametrosCompilacao)

Layer.o: Matrix.hpp Layer.cpp Neuron.hpp NeuralNet.hpp
	g++ -c Layer.cpp $(parametrosCompilacao)

Neuron.o: Matrix.hpp Layer.hpp Neuron.cpp NeuralNet.hpp
	g++ -c Neuron.cpp $(parametrosCompilacao)

NeuralNet.o: Matrix.hpp Layer.hpp Neuron.hpp NeuralNet.cpp
	g++ -c NeuralNet.cpp $(parametrosCompilacao)

clean:
	rm *.o ann
