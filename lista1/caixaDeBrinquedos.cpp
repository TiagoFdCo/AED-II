#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    vector<string> caixa = {};
    string brinquedo;

    cout << "Digite o brinquedo que deseja adicionar: " << endl;

    do{
        getline (cin, brinquedo);
        caixa.push_back(brinquedo);
        
        cout << "Digite outro brinquedo (Digite fim para encerrar)" << endl;

    }while(brinquedo != "fim");

    caixa.pop_back();

    cout << "Os brinquedos adicionados, foram: " << endl;
    for (int i = 0; i < caixa.size(); i++){
        cout << caixa[i] << endl;
    }
    return 0;
}