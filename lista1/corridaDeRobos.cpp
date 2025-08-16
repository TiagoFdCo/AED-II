#include <iostream>
#include <string>
#include <list>

using namespace std;

int main(){
    list<string> robos = {"robo1", "robo2", "robo3"};
    list<string>::iterator it;

    it = robos.begin();
    ++it;
    
    robos.insert(it, "robo4");

    return 0;
}