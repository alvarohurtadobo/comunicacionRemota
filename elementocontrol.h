#ifndef ELEMENTOCONTROL_H
#define ELEMENTOCONTROL_H


#include <actuador.h>
#include <medidor.h>

class ElementoControl
{
public:
    ElementoControl();
    void cortarSuministro();
    void establecerSuministro();
    Medidor accederMedidor();

private:
    Actuador miContactor;
    Medidor miMedidor;

    bool energizado;
    bool estadoFuncionalidad;
    int codigo;
};

#endif // ELEMENTOCONTROL_H
