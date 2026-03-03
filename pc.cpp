#include "pc.h"

pc::pc()
{
    direccion = 0;
}

void pc::aumentar()
{
    this->direccion++;
}

int pc::enviarDir()
{
    return this->direccion;
};