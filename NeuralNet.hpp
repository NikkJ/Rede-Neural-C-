#ifndef _NEURALNET_HPP_
#define _NEURALNET_HPP_

#include <iostream>
#include <vector>

#include "Matrix.hpp"
#include "Layer.hpp"


class NeuralNet{
public:
    NeuralNet(std::vector<unsigned int> topologia,double valorEsperado, unsigned int epocas, std::vector<std::vector<double>> entradas);

    void setEntradas(std::vector<std::vector<double>> entradas,int i);

    void imprimeNet();

    void treinar();
    double valorNeuronio(Matrix* valores,Matrix* pesos,int tam,int idNeuron);

    Matrix* atualizaPesos(Matrix* pesos, double erro, Matrix* valores);

    double preditar(std::vector<double> nums);
private:
    int tamTopo;
    double valorEsperado;
    unsigned int epocas;
    std::vector<unsigned int> topologia;
    std::vector<Layer*> camadas;
    std::vector<Matrix*> pesos;
    std::vector<std::vector<double>> entradas;
};

#endif