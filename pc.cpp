#include "pc.h"

pc::pc()
{
    direccion = 0;
}

void pc::aumentar()
{
    direccion++;
}

int pc::enviarDir()
{
    return direccion;
}