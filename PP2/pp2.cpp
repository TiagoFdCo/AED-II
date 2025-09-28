#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <limits>

using namespace std;

// ESTRUTURAS DE DADOS E BUSCA
using uint = unsigned int;
using Vertex = unsigned int;

// INF e NIL
constexpr int INF = numeric_limits<int>::max();
constexpr Vertex NIL = numeric_limits<Vertex>::max();

// QUEUE 
template <typename T>
class Queue{
private:
    list<T> *qlist; //lista duplamente encadeada dinamica
    int num_itens;

public:

    //construtores
    Queue():num_itens(0){
        qlist = new list<T>(); // inicializo a lista nova 
    }

    //destrutor
    ~Queue(){
        delete qlist;
        qlist = nullptr;
    }
    void enqueue(T item); //adiciona um item 
    void dequeue(); //retira um item
    T front(); //retorna o item na frente da fila
    int size(); //retorna o tamanho da fila
    bool empty(); //verifica de a fila estah vazia (true ou false)
};

template<typename T>
void Queue<T>::enqueue(T item){
    qlist->push_back(item);
    num_itens++;
}

template<typename T>
void Queue<T>::dequeue(){
    qlist->pop_front();
    num_itens--;
}

template<typename T>
T Queue<T>::front(){
    return qlist->front();
}

template<typename T>
bool Queue<T>::empty(){
    if(num_itens == 0){
        return true;
    }
    return false;
}
// GraphAL
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
            u == v){
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
        if (u > num_vertices){
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

GraphAL fillGraph(){
    uint u;
    uint v;
    uint qtd_vertices;
    uint qtd_arestas;

    cin >> qtd_vertices;
    cin >> qtd_arestas;

    GraphAL g(qtd_vertices);

    for (uint k = 0; k < qtd_arestas; k++){
        cin >> u;
        cin >> v;
        g.add_edge(u, v);
    }

    g.print_adjacency_list(g);
    return g;
}

// BFS
enum class Color{ WHITE, GRAY, BLACK };

class BFS{
private:
    GraphAL& graph;
    vector<int> distance;
    vector<Color> color;
    vector<Vertex> parent;
    vector<Vertex> order;

public:
    BFS(GraphAL& g):
        graph(g),
        distance(g.get_num_vertices(), INF),
        color(g.get_num_vertices(), Color::WHITE),
        parent(g.get_num_vertices(), NIL) {}

    void runBFS(const Vertex& s){
        // reinicializa vetores caso sejam de execucoes anteriores
        for(size_t i=0;i<distance.size();++i){
            distance[i] = INF;
            color[i] = Color::WHITE;
            parent[i] = NIL;
        }
        order.clear();

        color[s] = Color::GRAY;
        distance[s] = 0;
        parent[s] = NIL;

        Queue<Vertex> q;
        q.enqueue(s);

        while (!q.empty()){
            Vertex u = q.front();
            q.dequeue();
            for (Vertex v : graph.get_adj(u)){
                if (color[v] == Color::WHITE){
                    color[v] = Color::GRAY;
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                    order.push_back(v);
                    q.enqueue(v);
                }
            }
            color[u] = Color::BLACK;
        }
    }

    int getDistance(const Vertex& v){ return distance[v]; }
};

// CHESSBOARD
class Chessboard{
private:
    GraphAL graph;

public:
    Chessboard(): graph(64){ createChessboard(); }

    void createChessboard(){
        int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
        int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};

        for (int x = 0; x < 8; x++){
            for (int y = 0; y < 8; y++){
                int u = x * 8 + y;
                for (int k = 0; k < 8; k++){
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8){
                        int v = nx * 8 + ny;
                        graph.add_edge(u, v);
                    }
                }
            }
        }
    }

    GraphAL& getGraph(){ return graph; }

    // conversoes
    pair<int,int> notacaoParaPosicao(const string& s){
        int col = s[0] - 'a';
        int row = s[1] - '1';
        return {row, col};
    }

    vector<int> getHorseMoves(const string& reiPos){
        pair<int,int> p = notacaoParaPosicao(reiPos);
        int x = p.first;
        int y = p.second;
        vector<int> moves;
        int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
        int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};
        for(int k = 0; k < 8; k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8){
                moves.push_back(nx * 8 + ny);
            }
        }
        return moves;
    }

    int notacaoParaIndice(const string& s){
        pair<int,int> p = notacaoParaPosicao(s);
        int x = p.first;
        int y = p.second;
        return x*8 + y;
    }
};

// EXECUCAO
void executaAplicacao(){
    Chessboard board;
    GraphAL& g = board.getGraph();

    int T;
    if(!(cin >> T)) return;

    for(int t=0; t<T; t++){
        vector<string> cavalos_pos(4);
        string rei_pos;
        for(int i=0;i<4;i++) cin >> cavalos_pos[i];
        cin >> rei_pos;

        vector<int> cavalos_idx(4);
        for(int i=0;i<4;i++) cavalos_idx[i] = board.notacaoParaIndice(cavalos_pos[i]);

        vector<int> alvos = board.getHorseMoves(rei_pos);

        vector<int> dist(4, INF);
        for(int i=0;i<4;i++){
            int src = cavalos_idx[i];
            // se o cavalo ja esta em uma casa que ameaca o rei
            bool jaAmeaca = false;
            for(int a : alvos) if(a == src) { jaAmeaca = true; break; }
            if(jaAmeaca) { dist[i] = 0; continue; }

            BFS bfs(g);
            bfs.runBFS(src);

            int best = INF;
            for(int a : alvos){
                int d = bfs.getDistance(a);
                if(d < best) best = d;
            }
            dist[i] = best;
        }

        int menor = INF;
        for(int i=0;i<4;i++) if(dist[i] < menor) menor = dist[i];

        if(menor == INF){
            // nenhum cavalo alcanca as casas que atacam o rei -> linha vazia
            cout << '\n';
        } else {
            bool first = true;
            for(int i=0;i<4;i++){
                if(dist[i] == menor){
                    if(!first) cout << ' ';
                    cout << dist[i];
                    first = false;
                }
            }
            cout << '\n';
        }
    }
}

int main(){
    executaAplicacao();
    return 0;
}
