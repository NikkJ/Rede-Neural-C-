#include "Matrix.hpp"
#include <random>
#include <iostream>

Matrix::Matrix( int lin, int col,bool random)
        :col{(unsigned short)col},lin{(unsigned short)lin}{
            if(random){
                this->genRandom();
            }else{ 
                for(unsigned short i=0;i<this->lin;++i){
                    std::vector<double> val;
                    for(unsigned short j=0;j<this->col;++j){
                        val.push_back(0.0);
                    }
                this->matrix.push_back(val);
                }
            }
        }


void Matrix::setValue(double val,unsigned short lin,unsigned short col){
    this->matrix.at(lin).at(col) = val;
}

double Matrix::getValue(unsigned short lin, unsigned short col){
    return this->matrix.at(lin).at(col);
}

void Matrix::imprimeMatrix(){
    for(unsigned short i=0;i<this->lin;++i){
        for(unsigned short j=0;j<this->col;++j){
            std::cout << this->matrix.at(i).at(j)<< "\t";
        }
        std::cout<<std::endl;
    }
}


void Matrix::genRandom(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0,1.0);

    for(unsigned short i=0;i<this->lin;++i){
        std::vector<double> val;
        for(unsigned short j=0;j<this->col;++j){
            double r = this->geraNumRandom(gen,dis);
            val.push_back(r);
        }
        this->matrix.push_back(val);
    }
}

double Matrix::geraNumRandom(std::mt19937& gen,std::uniform_real_distribution<double>& dis){
    return dis(gen);
}

Matrix* Matrix::transposta(){
    Matrix *m{new Matrix{this->col,this->lin,false}};
    for(unsigned short i=0;i<this->lin;++i){
        for(unsigned short j=0;j<this->col;++j){
            m->setValue(this->getValue(i, j), j, i);
        }
    }
    return m;
}
