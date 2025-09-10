#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <limits>


using namespace std;

//ESTRUTURAS DE DADOS E BUSCA--------------------------------------------------------------------------------------------------
//Implementacao de apelidos usando "using"
using uint = unsigned int;
using Vertex = unsigned int;

//Implementacao do infinito e NIL
constexpr int INF = numeric_limits<int>::infinity();
constexpr Vertex NIL = numeric_limits<Vertex>::max(); 

//Implementacao da classe Queue

template <typename T>
class Queue{
private:
    T item;
    list<T> *qlist; //lista duplamente encadeada dinamica
    int num_itens;

public:

    //construtores
    Queue(): item(0), num_itens(0){
        qlist = new list<T> [item]; // inicializo a lista nova 
    }

    //destrutor
    ~Queue(){
        delete[] qlist;
        qlist = nullptr;
    }
    void enqueue(T item); //adiciona um item 
    void dequeue(); //retira um item
    T front(); //retorna o item na frente da fila
    int size(); //retorna o tamanho da fila
    bool empty(); //verifica de a fila está vazia (true ou false)
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

//Para a classe BFS
enum class Color{
    WHITE,
    GRAY,
    BLACK
};

//Implementacao da classe BFS
class BFS{
private:
    GraphAL& graph;
    vector<int> distance; //distancia
    vector<Color> color; //rotulo do vertice
    vector<Vertex> parent; //predecessor
    vector<Vertex> order; //ordem de busca

public:
    //construtores
    BFS(GraphAL& g):
    graph(g),
    distance(g.get_num_vertices(), INF),
    color(g.get_num_vertices(), Color::WHITE),
    parent(g.get_num_vertices(), NIL){}

    //metodos publicos
    void runBFS(const Vertex& s);
    int getDistance(const Vertex& v);
    Color getColor(const Vertex& v);
    Vertex getParent(const Vertex& v);
    vector<Vertex> getOrder() const;
    void printBFS();
};

void BFS::runBFS(const Vertex& s){
    //inicializacao dos vector feitas no constutor, agora a inicializacao do source
    color[s] = Color::GRAY; //inicializa o source como "a explorar"
    distance[s] = 0; //s esta a distancia 0 se si mesmo
    parent[s] = NIL; //s nao tem predecessores

    Queue<Vertex> q;
    q.enqueue(s); //enfileira o source para analise de seus adjacentes
    
    while (!q.empty())
    {
       Vertex u = q.front(); //pega o elemento da frente
       q.dequeue(); //desenfileira o elemento
       for (Vertex v : graph.get_adj(u)){ //pra cada vertice v dentro da lista de adjacencia u desse vertice
            if(color[v] == Color::WHITE){ 
                color[v] = Color::GRAY; //muda a cor pra CINZA
                distance[v] = distance[u] + 1; //aumenta a distancia do vertice adjacente em 1
                parent[v] = u; //coloca u, que o vertice enfileirado, como antecessor dos vertices consultados
                order.push_back(v); //registra a ordem
                q.enqueue(v);
            }
       }
       color[u] = Color::BLACK; //muda a cor do vertice na fila para preto
    }
    
}

int BFS::getDistance(const Vertex& v){
    return distance[v];
}

Color BFS::getColor(const Vertex& v){
    return color[v];
}

Vertex BFS::getParent(const Vertex& v){
    return parent[v];
}

vector<Vertex> BFS::getOrder() const{
    return order;
}

void BFS::printBFS(){
    cout << "distancia do vertice s ate os outros: " << endl;
    for(size_t v = 0; v < distance.size(); v++){
        if(distance[v] == INF)
            cout << v << ": INF (inalcancavel)\n";
        else
            cout << v << ": " << distance[v] << endl;
    }

    cout << "\nPais (arvore de BFS):\n";
    for(size_t v = 0; v < parent.size(); v++){
        if(parent[v] != NIL)
            cout << parent[v] << " -> " << v << endl;
    }

    cout << "\nOrdem de visita:\n";
    for(Vertex v : order){
        cout << v << " ";
    }
    cout << endl;
}

void fillBFS(GraphAL g){
    Vertex s;

    cout << "Digite o vertice de origem para a BFS" << endl;
    cin >> s; //recebe o vertice de origem

    BFS bfs(g);
    bfs.runBFS(s);
    bfs.printBFS();
}
//-----------------------------------------------------------------------------------------------------------------------------
//TABULEIRO--------------------------------------------------------------------------------------------------------------------

class Chessboard{
private:
    GraphAL graph;
public:
    //construtor
    Chessboard(): graph(64){
        createChessboard();
    }

    //metodos
    void createChessboard();
    GraphAL& getGraph();

    string posicaoParaNotacao(int x, int y);
    pair<int, int> notacaoParaPosicao(const string& s);

    vector<string> getHorseMoves(const string& pos);

    int notacaoParaIndice(const string& s);
    string indiceParaNotacao(int idx);
};

void Chessboard::createChessboard(){
    uint qtd_vertices = 64;

    GraphAL g(qtd_vertices);

    //movimentos do cavalo
    int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
    int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};

    for (int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            int u = x * 8 + y;
            for(int k = 0; k < 8; k++){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8){
                    int v = nx * 8 + ny;
                    graph.add_edge(u, v);
                }
            }
        }
    }
    
    graph.print_adjacency_list(graph); //so pra teste
}

GraphAL& Chessboard::getGraph(){
    return graph;
}

string Chessboard::posicaoParaNotacao(int x, int y){
    return string(1, 'a' + y) + string(1, '1' + x);
}

pair<int, int> Chessboard::notacaoParaPosicao(const string& s){
    return {s[1] - '1', s[0] - 'a'};
}

vector<string> Chessboard::getHorseMoves(const string& pos){
    auto [x, y] = notacaoParaPosicao(pos);
    vector<string> moves;
    int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
    int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};

    for(int k = 0; k < 8; k++){
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8){
            moves.push_back(posicaoParaNotacao(nx, ny));
        }
    }
    return moves;
}

int Chessboard::notacaoParaIndice(const string& s){
    auto [x, y] = notacaoParaPosicao(s);
    return x*8 + y;
}

string Chessboard::indiceParaNotacao(int idx){
    int x = idx / 8;
    int y = idx % 8;
    return posicaoParaNotacao(x, y);
}

void executaAplicacao(){
    Chessboard board;

    string inicio, fim;
//terminar esse negocio aqui
}

//MAIN-----------------------------------------------------------------------------------------------------------------------------
int main(){
    Chessboard board;


    return 0;
}