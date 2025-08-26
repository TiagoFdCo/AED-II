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
    vector<vector<Weight>> adj; //matriz dinamica de adjacencia

public:
    //construtores
    GraphAM(): num_vertices(0), num_edges(0){}
    GraphAM(uint num_vertices): num_vertices(num_vertices), num_edges(0), adj(num_vertices, vector<Weight>(num_vertices, 0)){}
        /*
        Criacao de matriz dinamica no proprio construtor, inicializa uma matriz de ordem num_vertices e inicializa todos com o valor 0, muito incrivel mesmo
        */
    //destrutor
    ~GraphAM(){}//A destruicao de um std::vector eh automatica

    //metodos
    void add_edge(const Vertex& u, const Vertex& v);
    void remove_edge(const Vertex& u, const Vertex& v);
    list<Vertex> get_adj(const Vertex& v) const;
    uint get_num_vertices() const;
    uint get_num_edges() const;
    void display_graph(const GraphAM& g);
    vector<vector<Weight>> get_adj_matrix() const;
};

//Metodos
void GraphAM::add_edge(const Vertex& u, const Vertex& v){
    try{
        if(u > num_vertices || //colocar a condicao de u ou v serem menores que zero eh desprezivel uma vez que estamos tratando de uints
        v > num_vertices ||
        u == v){
            throw invalid_argument("Argumentos invalidos!");
        }
    }catch(const invalid_argument& e){
        cout << "Erro: " << e.what() << endl;
    }

    adj[u][v] = 1;
    adj[v][u] = 1;
    num_edges++;
}

void GraphAM::remove_edge(const Vertex& u, const Vertex& v){
    adj[u][v] = 0;
    adj[v][u] = 0;
    num_edges--;
}

list<Vertex> GraphAM::get_adj(const Vertex& v) const{
    list<Vertex> neighbors;

    try{
        if(v > num_vertices){
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

vector<vector<Weight>> GraphAM::get_adj_matrix() const{
    return adj;
}

uint GraphAM::get_num_vertices() const{
    return num_vertices;
}

uint GraphAM::get_num_edges() const{
    return num_edges;
}

void GraphAM::display_graph(const GraphAM& g){
    cout << "num_vertices: " << g.num_vertices << endl;
    cout << "num_edges: " << g.num_edges << endl;

    for (uint i = 0; i < g.num_vertices; i++){
        for (uint j = 0; j < g.num_vertices; j++){
            cout << g.adj[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    uint n = 0;
    uint m = 0;
    uint u = 0;
    uint v = 0;

    //criacao do grafo de ordem n
    cin >> n; //qtd_vertices
    cin >> m; //qtd_arestas
    GraphAM g(n);

    for (uint i = 0; i < m ; i++){
        cin >> u;
        cin >> v;
        g.add_edge(u, v);
    }

    g.display_graph(g);
    return 0;
}