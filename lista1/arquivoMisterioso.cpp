#include <iostream>

using namespace std;

int main(){
    cout << "Digite o nome do arquivo que deseja buscar" << endl;

    try{
        string arquivo1 = "IoT_python.py";
        string arquivo2 = "gemeos_digitais.c";

        string busca;

        cin >> busca;
        if(busca != arquivo1 && busca != arquivo2){
            throw runtime_error("Arquivo nao existente!");
        }
        cout << busca << endl;
    }

    catch(const runtime_error& e){
        cout << "Erro: " << e.what() << endl;
    }
    return 0;
}