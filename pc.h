#ifndef PC_H
#define PC_H

using namespace std;

class pc
{
private:
    int direccion;

public:
    pc();
    void aumentar();
    int enviarDir();
};

#endif