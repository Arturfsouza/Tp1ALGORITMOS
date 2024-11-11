#include "grafo.hpp"
#include <queue>

grafo::grafo(int vertices){

}

void grafo::AdicionaAresta(std::string origem,std::string destino){
    grafo_[origem].push_back(destino);
    if(grafo_.find(destino)==grafo_.end()){
        grafo_[destino]={};
    }
}



int BFSadaptada(const std::map<std::string, std::vector<std::string>>& grafo, const std::string& inicial){
    std::queue<std::pair<std::string, int>> fila;
    std::map<std::string, bool> visitado;
    std::map<std::string,int> distancias;
    int max = 0;
    int vertices_alcancaveis = 0;
    visitado[inicial] = true;
    fila.push({inicial,0});
    distancias[inicial] = 0;
    int cont = 0;
    while(!fila.empty()){
        std::string atual = fila.front().first;
        int dist = fila.front().second;
        fila.pop();
        vertices_alcancaveis++;
        for(const auto& vizinho : grafo.at(atual)){
            if(visitado[vizinho]==false){
                visitado[vizinho] = true;
                distancias[vizinho] = dist+1;
                fila.push({vizinho, dist + 1});
                if(distancias[vizinho]>max){
                    max = distancias[vizinho];
                }
            }

        }
    }
    if(vertices_alcancaveis == grafo.size()){
        return max;
    }
    else{
        return -1;
    }
}

std::string grafo::EncontraCapital(){
    int min = 0;
    int cont = 0;
    std::string capital;
    for(auto it=grafo_.begin(); it!=grafo_.end();it++){
        int n = BFSadaptada(grafo_,it->first);
        if(n!= -1){
            if (cont == 0){
                min = n;
                capital = it->first;
            }
            else if(n<min){
                min= n;
                capital = it->first;
            }
            cont++;
        }
    }
    return capital;
}

grafo::~grafo(){}