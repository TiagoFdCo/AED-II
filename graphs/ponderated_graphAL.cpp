#include <iostream>
#include <list>
#include <utility>

using namespace std;

typedef unsigned int uint;
typedef unsigned int Vertex;
typedef float Weight;

class PgraphAL{
private:
    uint num_vertices;
    uint num_edges;
    list<pair<Vertex, Weight>> *adj; //vetor dinamico
    Weight weight;

public:
    //construtores
    PgraphAL(): num_vertices(0), num_edges(0), weight(0){}
    PgraphAL(uint num_vertices): num_vertices(num_vertices), num_edges(0), weight(0)
    {
        adj = new list<pair<Vertex, Weight>> [num_vertices];
    }

    //destrutor
    ~PgraphAL(){
        delete[] adj;
    }

    //metodos abstraidos
    void add_edge(Vertex u, Vertex v, Weight w);
    void remove_edge(Vertex u, Vertex v, Weight w); 
    list<pair<Vertex, Weight>> get_adj(Vertex u);
    void print_graph(); 
    uint get_num_vertices();
    uint get_num_edges();
    Weight get_weight(); 

};

//Metodos
void PgraphAL::add_edge(Vertex u, Vertex v, Weight w){
    adj[u].push_back({v, w});
    //adiciona o peso junto ao elemento adjacente

    adj[v].push_back({u, w});
    
    num_edges++;
}

void PgraphAL::remove_edge(Vertex u, Vertex v, Weight w){
    adj[u].remove({v, w});
    adj[v].remove({u, w});
    num_edges--;
}

list<pair<Vertex, Weight>> PgraphAL::get_adj(Vertex u){
    return adj[u];
}

uint PgraphAL::get_num_vertices(){
    return num_vertices;
}

uint PgraphAL::get_num_edges(){
    return num_edges;
}

Weight PgraphAL::get_weight(){
    return weight;
}

void PgraphAL::print_graph(){
    for (uint i = 0; i < num_vertices; i++){
        cout << i << ": ";
        for (auto &p : adj[i]) {
        uint v = p.first;   // vértice vizinho
        uint w = p.second;  // peso da aresta
        cout << "(" << v << ", " << w << ") ";
        }
        cout << endl;
    }
}

int main(){
    PgraphAL g(5);

    g.add_edge(1, 0, 3);
    g.add_edge(3, 2, 4);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 4, 0);

    g.print_graph(); 

    return 0;
}