#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>


//Implementacao de apelidos usando "using"
using namespace std;

using uint = unsigned int;
using Vertex = unsigned int;

//Implementacao da classe GraphAL
class GraphAL{
private:
    uint num_vertices;
    uint num_edges;
    list<Vertex> *adj; //vetor dinamico

public:
    //construtores
    GraphAL(): num_vertices(0), num_edges(0){}
    GraphAL(uint num_vertices): num_vertices(num_vertices), num_edges(0)
    {
        adj = new list<Vertex> [num_vertices]; /*
        alocamento de vetor dinamico indexado pelo numero de vertices,
        adicionado pelo usuario.*/
    }

    //destrutor
    ~GraphAL(){
            delete[] adj; //pra vetores dinamicos, usar delete[]
    }

    //metodos abstraidos
    void add_edge(const Vertex& u, const Vertex& v);
    void remove_edge(const Vertex& u, const Vertex& v);
    list<Vertex> get_adj(const Vertex& u) const;
    void print_adjacency_list(const GraphAL& g); 
    uint get_num_vertices() const;
    uint get_num_edges() const;

};

//Metodos
void GraphAL::add_edge(const Vertex& u, const Vertex& v){
    //Tratamento de excecao
    try{
        if(u >= num_vertices ||
            v >= num_vertices ||
            u == v ||
            u < 0 ||
            v < 0){
            throw invalid_argument("Argumentos invalidos!");
        }
    }
    catch(const invalid_argument& e){
        cout << "Erro: " << e.what() << endl;
    }
    adj[u].push_back(v);
    adj[v].push_back(u);
    num_edges++;
}

void GraphAL::remove_edge(const Vertex& u, const Vertex& v){
    adj[u].remove(v);
    adj[v].remove(u);
    num_edges--;
}

 list<Vertex> GraphAL::get_adj(const Vertex& u) const{
    try{
        if (u > num_vertices || u < 0){
            throw invalid_argument("Argumento invalido!");
        }
    }
    catch(const invalid_argument& e){
        cout << "Erro: " << e.what() << endl;
    }
    return adj[u];
}

uint GraphAL::get_num_vertices() const{
    return num_vertices;
}

uint GraphAL::get_num_edges() const{
    return num_edges;
}

void GraphAL::print_adjacency_list(const GraphAL& g){
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;

    for (uint j = 0; j < g.get_num_vertices(); j++){
        cout << j << ": ";
        for (Vertex v : g.get_adj(j)){
            cout << v << ", ";
        }
        cout << endl;
    }
}

int main(){
    uint u;
    uint v;
    uint qtd_vertices;
    uint qtd_arestas;

    cin >> qtd_vertices;
    cin >> qtd_arestas;

    GraphAL g(qtd_vertices);

    for (int k = 0; k < qtd_arestas; k++){
        cin >> u;
        cin >> v;
        g.add_edge(u, v);
    }

    g.print_adjacency_list(g);
    return 0;
}