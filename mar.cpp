#include "mar.h"

void mar::cargarDireccion(int nuevaDir)
{
    this->direccion = nuevaDir;
}

int mar::obtenerDireccion()
{
    return this->direccion;
}
