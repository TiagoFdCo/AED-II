#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <limits>

using namespace std;

//declaracao dos apelidos
using uint = unsigned int;
using Vertex = unsigned int;
using Weight = float;

constexpr double INF = numeric_limits<double>::infinity(); //declaracao de infinito usando limits para preencher a matriz

class PgraphAM{
private:
    uint num_vertices;
    uint num_edges;
    vector<vector<Weight>> adj; //matriz dinamica de adjacencia

public:
    //construtores
    PgraphAM(): num_vertices(0), num_edges(0){}
    PgraphAM(uint num_vertices): num_vertices(num_vertices), num_edges(0), adj(num_vertices, vector<Weight>(num_vertices, INF)){}
        /*
        Criacao de matriz dinamica no proprio construtor, inicializa uma matriz de ordem num_vertices e inicializa todos com o valor 0, muito incrivel mesmo
        */
    //destrutor
    ~PgraphAM(){}//A destruicao de um std::vector eh automatica

    //metodos
    void add_edge(const Vertex& u, const Vertex& v, const Weight& w);
    void remove_edge(const Vertex& u, const Vertex& v);
    list<Vertex> get_adj(const Vertex& v) const;
    uint get_num_vertices() const;
    uint get_num_edges() const;
    void display_graph(const PgraphAM& g);
    vector<vector<Weight>> get_adj_matrix() const;
};

//Metodos
void PgraphAM::add_edge(const Vertex& u, const Vertex& v, const Weight& w){
    try{
        if(u > num_vertices || //colocar a condicao de u ou v serem menores que zero eh desprezivel uma vez que estamos tratando de uints
        v > num_vertices ||
        u == v){
            throw invalid_argument("Argumentos invalidos!");
        }
    }catch(const invalid_argument& e){
        cout << "Erro: " << e.what() << endl;
    }

    adj[u][v] = w; //adiciona o valor do proprio peso na posicao que mostra a relacao entre u e v
    adj[v][u] = w;
    num_edges++;
}

void PgraphAM::remove_edge(const Vertex& u, const Vertex& v){
    adj[u][v] = INF;
    adj[v][u] = INF;
    num_edges--;
}

list<Vertex> PgraphAM::get_adj(const Vertex& v) const{
    list<Vertex> neighbors;

    try{
        if(v > num_vertices){
            throw invalid_argument("Argumento invalido!");
        }

        for (uint u = 0; u < num_vertices; u++){
            if (adj[v][u] != INF){
                neighbors.push_back(u);
            }
        }
    }
    catch(const invalid_argument& e){
        cout << "Erro: " <<e.what() << endl;
    }

    return neighbors;
}

vector<vector<Weight>> PgraphAM::get_adj_matrix() const{
    return adj;
}

uint PgraphAM::get_num_vertices() const{
    return num_vertices;
}

uint PgraphAM::get_num_edges() const{
    return num_edges;
}

void PgraphAM::display_graph(const PgraphAM& g){
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
    Weight w = 0;

    //criacao do grafo de ordem n
    cin >> n; //qtd_vertices
    cin >> m; //qtd_arestas
    PgraphAM g(n);

    for (uint i = 0; i < m ; i++){
        cin >> u;
        cin >> v;
        cin >> w;

        g.add_edge(u, v, w);
    }

    g.display_graph(g);
    return 0;
}