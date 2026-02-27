#ifndef MAR_H
#define MAR_H

#include <string>

using namespace std;

class mar
{
private:
    int direccion;

public:
    void cargarDireccion(int nuevaDir);
    int obtenerDireccion();
};

#endif