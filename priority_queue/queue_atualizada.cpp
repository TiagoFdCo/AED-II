#include <iostream>
#include <list>

using namespace std;

template <typename T>
class Queue {
private:
    list<T> qlist; // lista duplamente encadeada
    int num_itens;

public:
    // construtor
    Queue() : num_itens(0) {}

    // destrutor (não precisa de delete, pois list se limpa sozinha)
    ~Queue() = default;

    void enqueue(T item);  // adiciona um item 
    void dequeue();        // retira um item
    T front();             // retorna o item na frente da fila
    int size();            // retorna o tamanho da fila
    bool empty();          // verifica se a fila está vazia
};

template<typename T>
void Queue<T>::enqueue(T item) {
    qlist.push_back(item);
    num_itens++;
}

template<typename T>
void Queue<T>::dequeue() {
    if (!qlist.empty()) {
        qlist.pop_front();
        num_itens--;
    }
}

template<typename T>
T Queue<T>::front() {
    if (!qlist.empty()) {
        return qlist.front();
    }
    throw runtime_error("Fila vazia!");
}

template<typename T>
int Queue<T>::size() {
    return num_itens;
}

template<typename T>
bool Queue<T>::empty() {
    return num_itens == 0;
}

int main() {
    return 0;
}
