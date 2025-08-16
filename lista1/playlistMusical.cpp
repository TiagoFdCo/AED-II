#include <iostream>
#include <string>
#include <list>

using namespace std;

int main(){
    list<string> playlist;

    string musica;

    cout << "Digite a musica que deseja adicionar: " << endl;

    do{
        getline (cin, musica);
        playlist.push_back(musica);
        
        cout << "Digite a proxima musica (Digite fim para encerrar)" << endl << endl;

    }while(musica != "fim");

    playlist.pop_back(); // retira a string "fim"

    cout << "Voce removeu a primeira musica" << endl;
    playlist.pop_front();

    cout << "Adicione outra musica: " << endl;
    getline(cin, musica);
    playlist.push_back(musica);

    cout << "As musicas adicionadas, foram: " << endl;
    for (list<string>::iterator it = playlist.begin(); it != playlist.end(); ++it){
        cout << *it << endl;
    }
    return 0;
}