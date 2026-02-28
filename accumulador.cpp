#include "ACUMULADOR.h"

void Acumulador::almacenarDato(int nuevoDato)
{
    this->dato = nuevoDato;
}

int Acumulador::devolverDato()
{
    return this->dato;
}