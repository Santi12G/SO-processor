#include "UnidadControl.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

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
        string nombre, op1, valor, null1, null2;
        stringstream ss(ir.obtenerInstruccion());

        ss >> nombre >> op1 >> valor >> null1 >> null2;

        int direccion = stoi(op1.substr(1));

        memoria.escribirDato(direccion, valor);

        break;
    }
    case LDR:
    {
        // Extraer dirección (ej: D5 → 5)
        string op;
        stringstream ss(ir.obtenerInstruccion());
        ss >> op >> op;

        string direccion = op;

        registroMAR.cargarDireccion(direccion);

        string dato = memoria.devolverDato(stoi(direccion.substr(1)));
        registroMDR.cargarDato(dato);

        acc.almacenarDato(stoi(dato));
        break;
    }

    case ADD:
    {
        string instruccion = ir.obtenerInstruccion();
        stringstream ss(instruccion);

        string nombre, op1, op2, op3;

        ss >> nombre >> op1 >> op2 >> op3;

        // Convertir direcciones (D1 → 1)
        auto extraerDir = [](string op)
        {
            return stoi(op.substr(1));
        };

        // ---- ADD D1 ----
        if (op1 != "NULL" && op2 == "NULL")
        {
            int dir1 = extraerDir(op1);
            int valor1 = stoi(memoria.devolverDato(dir1));

            int resultado = alu.sumar(acc.devolverDato(), valor1);
            acc.almacenarDato(resultado);
        }

        // ---- ADD D1 D3 ----
        else if (op1 != "NULL" && op2 != "NULL" && op3 == "NULL")
        {
            int dir1 = extraerDir(op1);
            int dir2 = extraerDir(op2);

            int valor1 = stoi(memoria.devolverDato(dir1));
            int valor2 = stoi(memoria.devolverDato(dir2));

            int resultado = alu.sumar(valor1, valor2);
            acc.almacenarDato(resultado);
        }

        // ---- ADD D1 D3 D4 ----
        else if (op1 != "NULL" && op2 != "NULL" && op3 != "NULL")
        {
            int dir1 = extraerDir(op1);
            int dir2 = extraerDir(op2);
            int dir3 = extraerDir(op3);

            int valor1 = stoi(memoria.devolverDato(dir1));
            int valor2 = stoi(memoria.devolverDato(dir2));

            string resultado = to_string(alu.sumar(valor1, valor2));

            memoria.escribirDato(dir3, resultado);
        }

        break;
    }

    case INC:
    {
        string op;
        stringstream ss(ir.obtenerInstruccion());
        ss >> op >> op;

        int direccion = stoi(op.substr(1));
        int valor = stoi(memoria.devolverDato(direccion));

        int resultado = alu.incrementar(valor);
        memoria.escribirDato(direccion, to_string(resultado));
        break;
    }

    case DEC:
    {
        string op;
        stringstream ss(ir.obtenerInstruccion());
        ss >> op >> op;

        int direccion = stoi(op.substr(1));
        int valor = stoi(memoria.devolverDato(direccion));

        int resultado = alu.decrementar(valor);
        memoria.escribirDato(direccion, to_string(resultado));
        break;
    }

    case STR:
    {
        string op;
        stringstream ss(ir.obtenerInstruccion());
        ss >> op >> op;

        int direccion = stoi(op.substr(1));
        memoria.escribirDato(direccion, to_string(acc.devolverDato()));
        break;
    }

    case SHW:
    {
        string dummy, token;
        stringstream ss(ir.obtenerInstruccion());
        ss >> dummy >> token; // dummy == "SHW", token == target

        if (token == "ACC")
        {
            cout << acc.devolverDato() << endl;
        }
        else if (token == "ICR")
        {
            cout << ir.obtenerInstruccion() << endl;
        }
        else if (token == "MAR")
        {
            cout << registroMAR.obtenerDireccion() << endl;
        }
        else if (token == "MDR")
        {
            cout << registroMDR.obtenerDato() << endl;
        }
        else if (token == "UC")
        {
            cout << (estaActiva() ? "ACTIVA" : "DETENIDA") << endl;
        }
        else
        {
            // Expecting memory location like D5
            if (token.size() > 1 && token[0] == 'D' &&
                std::all_of(token.begin() + 1, token.end(), [](unsigned char c) { return std::isdigit(c); }))
            {
                int direccion = stoi(token.substr(1));
                cout << memoria.devolverDato(direccion) << endl;
            }
            else
            {
                // Unknown token: print as-is to avoid crash
                cout << token << endl;
            }
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

    contadorPrograma.aumentar();
}