#ifndef SISTEMAFISICO_H
#define SISTEMAFISICO_H

#include <subsistema.h>


class SistemaFisico
{
public:
    SistemaFisico();
    Subsistema* accederSubSustema(int code);


private:

    Subsistema* misSubsistemas[100];
};

#endif // SISTEMAFISICO_H
