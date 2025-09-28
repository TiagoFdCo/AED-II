#include <iostream>
#include <list>
#include <utility>

using namespace std;

using uint = unsigned int;
using Vertex = unsigned int;
using Weight = float;
using VertexWeightPair = pair<Vertex, Weight>;

class WeightedgraphAL{
private:
    uint num_vertices;
    uint num_edges;
    list<VertexWeightPair> *adj; //vetor dinamico de pares de (Vertex, Weight)
    Weight weight;

public:
    //construtores
    WeightedgraphAL(): num_vertices(0), num_edges(0), weight(0){}
    WeightedgraphAL(uint num_vertices): num_vertices(num_vertices), num_edges(0), weight(0)
    {
        adj = new list<VertexWeightPair> [num_vertices];
    }

    //destrutor
    ~WeightedgraphAL(){
        delete[] adj;
        adj = nullptr;
    }

    void add_edge(const Vertex& u, const Vertex& v, const Weight& w);
    void remove_edge(const Vertex& u, const Vertex& v, const Weight& w); 
    list<pair<Vertex, Weight>> get_adj(const Vertex& u) const;
    void print_graph(const WeightedgraphAL& g) const; 
    uint get_num_vertices() const;
    uint get_num_edges() const;
    Weight get_weight() const; 

};

//Metodos
void WeightedgraphAL::add_edge(const Vertex& u, const Vertex& v, const Weight& w){
    try{
        if (u < 0 ||
            v < 0 ||
            u > num_vertices ||
            v > num_vertices ||
            u == v){
            throw invalid_argument("Argumentos invalidos!");
        }
    }
    catch(const invalid_argument& e){
        cout << "Erro: " << e.what() << endl;
    }

    adj[u].push_back({v, w});
    //adiciona o peso junto ao elemento adjacente

    adj[v].push_back({u, w});
    
    num_edges++;
}

void WeightedgraphAL::remove_edge(const Vertex& u, const Vertex& v, const Weight& w){
    adj[u].remove({v, w});
    adj[v].remove({u, w});
    num_edges--;
}

list<VertexWeightPair> WeightedgraphAL::get_adj(const Vertex& u) const{
    try {
        if (u > num_vertices || u < 0){
            throw invalid_argument("Argumentos invalidos");
        }
    }
    catch(const invalid_argument& e){
        cout << "Erro:" << e.what() << endl;
    }

    return adj[u];
}

uint WeightedgraphAL::get_num_vertices() const{
    return num_vertices;
}

uint WeightedgraphAL::get_num_edges() const{
    return num_edges;
}

Weight WeightedgraphAL::get_weight() const{
    return weight;
}

void WeightedgraphAL::print_graph(const WeightedgraphAL& g) const{
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;

    for (uint i = 0; i < num_vertices; i++){
        cout << i << ": ";
        for (auto &p : g.get_adj(i)) {
        uint v = p.first;   // vertice vizinho
        float w = p.second;  // peso da aresta
        cout << "(" << v << ", " << w << "), ";
        }
        cout << endl;
    }
}

int main(){
    int n, m; //respectivamente: num_vertices e num_edges
    int u, v; // relacao entre vertice u e v
    float w; //peso da relacao entre vertice u e v

    cin >> n;
    cin >> m;

    WeightedgraphAL g(n);

    for (int i = 0 ; i < m; i++){
        cin >> u;
        cin >> v;
        cin >> w;

        g.add_edge(u, v, w);
    }

    g.print_graph(g); 

    return 0;
}