#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> lista;
    int numero;
    vector<int> listaDuplicada;

    cout << "Digite 5 numeros inteiros e eu os exibirei duplicados!"<< endl;

    for (int i = 0; i < 5; i++){
        cin >> numero;
        lista.push_back(numero);
    }

    for (int j = 0; j < lista.size(); j++){
        listaDuplicada.push_back(lista[j] * 2);
    }

    cout << "Aqui estao as duas listas de numeros: " << endl;

    cout << "[";

    for (int k = 0; k < lista.size(); k++){
        cout << lista[k];

        if (k < lista.size() - 1){
            cout << ", ";
        }
    }
    cout << "]"<< endl;

    cout << "[";

    for (int a = 0; a < listaDuplicada.size(); a++){
        cout << listaDuplicada[a];

        if (a < listaDuplicada.size() - 1){
            cout << ", ";
        }
    }
    cout << "]"<< endl;
    return 0;
}