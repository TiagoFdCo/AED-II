#include <iostream>
#include <list>
#include <string>

using namespace std;

int main(){
    list<string> filaHospital;

    string paciente;

    cout << "Registre o paciente : " << endl;

    do{
        getline (cin, paciente);
        filaHospital.push_back(paciente);
        
        cout << "Registre o proximo paciente (Digite fim para encerrar)" << endl << endl;

    }while(paciente != "fim");

    filaHospital.pop_back(); // retira a string "fim"

    cout << "Chamando o primeiro paciente" << endl;
    filaHospital.pop_front();

    cout << "Registre o paciente com urgencia!: " << endl;
    getline(cin, paciente);
    filaHospital.push_back(paciente);

    cout << "Os pacientes registrados, foram: " << endl;
    for (list<string>::iterator it = filaHospital.begin(); it != filaHospital.end(); ++it){
        cout << *it << endl;
    }
    return 0;
}