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

    return 0;
}