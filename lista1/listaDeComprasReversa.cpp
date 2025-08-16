#include <iostream>
#include <string>
#include <list>

using namespace std;

int main(){
    list<string> lista;

    string item;
    list<string>::reverse_iterator it;

    cout << "Digite o item que deseja adicionar: " << endl;

    do{
        getline (cin, item);
        lista.push_back(item);
        
        cout << "Digite o proximo item (Digite fim para encerrar)" << endl << endl;

    }while(item != "fim");

    lista.pop_back(); // retira a string "fim"

    cout << "Exibindo os itens em ordem inversa:" << endl;

    for (it = lista.rbegin(); it != lista.rend(); ++it){
        cout << *it << endl;
    }

    return 0;
}