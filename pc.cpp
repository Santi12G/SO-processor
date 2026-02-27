#include "pc.h"

void pc::aumentar()
{
    this->direccion++;
}

int pc::enviarDir()
{
    return this->direccion;
};