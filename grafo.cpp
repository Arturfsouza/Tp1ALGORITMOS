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

std::map<std::string, std::vector<std::string>> InverteGrafo(const std::map<std::string, std::vector<std::string>>& grafo){
    std::map<std::string, std::vector<std::string>> grafo_inverso;
    for(const auto& [origem,destinos] : grafo){
        if(grafo_inverso.find(origem) == grafo_inverso.end()){
            grafo_inverso[origem] = {};
        }
        for(const auto& destino : destinos){
            grafo_inverso[destino].push_back(origem);
        }
    }
    return grafo_inverso;
}

void preOrdem(const std::string& vertice, std::map<std::string, bool>& visitado, std::stack<std::string>& ordem, const std::map<std::string, std::vector<std::string>>& grafo){
    visitado[vertice] = true;
    for(const auto& vizinho : grafo.at(vertice)){
        if(!visitado[vizinho]){
            preOrdem(vizinho, visitado, ordem, grafo);
        }
    }
    ordem.push(vertice);
}

void DFS(const std::string& vertice, std::map<std::string, bool>& visitado, const std::map<std::string, std::vector<std::string>>& grafo, std::vector<std::string>& cfc){
    visitado[vertice] = true;
    cfc.push_back(vertice);
    for(const auto& vizinho : grafo.at(vertice)){
        if(!visitado[vizinho]){
            DFS(vizinho, visitado, grafo, cfc);
        }
    }
}

std::pair<int, std::vector<std::string>> grafo::BatalhoesSecundarios(const std::string& capital){
    std::stack<std::string> ordem;
    std::map<std::string, bool> visitado;

    for(const auto& [vertice,_] : grafo_){
        if(!visitado[vertice]){
            preOrdem(vertice, visitado, ordem, grafo_);
        }
    }

    auto grafo_invertido = InverteGrafo(grafo_);

    visitado.clear();
    int num_batalhoes = 0;
    std::vector<std::string> locais_batalhoes;

    while(!ordem.empty()){
        std::string vertice = ordem.top();
        ordem.pop();
        int eh_capital = 0; //flag para detectar se eh capital
        if(!visitado[vertice]){
            std::vector<std::string> cfc;
            DFS(vertice, visitado, grafo_invertido, cfc);

            for(auto it= cfc.begin(); it!=cfc.end(); it++){
                if (*it == capital){
                    eh_capital = 1;
                }
            }
            if(eh_capital == 0){
                num_batalhoes++;
                locais_batalhoes.push_back(cfc[0]);
            }
        }
    }
    return {num_batalhoes, locais_batalhoes};
}





grafo::~grafo(){}