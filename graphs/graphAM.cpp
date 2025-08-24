#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

using namespace std;

//declaracao dos apelidos
using uint = unsigned int;
using Vertex = unsigned int;
using Weight = unsigned int;

class GraphAM{
private:
    uint num_vertices;
    uint num_edges;
    Weight** adj; //matriz dinamica de adjacencia

public:
    //construtores
    GraphAM(): num_vertices(0), num_edges(0){}
    GraphAM(uint num_vertices): num_vertices(num_vertices), num_edges(0){
        adj = new Weight* [num_vertices];
        for (uint i = 0; i < num_vertices; i++){
            adj[i] = new Weight[num_vertices];
        }
        /*
        Criacao de matriz dinamica, indexada com numero de vertices informado pelo usuario
        */

        //preenchendo o grafo com zeros
        uint valor = 0;
        for (uint j = 0; j < num_vertices; j++){
            for(uint k = 0; k < num_vertices; k++){
                adj[j][k] = valor;
            }
        }
    }
    //destrutor
    ~GraphAM(){
        for (uint j = 0; j < num_vertices; j++){
            delete[] adj[j]; //libera as linhas
        }
        delete[] adj; //libera o vetor
    }

    //metodos
    void add_edge(const Vertex& u, const Vertex& v);
    void remove_edge(const Vertex& u, const Vertex& v);
    list<Vertex> get_adj(const Vertex& v) const;
    uint get_num_vertices() const;
    uint get_num_edges() const;
    void display_graph() const;
};

//Metodos
void GraphAM::add_edge(const Vertex& u, const Vertex& v){
    adj[u][v] = 1;
    adj[v][u] = 1;
    num_edges++;
}

void GraphAM::remove_edge(const Vertex& u, const Vertex& v){
    adj[u][v] = 0;
    adj[v][u] = 0;
    num_edges--;
}

//TESTAR ESSA PORRA AQUI
list<Vertex> GraphAM::get_adj(const Vertex& v) const{
    list<Vertex> neighbors;

    try{
        if(v >= num_vertices){
            throw invalid_argument("Argumento invalido!");
        }

        for (uint u = 0; u < num_vertices; u++){
            if (adj[v][u] != 0){
                neighbors.push_back(u);
            }
        }
    }
    catch(const invalid_argument& e){
        cout << "Erro: " <<e.what() << endl;
    }

    return neighbors;
}

uint GraphAM::get_num_vertices() const{
    return num_vertices;
}

uint GraphAM::get_num_edges() const{
    return num_edges;
}

void GraphAM::display_graph() const{
    for (uint i = 0; i < num_vertices; i++){
        for (uint j = 0; j < num_vertices; j++){
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    GraphAM g(4);

    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 2);

    g.display_graph();
    return 0;
}