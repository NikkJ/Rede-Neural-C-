#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <iostream>

class Neuron {
public:
    Neuron(double val);

    void setVal(double val);
    double getVal();

    void activate();
    double getValActived();

    void derive();
    double getValDeriv();

private:
    double val;
    double valActived;
    double valDerived;
};

#endif