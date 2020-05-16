#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <random>

class Matrix{
public:
    Matrix( int col, int lin,bool random);

    void genRandom();

    void imprimeMatrix();

    double geraNumRandom(std::mt19937& gen,std::uniform_real_distribution<double>& dis);

    Matrix* transposta();

    void setValue(double val,unsigned short lin,unsigned short col);
    double getValue(unsigned short lin,unsigned short col);

    unsigned short getCol(){return this->col;}
    unsigned short getLin(){return this->lin;}

private:
    unsigned short col, lin;
    std::vector<std::vector<double>> matrix;
};

#endif