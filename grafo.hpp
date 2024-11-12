#ifndef GRAFO_HPP
#define GRAFO_HPP
#include <map>
#include <string>
#include <vector>

class grafo{
    private:
        std::map<std::string, std::vector<std::string>> grafo_;
    
    public:
        grafo(int vertices);
        void AdicionaAresta(std::string origem, std::string destino);
        std::string EncontraCapital();
        int BatalhoesSecundarios(const std::string& capital);
        ~grafo();

};



#endif