#include <iostream>
#include <stdexcept>

using namespace std;

int main(){
    for(int i = 0; i < 4; i++){
        try{
            string tentativaSenha;
            string senha = "titilindo";

            cout << "Digite a senha, voce tem "<< 4 - i << " tentativa(s): ";
            cin >> tentativaSenha;
            if (tentativaSenha != senha){
                throw invalid_argument("Senha errada!");
            }else{
                cout << "Bem vindo!";
                break;
            }
        }
        catch(const invalid_argument& e){
            cout << "Erro: " << e.what() << endl;
        }
    }
    return 0;
}