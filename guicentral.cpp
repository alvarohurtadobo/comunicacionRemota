#include "guicentral.h"

GUICentral::GUICentral(QWidget *parent) :
    QDialog(parent)
{
    actualizar = false;
    inicioMensaje = 0;

    numeroSubSistemas[0]="76138856";

    estadoActual = 0;
    numeroAccionAutomata = 0;
}

void GUICentral::inicializarModulo(QString port)
{
    moduloCentral = new GUImodulo(port);
    connect(moduloCentral,SIGNAL(recibiMensaje()),this,SLOT(anteRecepcionMensaje()));
}

GUICentral::~GUICentral()
{
    delete moduloCentral;
}

GUImodulo * GUICentral::accederModulo() // NO PUEDES PASAR EL OBJETO!!!
{
    return moduloCentral;
}

int GUICentral::actualizarEstado(int estadoActual, int evento)
{
    return transiciones[estadoActual][evento];
}

QByteArray GUICentral::agenda(int place)
{
    return numeroSubSistemas[place];
}

void GUICentral::anteRecepcionMensaje()
{
    numeroAuxiliar.clear();                                 // Se vacia el adjuntador de digitos
    mensajeActual = moduloCentral->getUltimoMensaje();      // Se toma el mensaje que causo la interrupción y almacena para su análisis
    //moduloCentral->setWindowTitle(mensajeActual);
                                   // = 0 , Se inicializa el automata

    // verificaci{on ante llegada de notificaci{on de corte
    if(mensajeActual.count('#')>=10)
        emit informeCorte();

    //Verificaci{on ante llegada de comando de atención:
    if((mensajeActual.count('O')==1)&&(mensajeActual.count('K')==1))
        emit moduloDespierto();

    numeroMensajeALeer.clear();
    //if(estadoActual == 0)
    if(true)
    {
        for(int i = 0; i<mensajeActual.size();i++){
            numeroAccionAutomata = matrizDeteccionLugar[numeroAccionAutomata][mensajeActual.at(i)%8];
            accionAutomata(numeroAccionAutomata,mensajeActual.at(i));
        }
        if(numeroAccionAutomata==5)
        {
            moduloCentral->setWindowTitle("Recibio mensaje: "+numeroMensajeALeer);
            estadoActual = 1;                       // Se activa este estado en el que se emite la señal de recepcion de mensaje
            moduloCentral->leerMensaje(numeroMensajeALeer);
        }
        numeroAccionAutomata = 0;
    }
    else
    {
        if(estadoActual == 1)
        {
            moduloCentral->setWindowTitle("Detectando simbolo:");
            int comienzo = -1;           // Se detecta el '_'
            for(int i = 0; i<mensajeActual.size();i++){
                if((mensajeActual.at(i)=='_')&&(comienzo==-1))
                    comienzo = i;
            }
            //moduloCentral->setWindowTitle("Comienzo: "+comienzo);
            if(comienzo!=-1)
            {
                for(int i = comienzo; i<mensajeActual.size();i++){
                    if(mensajeActual.at(i)&0x4F)
                        numeroAuxiliar.append(mensajeActual.at(i));
                }
                moduloCentral->setWindowTitle("La información importante es: " +numeroAuxiliar);

                emit actualizarAnteLlegada();
            }
            estadoActual = 0;
            //QString despertad = "AT\r\n";
            //moduloCentral->escribir(despertad.toUtf8());
        }
    }
        //if(estadoActual == 1)
        if(true)
        {
            moduloCentral->setWindowTitle("Detectando simbolo:");
            int comienzo = -1;           // Se detecta el '_'
            for(int i = 0; i<mensajeActual.size();i++){
                if((mensajeActual.at(i)=='_')&&(comienzo==-1))
                    comienzo = i;
            }
            //moduloCentral->setWindowTitle("Comienzo: "+comienzo);
            if(comienzo!=-1)
            {
                for(int i = comienzo; i<mensajeActual.size();i++){
                    if(mensajeActual.at(i)&0x4F)
                        numeroAuxiliar.append(mensajeActual.at(i));
                }
                moduloCentral->setWindowTitle("La información importante es: " +numeroAuxiliar);

                emit actualizarAnteLlegada();
            }
            estadoActual = 0;

            /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
        }

}

void GUICentral::accionAutomata(int number,char current)
{
    switch(number)
    {
        case 5:
            if(((int)(current-'0')<10)&&((int)(current-'0')>-1))
                numeroMensajeALeer.append(current);
            break;
    default :
            break;
    }
}
