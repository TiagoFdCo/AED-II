#include <iostream>
#include <list>
#include <vector>
#include <iterator>

using namespace std;

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

int main(){
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(7);
    q.enqueue(8);

    cout << q.front() << endl;

    q.dequeue();

    cout << q.front() << endl;

    return 0;
}