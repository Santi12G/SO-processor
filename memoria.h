#ifndef MEMORIA_H
#define MEMORIA_H

#include <string>

using namespace std;

class Memoria
{
private:
    int datos[200];

public:
    Memoria();
    string devolverDato(int direccion);
    string escribirDato(int direccion, string dato);
};

#endif