#include "MEMORIA.h"
#include <sstream>

Memoria::Memoria()
{

    for (int i = 0; i < 200; i++)
        datos[i] = 0;
}

string Memoria::devolverDato(int direccion)
{
    // Validación básica de rango
    if (direccion < 0 || direccion >= 200)
        return "0";

    return to_string(datos[direccion]);
}

string Memoria::escribirDato(int direccion, string dato)
{
    // Validación básica de rango
    if (direccion < 0 || direccion >= 200)
        return "ERROR";

    // Convertir string a int
    datos[direccion] = stoi(dato);

    return "OK";
}