#include "ICR.h"
#include <sstream>

void ICR::cargarInstruccion(string inst)
{
    instruccionCompleta = inst;

    stringstream ss(inst);
    string nombre;

    ss >> nombre;

    if (nombre == "SET")
    {
        tipo = SET;
    }
    else if (nombre == "LDR")
    {
        tipo = LDR;
    }
    else if (nombre == "ADD")
    {
        tipo = ADD;
    }
    else if (nombre == "INC")
    {
        tipo = INC;
    }
    else if (nombre == "DEC")
    {
        tipo = DEC;
    }
    else if (nombre == "STR")
    {
        tipo = STR;
    }
    else if (nombre == "SHW")
    {
        tipo = SHW;
    }
    else if (nombre == "PAUSE")
    {
        tipo = PAUSE;
    }
    else if (nombre == "END")
    {
        tipo = END;
    }
    else
    {
        tipo = NONE;
    }
}

TipoInstruccion ICR::obtenerTipo()
{
    return tipo;
}