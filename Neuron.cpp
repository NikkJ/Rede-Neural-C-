#include <iostream>

#include "Neuron.hpp"

Neuron::Neuron(double val){
        this->val = val;
        //std::cout<<"constr: "<<val<<std::endl;
        activate();
        derive();
    }

void Neuron::activate(){
    //std::cout<<"ativando: "<<this->val<<std::endl;
    this->valActived = this->val / (1+abs(this->val));
}

void Neuron::derive(){
    this->valDerived = this->valActived * (1- this->valActived);
}

void Neuron::setVal(double val){
    this->val = val;
}

double Neuron::getVal(){
    return this->val;
}

double Neuron::getValDeriv(){ 
    if(this->valDerived!=0){
        return this->valDerived;
    }else{
        this->derive();
        return this->valDerived;
    }
}
double Neuron::getValActived(){ return this->valActived;}
