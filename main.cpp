#include "grafo.hpp"
#include <iostream>

int main(){
    int v;
    int a;
    std::cin>>v>>a;
    grafo g(v);
    std::string origem;
    std::string destino;
    for(int i=0;i<a;i++){
        std::cin >> origem>>destino;
        g.AdicionaAresta(origem,destino);}
    std::string capital = g.EncontraCapital();
    std::cout<<capital<<std::endl;
    auto n = g.BatalhoesSecundarios(capital);
    std::cout<<n.first<<std::endl;
    for(auto it = n.second.begin(); it != n.second.end(); it++){
        std::cout<<*it<<std::endl;
    }

    auto patrulhas = g.PatrulhamentoPreventivo();
    if (patrulhas.empty()) {
        std::cout << "Nenhum patrulhamento possível" << std::endl;
    } else {
        std::cout << patrulhas.size() << std::endl; // Número de patrulhamentos possíveis
        for (const auto& [batalhao, rota] : patrulhas) {
            for (const auto& local : rota) {
                std::cout << local << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}