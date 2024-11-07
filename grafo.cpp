#include "grafo.hpp"
#include <queue>

grafo::grafo(int vertices){

}

void grafo::AdicionaAresta(std::string origem,std::string destino){
    grafo_[origem].push_back(destino);
}

std::string grafo::EncontraCapital(){
    int max = 0;
    std::string capital;
    for(auto it=grafo_.begin(); it!=grafo_.end();it++){
        int n = BFSadaptada(grafo_,it->first);
        if(n>max){
            max = n;
            capital = it->first;
        }
    }
    return capital;
}

int BFSadaptada(const std::map<std::string, std::vector<std::string>>& grafo, const std::string& inicial){
    std::queue<std::string> fila;
    std::map<std::string, bool> visitado;
    int cont = 0;
    visitado[inicial] = true;
    fila.push(inicial);

    while(!fila.empty()){
        std::string atual = fila.front();
        fila.pop();
        cont ++;
        for(const auto& vizinho : grafo.at(atual)){
            if(visitado[vizinho]==false){
                visitado[vizinho] = true;
                fila.push(vizinho);
            }

        }
    }
    return cont;
}