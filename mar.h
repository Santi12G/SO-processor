#ifndef MAR_H
#define MAR_H

#include <string>

using namespace std;

class mar
{
private:
    string direccion;

public:
    void cargarDireccion(string nuevaDir);
    string obtenerDireccion();
};

#endif