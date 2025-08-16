#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<string> fila = {};
    string passageiros;

    cout << "Digite o nome do passageiro que deseja adicionar: " << endl;

    do{
        getline (cin, passageiros);
        fila.push_back(passageiros);
        
        cout << "Digite o nome do proximo passageiro (Digite fim para encerrar)" << endl;

    }while(passageiros != "fim");

    cout << "Meu deus do ceu!! O terceiro passageiro foi ejetado da fila!!!!!!!!!!"<< endl;

    fila.erase(fila.begin() + 2);

    fila.pop_back();

    cout << "Os passageiros da fila sao: " << endl << endl;
    for (int i = 0; i < fila.size(); i++){
        cout << fila[i] << endl;
    }
    return 0;
}