#include <iostream>
#include <stdexcept>

using namespace std;

int main(){
    float cofrinho = 0;
    float valor;
    string confirmacao;

    cout << "Adicione uma quantia ao cofrinho" <<endl;
    try{
        do{
            cin >> valor;
            if(valor < 0){
                throw runtime_error("Valor negativo!");
            }
            cofrinho += valor;
            cout << "Deseja adicionar mais um valor? (S/N)" <<endl;
            cin >> confirmacao;
            if (confirmacao == "S" || confirmacao == "s"){
                continue;
            }else{
                break;
            }
        }while (true);
        cout << "O confrinho tem R$" << cofrinho << "reais guardados" << endl;
    }

    catch(const runtime_error& e){
        cout << "Erro: " <<e.what() << endl;
    }
    
    return 0;
}