#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <iostream>
#include <vector>
#include "Neuron.hpp"
#include "Matrix.hpp"

class Layer{
public:
    Layer(int tam);

    void setValor(int i,double v);
    int numNeurons();
    double getValorNeuronio(int i);

    Matrix* matrizarValores();
    Matrix* matrizarAtivados();
    Matrix* matrizarDerivados();

private:
    unsigned short tam;
    std::vector<Neuron*> neurons;
};

#endif