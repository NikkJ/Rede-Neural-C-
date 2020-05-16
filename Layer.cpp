#include "Layer.hpp"

#include <iostream>

Layer::Layer(int tam)
    :tam{(unsigned short)tam}{
    for(unsigned short i =0;i<tam;i++){
        Neuron *n{new Neuron{0.0}};
        this->neurons.push_back(n);
    }
}

void Layer::setValor(int i, double v){
    this->neurons.at(i)->setVal(v);
}

double Layer::getValorNeuronio(int i){
    return this->neurons.at(i)->getVal();
}

int Layer::numNeurons(){
    return this->neurons.size();
}

Matrix* Layer::matrizarValores(){
    Matrix* m{new Matrix{1,(int)this->neurons.size(),false}};
    //std::cout<<"Matrizar: ";
    for(unsigned int i = 0; (size_t)i < this->neurons.size(); ++i){
        m->setValue(this->neurons.at(i)->getVal(),0,i);
        //std::cout<<this->neurons.at(i)->getVal()<< "   ";
    }
    //std::cout<<std::endl;
    return m;
}

Matrix* Layer::matrizarAtivados(){
    Matrix* m{new Matrix{1,(int)this->neurons.size(),false}};
    for( int i = 0;(size_t) i < this->neurons.size(); ++i){
        m->setValue(this->neurons.at(i)->getValActived(),0,i);
    }
    return m;
}

Matrix* Layer::matrizarDerivados(){
    Matrix* m{new Matrix{1,(int)this->neurons.size(),false}};
    for( int i = 0;(size_t) i < this->neurons.size(); ++i){
        m->setValue(this->neurons.at(i)->getValDeriv(),0,i);
    }
    return m;
}