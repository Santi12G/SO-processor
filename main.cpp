#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "pc.h"
#include "ICR.h"
#include "ALU.h"
#include "ACUMULADOR.h"
#include "MAR.h"
#include "MDR.h"
#include "MEMORIA.h"
#include "unidadControl.h"

using namespace std;

int main(int argc, char *argv[])
{
    pc contadorPrograma;
    ICR ir;
    ALU alu;
    Acumulador acc;
    mar registroMAR;
    mdr registroMDR;
    Memoria memoria;
    UnidadControl uc;

    if (argc < 2)
    {
        cout << "Uso: Procesador <archivo.txt>" << endl;
        return 1;
    }

    ifstream archivo(argv[1]);

    if (!archivo)
    {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    vector<string> instrucciones;
    string linea;

    while (getline(archivo, linea))
    {
        if (!linea.empty())
            instrucciones.push_back(linea);
    }

    archivo.close();

    // ===== FETCH INICIAL =====
    int pcActual = contadorPrograma.enviarDir();

    string direccion = "D" + to_string(pcActual);
    registroMAR.cargarDireccion(direccion);

    string instruccion = instrucciones[pcActual];
    registroMDR.cargarDato(instruccion);

    ir.cargarInstruccion(instruccion);

    while (uc.estaActiva())
    {
        // ===== EXECUTE =====
        uc.ejecutarInstruccion(
            ir,
            alu,
            acc,
            registroMAR,
            registroMDR,
            memoria,
            contadorPrograma);

        // ===== NEXT INSTRUCTION =====
        contadorPrograma.aumentar();

        int pcActual = contadorPrograma.enviarDir();

        if (pcActual >= instrucciones.size())
            break;

        // MAR ← PC
        string direccion = "D" + to_string(pcActual);
        registroMAR.cargarDireccion(direccion);

        // ===== FETCH =====
        string instruccion = instrucciones[pcActual];

        registroMDR.cargarDato(instruccion);

        ir.cargarInstruccion(instruccion);
    }

    cout << "Programa finalizado." << endl;

    return 0;
}