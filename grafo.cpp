#include "grafo.hpp"


grafo::grafo(){

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


bool EhEuleriano(const std::map<std::string, std::vector<std::string>>& subgrafo) {
    std::map<std::string, int> grau_entrada, grau_saida;

    // Calcula graus de entrada e saída
    for (const auto& [vertice, adjacentes] : subgrafo) {
        grau_saida[vertice] += adjacentes.size();
        for (const auto& destino : adjacentes) {
            grau_entrada[destino]++;
        }
    }

    // Verifica se os graus de entrada e saída são iguais para todos os vértices
    for (const auto& [vertice, _] : subgrafo) {
        if (grau_entrada[vertice] != grau_saida[vertice]) {
            return false;
        }
    }

    // Verifica conectividade usando componentes fortemente conectados (Kosaraju ou equivalente)
    std::map<std::string, bool> visitado;
    std::stack<std::string> ordem;

    for (const auto& [vertice, _] : subgrafo) {
        if (!visitado[vertice]) {
            preOrdem(vertice, visitado, ordem, subgrafo);
        }
    }

    auto subgrafo_invertido = InverteGrafo(subgrafo);
    visitado.clear();
    std::vector<std::string> vazio;  // Vetor temporário vazio
    DFS(ordem.top(), visitado, subgrafo_invertido, vazio);
    for (const auto& [vertice, _] : subgrafo) {
        if (!visitado[vertice]) return false;
    }

    return true;
}

// Função para encontrar um circuito Euleriano
std::vector<std::string> EncontraCircuitoEuleriano(
    const std::map<std::string, std::vector<std::string>>& subgrafo,
    const std::string& origem) {
    std::map<std::string, std::vector<std::string>> grafo_mutavel = subgrafo;
    std::stack<std::string> stack;
    std::vector<std::string> circuito;

    stack.push(origem);
    while (!stack.empty()) {
        std::string atual = stack.top();
        if (!grafo_mutavel[atual].empty()) {
            std::string proximo = grafo_mutavel[atual].back();
            grafo_mutavel[atual].pop_back();
            stack.push(proximo);
        } else {
            circuito.push_back(atual);
            stack.pop();
        }
    }

    std::reverse(circuito.begin(), circuito.end());
    return circuito;
}

// Implementação de PatrulhamentoPreventivo
std::map<std::string, std::vector<std::string>> grafo::PatrulhamentoPreventivo() {
    std::map<std::string, std::vector<std::string>> patrulhas;

    // Identifica a capital
    std::string capital = EncontraCapital();

    // Identifica os batalhões secundários
    auto [num_batalhoes, locais_batalhoes] = BatalhoesSecundarios(capital);

    // Adiciona capital e batalhões secundários à lista de vértices para análise
    std::vector<std::string> batalhoes = locais_batalhoes;
    batalhoes.push_back(capital);

    // Itera sobre todos os batalhões (capital + secundários)
    for (const auto& batalhao : batalhoes) {
        // Subgrafo alcançável a partir do batalhão atual
        std::map<std::string, std::vector<std::string>> subgrafo;
        std::queue<std::string> fila;
        std::map<std::string, bool> visitado;

        fila.push(batalhao);
        visitado[batalhao] = true;

        // Constrói o subgrafo alcançável
        while (!fila.empty()) {
            std::string atual = fila.front();
            fila.pop();

            subgrafo[atual] = grafo_[atual];
            for (const auto& vizinho : grafo_[atual]) {
                if (!visitado[vizinho]) {
                    visitado[vizinho] = true;
                    fila.push(vizinho);
                }
            }
        }

        // Verifica se o subgrafo é Euleriano
        if (EhEuleriano(subgrafo)) {
            // Encontra o circuito Euleriano para o subgrafo
            std::vector<std::string> rota = EncontraCircuitoEuleriano(subgrafo, batalhao);
            patrulhas[batalhao] = rota;
        }
    }

    return patrulhas;
}


grafo::~grafo(){}