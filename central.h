#ifndef CENTRAL_H
#define CENTRAL_H

#include <guimodulo.h>

class Central
{
public:
    Central();
    ~Central();
    GUImodulo * accederModulo();
    void enviarMensajeSolicitudDatos();

private slots:
    void anteRecepcionMensaje();

private:
    GUImodulo * moduloCentral;

};

#endif // CENTRAL_H
