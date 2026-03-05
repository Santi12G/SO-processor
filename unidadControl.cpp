#include "UnidadControl.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

UnidadControl::UnidadControl()
{
    ejecutando = true;
}

bool UnidadControl::estaActiva()
{
    return ejecutando;
}

void UnidadControl::detener()
{
    ejecutando = false;
}

void UnidadControl::ejecutarInstruccion(
    ICR &ir,
    ALU &alu,
    Acumulador &acc,
    mar &registroMAR,
    mdr &registroMDR,
    Memoria &memoria,
    pc &contadorPrograma)
{
    TipoInstruccion tipo = ir.obtenerTipo();

    switch (tipo)
    {

    case SET:
    {
        string nombre, op1, valor;
        stringstream ss(ir.obtenerInstruccion());

        ss >> nombre >> op1 >> valor;

        int direccion = stoi(op1.substr(1));

        registroMAR.cargarDireccion(op1);
        registroMDR.cargarDato(valor);

        memoria.escribirDato(direccion, valor);

        break;
    }

    case LDR:
    {
        string nombre, op;
        stringstream ss(ir.obtenerInstruccion());

        ss >> nombre >> op;

        int direccion = stoi(op.substr(1));

        registroMAR.cargarDireccion(op);

        string dato = memoria.devolverDato(direccion);
        registroMDR.cargarDato(dato);

        acc.almacenarDato(stoi(dato));

        break;
    }

    case ADD:
    {
        string nombre, op1, op2, op3;
        stringstream ss(ir.obtenerInstruccion());

        ss >> nombre >> op1 >> op2 >> op3;

        auto dir = [](string op)
        { return stoi(op.substr(1)); };

        // ADD D1
        if (op1 != "NULL" && op2 == "NULL")
        {
            int valor = stoi(memoria.devolverDato(dir(op1)));

            int resultado = alu.sumar(acc.devolverDato(), valor);

            acc.almacenarDato(resultado);
        }

        // ADD D1 D2
        else if (op1 != "NULL" && op2 != "NULL" && op3 == "NULL")
        {
            int v1 = stoi(memoria.devolverDato(dir(op1)));
            int v2 = stoi(memoria.devolverDato(dir(op2)));

            int resultado = alu.sumar(v1, v2);

            acc.almacenarDato(resultado);
        }

        // ADD D1 D2 D3
        else if (op1 != "NULL" && op2 != "NULL" && op3 != "NULL")
        {
            int v1 = stoi(memoria.devolverDato(dir(op1)));
            int v2 = stoi(memoria.devolverDato(dir(op2)));

            int resultado = alu.sumar(v1, v2);

            // resultado también queda en el acumulador
            acc.almacenarDato(resultado);

            registroMAR.cargarDireccion(op3);
            registroMDR.cargarDato(to_string(resultado));

            memoria.escribirDato(dir(op3), registroMDR.obtenerDato());
        }

        break;
    }

    case INC:
    {
        string nombre, op;
        stringstream ss(ir.obtenerInstruccion());
        ss >> nombre >> op;

        int direccion = stoi(op.substr(1));

        registroMAR.cargarDireccion(op);

        string dato = memoria.devolverDato(direccion);
        registroMDR.cargarDato(dato);

        acc.almacenarDato(stoi(dato));

        int resultado = alu.incrementar(acc.devolverDato());
        acc.almacenarDato(resultado);

        registroMDR.cargarDato(to_string(resultado));

        memoria.escribirDato(direccion, registroMDR.obtenerDato());

        break;
    }

    case DEC:
    {
        string nombre, op;
        stringstream ss(ir.obtenerInstruccion());
        ss >> nombre >> op;

        int direccion = stoi(op.substr(1));

        registroMAR.cargarDireccion(op);

        string dato = memoria.devolverDato(direccion);
        registroMDR.cargarDato(dato);

        acc.almacenarDato(stoi(dato));

        int resultado = alu.decrementar(acc.devolverDato());
        acc.almacenarDato(resultado);

        registroMDR.cargarDato(to_string(resultado));

        memoria.escribirDato(direccion, registroMDR.obtenerDato());

        break;
    }

    case STR:
    {
        string nombre, op;
        stringstream ss(ir.obtenerInstruccion());

        ss >> nombre >> op;

        int direccion = stoi(op.substr(1));

        registroMAR.cargarDireccion(op);
        registroMDR.cargarDato(to_string(acc.devolverDato()));

        memoria.escribirDato(direccion, registroMDR.obtenerDato());

        break;
    }

    case SHW:
    {
        string dummy, token;
        stringstream ss(ir.obtenerInstruccion());

        ss >> dummy >> token;

        if (token == "ACC")
            cout << acc.devolverDato() << endl;

        else if (token == "ICR")
        {
            cout << ir.obtenerInstruccionAnterior() << endl;
        }

        else if (token == "MAR")
            cout << registroMAR.obtenerDireccion() << endl;

        else if (token == "MDR")
            cout << registroMDR.obtenerDato() << endl;

        else if (token == "UC")
            cout << (estaActiva() ? "ACTIVA" : "DETENIDA") << endl;

        else if (token[0] == 'D')
        {
            int direccion = stoi(token.substr(1));

            // MAR ← dirección
            registroMAR.cargarDireccion(token);

            // MDR ← Mem[MAR]
            string dato = memoria.devolverDato(direccion);
            registroMDR.cargarDato(dato);

            // mostrar dato
            cout << registroMDR.obtenerDato() << endl;
        }

        break;
    }

    case PAUSE:
    {
        cout << "Procesador en pausa. Presione ENTER para continuar...";
        cin.get();
        break;
    }

    case END:
        detener();
        break;

    default:
        break;
    }
}