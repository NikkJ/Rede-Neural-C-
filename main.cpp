#include "Layer.hpp"
#include "Neuron.hpp"
#include "Matrix.hpp"
#include "NeuralNet.hpp"

#include <iostream>
#include <vector>

int main(){
    std::vector<unsigned int> topologia;
    topologia.push_back(3);
    topologia.push_back(3);
    topologia.push_back(3);
    topologia.push_back(1);

    std::vector<std::vector<double>> entradas(2);
    entradas.at(0).push_back(2.12341232);
    entradas.at(0).push_back(3.9128);
    entradas.at(0).push_back(4.012);
    entradas.at(1).push_back(10.823910);
    entradas.at(1).push_back(187.128472);
    entradas.at(1).push_back(20.8742);
    
    NeuralNet *n{new NeuralNet{topologia,1,10,entradas}};
    n->treinar();

    std::vector<double> nums;
    nums.push_back(2);
    nums.push_back(5);
    nums.push_back(1);

    std::cout<<n->preditar(nums)<<std::endl;
    //n->imprimeNet();

    return 0;
}