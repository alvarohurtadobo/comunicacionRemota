#ifndef SUBSISTEMA_H
#define SUBSISTEMA_H

#include <centralizador.h>

class Subsistema
{
public:
    Subsistema();
    Centralizador * accederControlador(int codigo);

private:

    Centralizador * misControladores[100];
    int numeroCentralizadores;
};

#endif // SUBSISTEMA_H
