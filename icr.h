#ifndef ICR_H
#define ICR_H

#include <string>
using namespace std;

enum TipoInstruccion
{
    SET,
    LDR,
    ADD,
    INC,
    DEC,
    STR,
    SHW,
    PAUSE,
    END,
    NONE
};

class IR
{
private:
    string instruccionCompleta;
    TipoInstruccion tipo;

public:
    void cargarInstruccion(string inst);
    TipoInstruccion obtenerTipo();
};

#endif