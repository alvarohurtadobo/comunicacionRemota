#include "sistemacontrol.h"

SistemaControl::SistemaControl(QString port, QObject * parent) : QObject(parent)
{
    miPantallaControl = new InterfazGrafica;

    esperandoModem = false;

    miCentral.inicializarModulo(port);
    numeroSubSistema.append("65423572");
    mensajeSolicitud.append("/acb0%");


    connect(miPantallaControl,SIGNAL(llamadoAModem()),this,SLOT(arrancarGUIModem()));
    connect(miPantallaControl,SIGNAL(solicitudDatos()),this,SLOT(solicitarMediciones()));
    connect(miPantallaControl,SIGNAL(ordenEjecutar()),this,SLOT(ejecutarCorteConexion()));
    connect(&miCentral,SIGNAL(actualizarAnteLlegada()),this,SLOT(actualizarAnteAlertaGUICentral()));
    connect(&miCentral,SIGNAL(informeCorte()),this,SLOT(actualizarInformacionCorte()));

    connect(miPantallaControl,SIGNAL(comandoFiltroCambiado(QString)),this,SLOT(actualizarBusqueda(QString)));

    connect(&miControl,SIGNAL(paraEjecutar(bool,QString,QString)),this,SLOT(nuevaEjecucion(bool,QString,QString)));

    // BASE DATOS
    miPantallaControl->establecerVistaTabla(miControl.getFiltro());
    connect(&miControl,SIGNAL(tablaActualizada()),this,SLOT(actualizarTabla()));
    connect(miPantallaControl,SIGNAL(llamadaExportacion()),this,SLOT(exportar()));

    connect(miPantallaControl,SIGNAL(solicitudNuevoChip(QString)),this,SLOT(anteNuevoNumero(QString)));

    connect(miPantallaControl,SIGNAL(emitRefrescoModem()),this,SLOT(anteRefrescoModem()));
    connect(miPantallaControl,SIGNAL(emitRefrescoPotencias()),this,SLOT(anteRefrescoPontencias()));

    connect(&miCentral,SIGNAL(moduloDespierto()),this,SLOT(anteModuloDespierto()));

    miPantallaControl->show();
}

QString SistemaControl::getContrasena()
{
    return contrasena;
}

void SistemaControl::setContrasena(QString pass)
{
    contrasena = pass;
}

void SistemaControl::arrancarGUIModem()
{
    miCentral.accederModulo()->show();
}

void SistemaControl::solicitarMediciones()
{
    miCentral.accederModulo()->enviarMensaje(miCentral.agenda(0),mensajeSolicitud.toUtf8());
}

void SistemaControl::ejecutarCorteConexion()
{
    QByteArray miMensaje;
    miMensaje.append("/acb0<");
    int disponibles = miPantallaControl->obtenerFaltantes();
    while(disponibles)
    {
        miMensaje.append(miPantallaControl->obtenerAccion(disponibles-1));
        miMensaje.append(miPantallaControl->obtenerCentralizador(disponibles-1));
        miMensaje.append(miPantallaControl->obtenerPuerto(disponibles-1));
        //miMensaje.append(".");
        miPantallaControl->ordenEjecutada();
        disponibles = miPantallaControl->obtenerFaltantes();
    }
    miMensaje.append(">");
    miCentral.accederModulo()->enviarMensaje(miCentral.agenda(0),miMensaje);
}

void SistemaControl::actualizarAnteAlertaGUICentral()
{
    bool estadosActuales[16]={0};
    unsigned long datosTraducidos1[8] = {0};
    unsigned long datosTraducidos2[8] = {0};
    QByteArray datoCortado[2];
    QByteArray datoFiltrado[2];
    QByteArray datoSinFiltrar;
    int mitad = 0;

    datoSinFiltrar = miCentral.numeroAuxiliar;
    for(int l = 0; l< datoSinFiltrar.size();l++)
    {
        if(datoSinFiltrar.at(l)=='1'){
            mitad = l;
        }
    }

    for(int l = 0; l<mitad;l++){
        datoCortado[0].append(datoSinFiltrar.at(l));
    }

    for(int l = mitad; l<datoSinFiltrar.size();l++){
        datoCortado[1].append(datoSinFiltrar.at(l));
    }

    for(int l = 0; l< datoCortado[0].size();l++){
        if((datoCortado[0].at(l)>='A')&&(datoCortado[0].at(l)<='P')){
            datoFiltrado[0].append(datoCortado[0].at(l));
        }
    }

    for(int l = 0; l< datoCortado[1].size();l++){
        if((datoCortado[1].at(l)>='A')&&(datoCortado[1].at(l)<='P')){
            datoFiltrado[1].append(datoCortado[1].at(l));
        }
    }

    for(int l = 0; l< 8;l++){
        datosTraducidos1[l] += (unsigned long)(datoFiltrado[0].at(8*l)-'A');
        datosTraducidos1[l] += (unsigned long)((datoFiltrado[0].at(8*l+1)-'A')&0x7)*(unsigned long)16;
        datosTraducidos1[l] += (unsigned long)(datoFiltrado[0].at(8*l+2)-'A')*(unsigned long)16*8;
        datosTraducidos1[l] += (unsigned long)((datoFiltrado[0].at(8*l+3)-'A')&0x7)*(unsigned long)16*8*16;
        datosTraducidos1[l] += (unsigned long)(datoFiltrado[0].at(8*l+4)-'A')*(unsigned long)16*8*16*8;
        datosTraducidos1[l] += (unsigned long)((datoFiltrado[0].at(8*l+5)-'A')&0x7)*(unsigned long)16*8*16*8*16;
        datosTraducidos1[l] += (unsigned long)(datoFiltrado[0].at(8*l+6)-'A')*(unsigned long)16*8*16*8*16*8;
        datosTraducidos1[l] += (unsigned long)((datoFiltrado[0].at(8*l+7)-'A')&0x3)*(unsigned long)16*8*16*8*16*8*16;
        estadosActuales[l]=((datoFiltrado[0].at(8*l+7)-'A')&0x4);

        datosTraducidos2[l] += (unsigned long)(datoFiltrado[1].at(8*l)-'A');
        datosTraducidos2[l] += (unsigned long)((datoFiltrado[1].at(8*l+1)-'A')&0x7)*(unsigned long)16;
        datosTraducidos2[l] += (unsigned long)(datoFiltrado[1].at(8*l+2)-'A')*(unsigned long)16*8;
        datosTraducidos2[l] += (unsigned long)((datoFiltrado[1].at(8*l+3)-'A')&0x7)*(unsigned long)16*8*16;
        datosTraducidos2[l] += (unsigned long)(datoFiltrado[1].at(8*l+4)-'A')*(unsigned long)16*8*16*8;
        datosTraducidos2[l] += (unsigned long)((datoFiltrado[1].at(8*l+5)-'A')&0x7)*(unsigned long)16*8*16*8*16;
        datosTraducidos2[l] += (unsigned long)(datoFiltrado[1].at(8*l+6)-'A')*(unsigned long)16*8*16*8*16*8;
        datosTraducidos2[l] += (unsigned long)((datoFiltrado[1].at(8*l+7)-'A')&0x3)*(unsigned long)16*8*16*8*16*8*16;
        estadosActuales[l+8]=((datoFiltrado[1].at(8*l+7)-'A')&0x4);
    }

    for(int i = 0;i<8;i++){
        miControl.actualizarLectura(i,estadosActuales[i],datosTraducidos1[i]);
        miControl.actualizarLectura(i+8,estadosActuales[i+8],datosTraducidos2[i]);
    }

    miPantallaControl->actualizacionExitosa();
    miPantallaControl->setAlerta("Actualizaciones recibidas exitosamente !!");
}

void SistemaControl::actualizarTabla()
{
    miPantallaControl->establecerVistaTabla(miControl.getFiltro());
}

void SistemaControl::actualizarBusqueda(QString key)
{
    miControl.getFiltro()->setFilterFixedString(key);
}

void SistemaControl::exportar()
{
    miExportador.exportarCSV(miControl.getTabla());
}

void SistemaControl::nuevaEjecucion(bool verificado, QString antes, QString despues)
{
    //miPantallaControl->getRegistro()->setText(miPantallaControl->getRegistro()->text()+verificado+"_"+antes+"_"+despues+"\n");
}

void SistemaControl::anteNuevoNumero(QString number)
{
    QByteArray mensajeCambio;
    mensajeCambio.append("/acb0#");
    mensajeCambio.append(number);
    //miCentral.accederModulo()->enviarMensaje(numeroSubSistema.toUtf8(),mensajeCambio);
    miCentral.accederModulo()->enviarMensaje(miCentral.agenda(0),mensajeCambio);
}

void SistemaControl::actualizarInformacionCorte()
{
    miPantallaControl->setAlerta("El módulo acaba de sufrir un corte");
}

void SistemaControl::anteRefrescoPontencias()
{
    miControl.actualizarPotencias();
}

void SistemaControl::anteRefrescoModem()
{
    QByteArray miArray;
    miArray.append("AT\r\n");
    miCentral.accederModulo()->escribir(miArray);
    esperandoModem = true;
}

void SistemaControl::anteModuloDespierto()
{
    if(esperandoModem){
        miPantallaControl->setAlerta("Modulo en funcionamiento normal en hora: "+QDate::currentDate().toString());
        esperandoModem = false;
    }
}

// PARA LA BASE DE DATOS

