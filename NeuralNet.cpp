#include "NeuralNet.hpp"

#include <iostream>
#include <vector>
#include <cmath>

void NeuralNet::imprimeNet(){
    std::cout<< "CAMADA: "<< 0 << std::endl;
    std::cout<<std::endl;
    Matrix *m = this->camadas.at(0)->matrizarValores(); 
    m->imprimeMatrix();
    std::cout<<std::endl;
    for(unsigned int i = 1;i < this->camadas.size();++i){
        std::cout<< "CAMADA ATIVADA: "<< i << std::endl;
        std::cout<<std::endl;
        m = this->camadas.at(i)->matrizarAtivados();
        //this->camadas.at(i)->getValue();
        m->imprimeMatrix();
        std::cout<<std::endl;
    }
    delete m;
}

void NeuralNet::setEntradas(std::vector<std::vector<double>> entradas, int n){
    for(unsigned int i = 0;i < entradas.at(n).size();++i){
        
        this->camadas.at(0)->setValor(i,entradas.at(n).at(i));
    }
}

NeuralNet::NeuralNet(std::vector<unsigned int> topologia,double valorEsperado, unsigned int epocas, std::vector<std::vector<double>> entradas)
    :tamTopo{(int)topologia.size()},valorEsperado{valorEsperado},epocas{epocas},topologia{topologia},entradas{entradas}
    {
        
        for(int i = 0;i < this->tamTopo;++i){
            Layer *l{new Layer{(int)topologia.at(i)}};
            this->camadas.push_back(l);
        }
        for(int i=0;i < (this->tamTopo)-1;++i){
            Matrix *m{new Matrix{(int)topologia.at(i),(int)topologia.at(i+1),true}};
            this->pesos.push_back(m);
        }
    }

Matrix* NeuralNet::atualizaPesos(Matrix* pesos, double erro,Matrix* valores){
    //std::cout<<"GetLin  = "<<pesos->getLin()<<std::endl;
    //std::cout<<"GetCol  = "<<pesos->getCol()<<std::endl;
    for(int i=0;i<pesos->getLin();++i){
        for(int j=0;j<pesos->getCol();j++){
            //std::cout<<"Peso antes: "<<pesos->getValue(i,j)<<std::endl;

            double novoPeso = pesos->getValue(i,j) + valores->getValue(0,i)*erro;
            //std::cout<<"atualiza"<<std::endl;
            
            pesos->setValue(novoPeso,i,j);
        }
    }
    return pesos;
}

double NeuralNet::valorNeuronio(Matrix* valores,Matrix* pesos, int tam, int idNeuron){
    double valor = 0.0;
    for(unsigned int i = 0;(int) i < tam-1; ++i){ //tam-1 pq ta vindo como 3
        valor += valores->getValue(0,i) * pesos->getValue(i,idNeuron);
    }
    if(pesos == this->pesos.at(this->pesos.size()-1)){
        std::cout<<"valores: "<<std::endl;
        valores->imprimeMatrix();
        std::cout<<"pesos: "<<std::endl;
        pesos->imprimeMatrix();
        std::cout<<"tam: "<<tam<<std::endl;
        std::cout<<"valor: "<<valor<<std::endl;
    }
    
    return valor;
}

void NeuralNet::treinar(){
    Matrix* m;// = this->camadas.at(0)->matrizarDerivados();
    int i=0;
    std::vector<Matrix*> valoresPassado;
    //m->imprimeMatrix();
    //std::cout<<std::endl;
    Matrix* valores;
    double valor;
    for(int ent = 0;(unsigned int) ent < this->entradas.size();++ent){

        this->setEntradas(this->entradas,ent);

        for(unsigned int e=0;e<this->epocas;++e){
            for( i = 1;(unsigned int) i < (this->camadas.size()-1);++i){

                for(int j = 0;j <this->camadas.at(i)->numNeurons();++j){
                    
                    valores = this->camadas.at(i-1)->matrizarValores();//transformar
                    
                    valor = this->valorNeuronio(valores,this->pesos.at(i-1), this->topologia.at(i-1), j);
                    
                    Neuron* n{new Neuron{valor}};//problema: pega o valor da camada antesrior de forma linear como a segunda camada tem 2 neuronios a terceira tem 3 da erro
                
                    this->camadas.at(i)->setValor(j,n->getValActived());
                    
                    delete n;
                }

                m = this->camadas.at(i)->matrizarValores();

                //std::cout<<std::endl;
                
            }
            //ultimo neuronio
            valores = this->camadas.at(this->camadas.size()-2)->matrizarValores();
            //valores->imprimeMatrix();
            std::cout<<std::endl;
            valor = this->valorNeuronio(valores,this->pesos.at(this->pesos.size()-1), 1, 0);
            //std::cout<<"valor: "<<valor<<std::endl;
            this->camadas.at(this->camadas.size()-1)->setValor(0,valor);

            for( i =0;(unsigned int) i < this->camadas.size();++i){
                valoresPassado.push_back(this->camadas.at(i)->matrizarValores());
            }
            //std::cout<<this->camadas.at(this->camadas.size()-1)->matrizarValores()->getValue(0,0)<<std::endl;
            std::vector<Matrix*> novosPesos(this->pesos.size());
            for(int i = 0;(unsigned int) i < (this->camadas.size()-1);++i){
                novosPesos.at(i) = this->atualizaPesos(this->pesos.at(i),
                                    std::abs(this->camadas.at(this->camadas.size()-1)->matrizarValores()->getValue(0,0)-(this->valorEsperado)),
                                    valoresPassado.at(i));
                //std::cout<<std::endl;
            }
            this->pesos.assign(novosPesos.begin(),novosPesos.end());
        }
    }
}

double NeuralNet::preditar(std::vector<double> numeros){
    Matrix *m;
    for(unsigned int i = 0;i < numeros.size();++i){
        this->camadas.at(0)->setValor(i,numeros.at(i));
    }
    for( int i = 1;(unsigned int) i < (this->camadas.size()-1);++i){

            for(int j = 0;j <this->camadas.at(i)->numNeurons();++j){
                
                Matrix* valores = this->camadas.at(i-1)->matrizarValores();//transformar
                
                double valor = this->valorNeuronio(valores,this->pesos.at(i-1), this->topologia.at(i-1), j);
                
                Neuron* n{new Neuron{valor}};//problema: pega o valor da camada antesrior de forma linear como a segunda camada tem 2 neuronios a terceira tem 3 da erro
             
                this->camadas.at(i)->setValor(j,n->getValActived());
                
                delete n;
            }

            m = this->camadas.at(i)->matrizarValores();

            //std::cout<<std::endl;
            
    }
    return this->camadas.at(this->camadas.size()-1)->getValorNeuronio(0);
}
