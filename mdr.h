#ifndef MDR_H
#define MDR_H

#include <iostream>
#include <string>

using namespace std;

class mdr
{
private:
    string data;

public:
    void cargarDato(string nuevoDato);
    string obtenerDato();
};

#endif