#ifndef GRAFO_HPP
#define GRAFO_HPP
#include <map>
#include <string>
#include <vector>
#include <stack>

class grafo{
    private:
        std::map<std::string, std::vector<std::string>> grafo_;
    
    public:
        grafo(int vertices);
        void AdicionaAresta(std::string origem, std::string destino);
        std::string EncontraCapital();
        std::pair<int, std::vector<std::string>> BatalhoesSecundarios(const std::string& capital);
        ~grafo();

};



#endif