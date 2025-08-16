#include <iostream>
#include <vector>

using namespace std;

int main(){

    vector<double> temperaturas;
    double temperatura;

    string confirmacao;

    double media; 
    double cont;

    cout << "Digite as temperaturas e calcularei a media, a maior e a menor temperatura" << endl;

    do{
        cout << "Digite a temperatura: " << endl;
        cin >> temperatura;
        temperaturas.push_back(temperatura);
        cont += temperatura;
        
        cout << "Deseja adicionar mais uma temperatura? (S/N): ";
        cin >> confirmacao;
        if (confirmacao == "S" || confirmacao == "s"){
            continue;
        }else{
            break;
        }
    }while (true);

    int n = temperaturas.size();

    //Bubble Sort
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - 1 ; j ++){
            if (temperaturas[i] > temperaturas[j + 1]){
                int temp = temperaturas[j];
                temperaturas[j] = temperaturas[j + 1];
                temperaturas[j + 1] = temp;
            }
        }
    }

    //Saida

    media = cont / n;
    cout << "media: " << media << endl;
    cout << "temperatura mais baixa: " << temperaturas[0] << endl;
    cout << "tempertura mais alta: " << temperaturas[n-1];
    return 0;
}