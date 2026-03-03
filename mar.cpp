#include "mar.h"

void mar::cargarDireccion(string nuevaDir)
{
    this->direccion = nuevaDir;
}

string mar::obtenerDireccion()
{
    return direccion;
}
