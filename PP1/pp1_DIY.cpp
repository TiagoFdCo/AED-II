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
        for (int i = 0; i < num_vertices; i++){
            delete[] adj; //pra vetores dinamicos, usar delete[]
        }
    }

    //metodos abstraidos
    void add_edge(const Vertex& u, const Vertex& v);
    void remove_edge(const Vertex& u, const Vertex& v);
    list<Vertex> get_adj(const Vertex& u);
    void print_adjascency_list(GraphAL g); 
    uint get_num_vertices();
    uint get_num_edges();

};

//Metodos
void GraphAL::add_edge(const Vertex& u, const Vertex& v){
    //Tratamento de exceção
    try{
        if(u > num_vertices ||
            v > num_vertices ||
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

list<Vertex> GraphAL::get_adj(const Vertex& u){
    try{
        if (u > num_vertices || u < 0){
            throw invalid_argument("Argumento inválido!");
        }
    }
    catch(const invalid_argument& e){
        cout << "Erro: " << e.what() << endl;
    }
    return adj[u];
}

uint GraphAL::get_num_vertices(){
    return num_vertices;
}

uint GraphAL::get_num_edges(){
    return num_edges;
}

void GraphAL::print_adjascency_list(GraphAL g){
    cout << "numero_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;

    for (int j = 0; j < g.get_num_vertices(); j++){
        cout << j << ": ";
        for (Vertex v : g.get_adj(j)){
            cout << v << ", ";
        }
        cout << endl;
    }
}

int main(){
    GraphAL g(5);

    g.add_edge(1, 0);
    g.add_edge(3, 2);
    g.add_edge(1, 2);
    g.add_edge(1, 4);

    g.print_adjascency_list(g);

    cout << g.get_num_vertices();

    return 0;
}