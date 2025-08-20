#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

using namespace std;

typedef unsigned int uint;
typedef unsigned int Vertex;

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
        adj = new list<Vertex> [num_vertices];
    }

    //destrutor
    //~GraphAL();

    //metodos abstraidos
    void add_edge(Vertex u, Vertex v);
    void remove_edge(Vertex u, Vertex v);
    list<Vertex> get_adj(Vertex u);
    void print_graph(); //FAZ ESSA PORRA AQUI!!!
    uint get_num_vertices();
    uint get_num_edges();

};

//Metodos
void GraphAL::add_edge(Vertex u, Vertex v){
    /*if (u < 0 || v < 0){
        throw invalid_argument("Vertice(s) invalido(s)");
    }*/
    adj[u].push_back(v);
    adj[v].push_back(u);
    num_edges++;
}

void GraphAL::remove_edge(Vertex u, Vertex v){
    adj[u].remove(v);
    adj[v].remove(u);
    num_edges--;
}

list<Vertex> GraphAL::get_adj(Vertex u){
    return adj[u];
}

uint GraphAL::get_num_vertices(){
    return num_vertices;
}

uint GraphAL::get_num_edges(){
    return num_edges;
}

void GraphAL::print_graph(){
    for (int i = 0; i < num_vertices; i++){
        cout << i << ": ";
        for (Vertex v : adj[i]){
            cout << v << " ";
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

    g.print_graph();

    return 0;
}