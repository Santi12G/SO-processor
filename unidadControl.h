#ifndef UNIDAD_CONTROL_H
#define UNIDAD_CONTROL_H

#include "ICR.h"
#include "ALU.h"
#include "ACUMULADOR.h"
#include "MAR.h"
#include "MDR.h"
#include "MEMORIA.h"
#include "pc.h"

class UnidadControl
{
private:
    bool ejecutando;

public:
    UnidadControl();

    bool estaActiva();
    void detener();

    void ejecutarInstruccion(
        ICR &ir,
        ALU &alu,
        Acumulador &acc,
        mar &registroMAR,
        mdr &registroMDR,
        Memoria &memoria,
        pc &contadorPrograma);
};

#endif