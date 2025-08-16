#include <iostream>

using namespace std;

int main(){
    cout << "Digite dois numeros e eu farei a divisao deles:" << endl;
    try{
        float num1;
        float num2;
    
        cin >> num1;
        cin >> num2;

        if(num2 == 0){
            throw runtime_error("Divisao por zero!!");
        }
        cout << num1 / num2 << endl;
    }

    catch(const runtime_error& e){
        cout << "Erro: " <<e.what() << endl;
    }
    return 0;
}