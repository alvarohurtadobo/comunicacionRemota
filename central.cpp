#include "central.h"

Central::Central()
{
    moduloCentral = new GUImodulo;
    //connect(moduloCentral,SIGNAL(recibiMensaje()),this,SLOT(anteRecepcionMensaje()));
}

Central::~Central()
{
    delete moduloCentral;
}

GUImodulo * Central::accederModulo() // NO PUEDES PASAR EL OBJETO!!!
{
    return moduloCentral;
}

void Central::enviarMensajeSolicitudDatos()
{
    //moduloCentral;
}

void Central::anteRecepcionMensaje()
{
    /*Ante la llegada de un mensaje del módulo la central verifica que se recibio un mensaje de texto*/
    // moduloCentral->
}
