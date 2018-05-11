#ifndef CENTRALIZADOR_H
#define CENTRALIZADOR_H

#include <elementocontrol.h>

class Centralizador
{
public:
    Centralizador();

    ElementoControl * accederElemento(int puerto);
    void activarElemento(int puerto);
    void desactivarElemento(int puerto);

private:
    ElementoControl misElementosControl;
    int codigo;
    string nombre;
    bool estado;
    string descripcion;
    int numeroElementos;
};

#endif // CENTRALIZADOR_H
