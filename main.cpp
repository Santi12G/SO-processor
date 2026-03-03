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

int main()
{
    // ===== Crear componentes del procesador =====
    pc contadorPrograma;
    ICR ir;
    ALU alu;
    Acumulador acc;
    mar registroMAR;
    mdr registroMDR;
    Memoria memoria;
    UnidadControl uc;

    // ===== Leer archivo =====
    ifstream archivo("programa.txt");

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

    // ===== Ciclo FETCH - DECODE - EXECUTE =====
    while (uc.estaActiva())
    {
        int pcActual = contadorPrograma.enviarDir();

        if (pcActual >= instrucciones.size())
            break;

        string instruccion = instrucciones[pcActual];

        // ===== DECODE =====
        ir.cargarInstruccion(instruccion);

        // ===== Caso especial: SET =====
        if (ir.obtenerTipo() == SET)
        {
            string op, direccionStr, valorStr;
            stringstream ss(instruccion);

            ss >> op >> direccionStr >> valorStr;

            int direccion = stoi(direccionStr.substr(1));
            memoria.escribirDato(direccion, valorStr);

            contadorPrograma.aumentar();
            continue;
        }

        // ===== EXECUTE (resto instrucciones) =====
        uc.ejecutarInstruccion(
            ir,
            alu,
            acc,
            registroMAR,
            registroMDR,
            memoria,
            contadorPrograma);
    }

    cout << "Programa finalizado." << endl;

    return 0;
}
