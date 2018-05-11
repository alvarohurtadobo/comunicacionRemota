#include <QTableWidget>

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include <QTableView>
#include <QComboBox>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "interfazgrafica.h"

InterfazGrafica::InterfazGrafica(QWidget *parent) : QWidget(parent)
{
    // Alertas:
    etiquetaAlertas = new QLabel("Alertas:");
    misAlertas = new QLabel;

    // PANTALLA TOTAL SUPERIOR
    miParteSuperior = new QTabWidget;
    miParteSuperior->setMaximumHeight(200);
    miParteSuperior->setMinimumWidth(1000);
    miPantallaControl = new QWidget;
    miPantallaSeguridad = new QWidget;
    miPantallaInformacion = new QWidget;

    miFondoImagen1 = new QLabel;
    miImagenFondo1.load("elfeosa.bmp");
    miImagenFondo1=miImagenFondo1.scaledToWidth(miImagenFondo1.width()*0.8);
    miFondoImagen1->setPixmap(miImagenFondo1);

    miFondoImagen2 = new QLabel;
    miImagenFondo2.load("ende.bmp");
    miFondoImagen2->setPixmap(miImagenFondo2);

    miFondoImagen3 = new QLabel(miFondoImagen1);
    miFondoImagen3->setPixmap(miImagenFondo1);
    miFondoImagen4 = new QLabel(miFondoImagen2);
    miFondoImagen4->setPixmap(miImagenFondo2);

    miFondoImagen5 = new QLabel(miFondoImagen1);
    miFondoImagen5->setPixmap(miImagenFondo1);
    miFondoImagen6 = new QLabel(miFondoImagen2);
    miFondoImagen6->setPixmap(miImagenFondo2);

/*////////////////////////////////PANTALLA DE SEGURIDAD////////////////////////////////////////////*/
    etiquetaTituloCambioContrasena = new QLabel("Si desea cambiar la contraseña del sistema:");
    etiquetaAdvertencia = new QLabel;

    etiquetaAntiguaContrasena = new QLabel("Ingrese la contraseña actual");
    etiquetaNuevaContrasena = new QLabel("Ingrese la nueva contraseña");
    etiquetaConfirmarContrasena = new QLabel("Vuelva a ingresar la contraseña");

    entradaAntiguaContrasena = new QLineEdit;
    entradaAntiguaContrasena->setEchoMode(QLineEdit::Password);
    entradaNuevaContrasena = new QLineEdit;
    entradaNuevaContrasena->setEchoMode(QLineEdit::Password);
    entradaConfirmarContrasena = new QLineEdit;
    entradaConfirmarContrasena->setEchoMode(QLineEdit::Password);

    botonEjecutarCambioContrasena = new QPushButton("Cambiar contraseña");
    botonCancelarCambioContrasena = new QPushButton("Cancelar");

    connect(botonCancelarCambioContrasena,SIGNAL(clicked()),this,SLOT(borrarIntentoContrasena()));
    connect(botonEjecutarCambioContrasena,SIGNAL(clicked()),this,SLOT(ejecutarCambioContrasena()));


    QHBoxLayout * antiguaContrasena = new QHBoxLayout;
    antiguaContrasena->addWidget(etiquetaAntiguaContrasena);
    antiguaContrasena->addWidget(entradaAntiguaContrasena);

    QHBoxLayout * nuevaContrasena = new QHBoxLayout;
    nuevaContrasena->addWidget(etiquetaNuevaContrasena);
    nuevaContrasena->addWidget(entradaNuevaContrasena);

    QHBoxLayout * confirmarContrasena = new QHBoxLayout;
    confirmarContrasena->addWidget(etiquetaConfirmarContrasena);
    confirmarContrasena->addWidget(entradaConfirmarContrasena);


    QHBoxLayout * ejecucionContrasena = new QHBoxLayout;
    ejecucionContrasena->addWidget(botonEjecutarCambioContrasena);
    ejecucionContrasena->addWidget(botonCancelarCambioContrasena);

    QVBoxLayout * contrasena = new QVBoxLayout;
    contrasena->addWidget(etiquetaTituloCambioContrasena);
    contrasena->addWidget(etiquetaAdvertencia);
    contrasena->addLayout(antiguaContrasena);
    contrasena->addLayout(nuevaContrasena);
    contrasena->addLayout(confirmarContrasena);
    contrasena->addLayout(ejecucionContrasena);

    etiquetaTituloCambioNumero = new QLabel("Si desea cambiar el número de la central:");
    etiquetaNuevoNumero = new QLabel("Ingrese el nuevo número del chip");
    botonEjecutarCambioNumero = new QPushButton("Cambiar número");
    botonCancelarCambioNumero = new QPushButton("Cancelar");
    etiquetaContrasenaActual = new QLabel("Contraseña de administrador: ");

    entradaContrasenaActual = new QLineEdit;
    entradaContrasenaActual->setEchoMode(QLineEdit::Password);
    entradaNuevoNumero = new QLineEdit;

    connect(botonCancelarCambioNumero,SIGNAL(clicked()),this,SLOT(borrarIntentoNumero()));
    connect(botonEjecutarCambioNumero,SIGNAL(clicked()),this,SLOT(ejecutarCambioNumero()));


    QHBoxLayout * numeroNuevo = new QHBoxLayout;
    numeroNuevo->addWidget(etiquetaNuevoNumero);
    numeroNuevo->addWidget(entradaNuevoNumero);

    QHBoxLayout * confirmarCambio = new QHBoxLayout;
    confirmarCambio->addWidget(etiquetaContrasenaActual);
    confirmarCambio->addWidget(entradaContrasenaActual);

    QHBoxLayout * ejecutarCambio = new QHBoxLayout;
    ejecutarCambio->addWidget(botonEjecutarCambioNumero);
    ejecutarCambio->addWidget(botonCancelarCambioNumero);

    QVBoxLayout * numero = new QVBoxLayout;
    numero->addWidget(etiquetaTituloCambioNumero);
    numero->addLayout(numeroNuevo);
    numero->addLayout(confirmarCambio);
    numero->addLayout(ejecutarCambio);



    QHBoxLayout * totalSEG = new QHBoxLayout;
    totalSEG->addWidget(miFondoImagen4);
    totalSEG->addLayout(contrasena);
    totalSEG->addLayout(numero);
    totalSEG->addWidget(miFondoImagen3);

    miPantallaSeguridad->setLayout(totalSEG);


/*////////////////////////////////PANTALLA DE INFORMACIÓN////////////////////////////////////////////*/

    miEtiqueta = new QLabel("Este programa fue desarrollado por el Univ. Álvaro Rubén Hurtado Maldonado\na.hurtado.bo@ieee.org\nUniversidad Técnica de Oruro \nFacultad Nacional de Ingeniería\nCarrera de Ingeniería Eléctrica - Ingeniería Electrónica\npara la Empresa de Luz y Fuerza Eléctrica Oruro. S.A.\nEmpleando Qt Creator 3.0.1");
    QHBoxLayout * totalI = new QHBoxLayout;
    totalI->addWidget(miFondoImagen6);
    totalI->addWidget(miEtiqueta);
    totalI->addWidget(miFondoImagen5);

    miPantallaInformacion->setLayout(totalI);

/*////////////////////////////////////// GENERAL /////////////////////////////////////*/
    miTitulo1 = new QLabel("Adquisición de datos");

    etiquetaActualizacion = new QLabel("Ultima actualizacion: ");
    ultimoTiempo = new QLabel(" ");


    etiquetaSubsistema = new QLabel("Sub Sistema");
    numeroSistema = new QLineEdit;
    solicitarDatos = new QPushButton("Solicitar Datos");

    accederModemComunicacion = new QPushButton("Acceder al modem de comunicacion");
    //accederModemRemoto = new QPushButton("Consultar Saldo");
    accederSistemaActuacion = new QPushButton("Realizar Corte/Conexion");

    miInformacionActualizada = new QLabel("Ultima Actualizacion: \n");

// Conectando S/S
    connect(accederModemComunicacion,SIGNAL(clicked()),this,SLOT(solicitudModemPresionado()));
    connect(accederSistemaActuacion,SIGNAL(clicked()),this,SLOT(solicitudCC()));

    connect(solicitarDatos,SIGNAL(clicked()),this,SLOT(solicitarDatosPresionado()));

    QHBoxLayout * datosAdquisicion = new QHBoxLayout;
    datosAdquisicion->addWidget(etiquetaActualizacion);
    datosAdquisicion->addWidget(ultimoTiempo);


    QHBoxLayout * adquisicion = new QHBoxLayout;
    adquisicion->addWidget(etiquetaSubsistema);
    adquisicion->addWidget(numeroSistema);
    adquisicion->addWidget(solicitarDatos);

    QHBoxLayout * comunicacion = new QHBoxLayout;
    comunicacion->addWidget(accederModemComunicacion);
    //comunicacion->addWidget(accederModemRemoto);

    QHBoxLayout * acceso = new QHBoxLayout;
    acceso->addWidget(accederSistemaActuacion);



    QVBoxLayout * total1 = new QVBoxLayout;
    total1->addWidget(miTitulo1);
    total1->addLayout(datosAdquisicion);
    total1->addLayout(adquisicion);
    total1->addLayout(comunicacion);


/*///////////////////////////////////CORTE Y CONEXIÓN/////////////////////////////////////*/
    miTitulo2 = new QLabel("Corte y conexión");

    botonEjecutar = new QPushButton("Ejecutar Acciones");
    botonCancelar = new QPushButton("Cancelar Acciones");

    etiquetaSubSistemaCC = new QLabel("Subsistema");
    etiquetaCentralizador = new QLabel("Centralizador");
    etiquetaPuerto = new QLabel("Puerto");

    ingresoSubSistema = new QLineEdit;
    ingresoCentralizador = new QLineEdit;
    ingresoPuerto = new QLineEdit;


    botonCortar = new QPushButton("Cortar Suministro");
    botonEstablecer = new QPushButton("Conectar Suministro");

    connect(botonCortar,SIGNAL(clicked()),this,SLOT(cortarPresionado()));
    connect(botonEstablecer,SIGNAL(clicked()),this,SLOT(establecerPresionado()));
    connect(botonEjecutar,SIGNAL(clicked()),this,SLOT(ejecutarPresionado()));
    connect(botonCancelar,SIGNAL(clicked()),this,SLOT(cancelarPresionado()));

    QHBoxLayout * subSistema = new QHBoxLayout;
    subSistema->addWidget(etiquetaSubSistemaCC);
    subSistema->addWidget(ingresoSubSistema);

    QHBoxLayout * centralizador = new QHBoxLayout;
    centralizador->addWidget(etiquetaCentralizador);
    centralizador->addWidget(ingresoCentralizador);

    QHBoxLayout * puerto = new QHBoxLayout;
    puerto->addWidget(etiquetaPuerto);
    puerto->addWidget(ingresoPuerto);

    QHBoxLayout * opcionesEjecucion = new QHBoxLayout;
    opcionesEjecucion->addWidget(botonCortar);
    opcionesEjecucion->addWidget(botonEstablecer);

    QHBoxLayout * ejecucion = new QHBoxLayout;
    ejecucion->addWidget(botonEjecutar);
    ejecucion->addWidget(botonCancelar);

    QVBoxLayout * total2 = new QVBoxLayout;
    total2->addWidget(miTitulo2);
    total2->addLayout(subSistema);
    total2->addLayout(centralizador);
    total2->addLayout(puerto);
    total2->addLayout(opcionesEjecucion);
    total2->addLayout(ejecucion);
    //total2->addLayout(acceso);

/*///////////////////////////////////BASE DE DATOS/////////////////////////////////////*/
    botonExportar = new QPushButton("Exportar Base de Datos");
    registro = new QLabel("Registro:\n");
    salir = new QPushButton("Salir");
    connect(botonExportar,SIGNAL(clicked()),this,SLOT(solicitudExportarPresionado()));
    connect(salir,SIGNAL(clicked()),this,SLOT(salirPresionado()));

    refrescoModem = new QPushButton("Refrescar Modem");
    refrescoPotencias = new QPushButton("Refrescar Potencias");

    connect(refrescoModem,SIGNAL(clicked()),this,SLOT(solicitudRefrescoModem()));
    connect(refrescoPotencias,SIGNAL(clicked()),this,SLOT(solicitudRefrescoPotencias()));

    QHBoxLayout *refrescos = new QHBoxLayout;
    refrescos->addWidget(refrescoModem);
    refrescos->addWidget(refrescoPotencias);

    QHBoxLayout *opcionFinal = new QHBoxLayout;
    opcionFinal->addWidget(botonExportar);
    opcionFinal->addWidget(salir);

    QVBoxLayout * total3 = new QVBoxLayout;
    total3->addWidget(registro);
    total3->addLayout(refrescos);
    total3->addLayout(opcionFinal);

    QHBoxLayout * totalG = new QHBoxLayout;
    totalG->addWidget(miFondoImagen2);
    totalG->addLayout(total1);
    totalG->addLayout(total2);
    totalG->addLayout(total3);
    totalG->addWidget(miFondoImagen1);

    miPantallaControl->setLayout(totalG);

/*/////////////////////////////////// BASE DE DATOS VISUAL//////////////////////////////////*/


// Se crean los objetos
    miBusqueda = new QLineEdit;
    miEtiquetaBusqueda = new QLabel("Buscar: ");
    miTablaMediciones = new QTableView;

    connect(miTablaMediciones,SIGNAL(clicked(QModelIndex)),this,SLOT(seleccionCelda(QModelIndex)));

// Se asigna la tabla y se establece su tamaño:

    miTablaMediciones->setColumnWidth(0,25);
    miTablaMediciones->setColumnWidth(5,35);
    miTablaMediciones->setColumnWidth(6,40);
    miTablaMediciones->setColumnWidth(7,50);
    miTablaMediciones->setColumnWidth(8,40);
    miTablaMediciones->setColumnWidth(9,25);
    miTablaMediciones->setColumnWidth(10,25);
    miTablaMediciones->setColumnWidth(11,80);
    miTablaMediciones->setColumnWidth(12,70);
    miTablaMediciones->setColumnWidth(13,50);

// Se conectan los objetos incluyendo los de busqueda:
    connect(miBusqueda,SIGNAL(textChanged(QString)),this,SLOT(solicitudBusquedaCambiada(QString)));

// Se organizan los objetos
    QHBoxLayout * opciones = new QHBoxLayout;
    opciones->addWidget(miEtiquetaBusqueda);
    opciones->addWidget(miBusqueda);


    QVBoxLayout * totalDB = new QVBoxLayout;
    totalDB->addLayout(opciones);
    totalDB->addWidget(miTablaMediciones);

    /*/////////////TABLERO DE CONTROL COMPLETO//////////////*/
    miParteSuperior->addTab(miPantallaControl,"Principal");
    miParteSuperior->addTab(miPantallaSeguridad,"Seguridad");
    miParteSuperior->addTab(miPantallaInformacion,"Acerca de");

    QVBoxLayout * total = new QVBoxLayout;
    total->addWidget(miParteSuperior);
    total->addLayout(totalDB);
    total->addWidget(etiquetaAlertas);
    total->addWidget(misAlertas);


    this->setLayout(total);
    setWindowTitle("Sistema de control");

    QSize iconoSuperior(1,1);
    miIcono.addFile("elfeosa.bmp",iconoSuperior);
    this->setWindowIcon(miIcono);
}

QLabel* InterfazGrafica::obtenerLabelInformacion()
{
    return miInformacionActualizada;
}

void InterfazGrafica::establecerVistaTabla(QSortFilterProxyModel *myTable)
{
    miTablaMediciones->setModel(myTable);
}

void InterfazGrafica::actualizacionExitosa()
{
    ultimoTiempo->setText(QDateTime::currentDateTime().toString("dd MMMM yyyy hh:mm:ss"));
}

QLabel *InterfazGrafica::getRegistro()
{
    return registro;
}

void InterfazGrafica::actualizarNumerosCC(int data)
{
    ingresoSubSistema->setText("76138856");
    if(data<8)
    {
        ingresoCentralizador->setText("0");
        ingresoPuerto->setText(QString::number(data));
    }
    else
    {
        ingresoCentralizador->setText("1");
        ingresoPuerto->setText(QString::number(data-8));
    }
}

int InterfazGrafica::obtenerFaltantes()
{
    return faltantes;
}

int InterfazGrafica::obtenerSubsistema()
{
    return ingresoSubSistema->text().toInt();
}

QByteArray InterfazGrafica::obtenerAccion(int posicion)
{
    return accion[posicion];
}

QByteArray InterfazGrafica::obtenerCentralizador(int posicion)
{
    return locacion[posicion][0];
}

QByteArray InterfazGrafica::obtenerPuerto(int posicion)
{
    return locacion[posicion][1];
}

void InterfazGrafica::ordenEjecutada()
{
    faltantes--;
}

void InterfazGrafica::setAlerta(QString miAlerta)
{
    misAlertas->setText(QDateTime::currentDateTime().toString("dd MMMM yyyy hh:mm:ss")+": "+ miAlerta);
}



void InterfazGrafica::solicitudModemPresionado()
{
    emit llamadoAModem();
}

void InterfazGrafica::solicitudCC()
{
    emit llamadoACC();
}

void InterfazGrafica::solicitarDatosPresionado()
{
    emit solicitudDatos();
    misAlertas->setText("Solicitando Actualizaciones ...");
}

void InterfazGrafica::solicitudExportarPresionado()
{
    emit llamadaExportacion();
}

void InterfazGrafica::solicitudBusquedaCambiada(QString searchKey)
{
    emit comandoFiltroCambiado(searchKey);
}

void InterfazGrafica::seleccionCelda(QModelIndex miDato)
{
    numeroSistema->setText("76138856 ("+miDato.data().toString()+")");
    actualizarNumerosCC(miDato.row());
    emit numeroCeldaPresionada(miDato.row());
}

void InterfazGrafica::borrarIntentoContrasena()
{
    entradaAntiguaContrasena->clear();
    entradaNuevaContrasena->clear();
    entradaConfirmarContrasena->clear();
}

void InterfazGrafica::ejecutarCambioContrasena()
{
    QFile miArchivoTemporal(QDir::currentPath()+"/OddOne.txt");
    QString line;
    if (miArchivoTemporal.open(QIODevice::ReadOnly))
    {
       QTextStream in(&miArchivoTemporal);
       while ( !in.atEnd() )
       {
            line = in.readLine();
       }
       miArchivoTemporal.close();
    }
    if((entradaAntiguaContrasena->text()==line)&&(entradaConfirmarContrasena->text()==entradaNuevaContrasena->text())&&(entradaNuevaContrasena->text().size()>=8))
    {

        if (miArchivoTemporal.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream data( &miArchivoTemporal );
            data << entradaNuevaContrasena->text();
            miArchivoTemporal.close();
        }
        etiquetaAdvertencia->setText("Contraseña cambiada exitosamente");
    }
    else{
        etiquetaAdvertencia->setText("Error al ingresar la contraseña");
    }
    borrarIntentoContrasena();

}

void InterfazGrafica::borrarIntentoNumero()
{
    entradaNuevoNumero->clear();
    entradaContrasenaActual->clear();
}

void InterfazGrafica::ejecutarCambioNumero()
{
    if(entradaContrasenaActual->text()=="vj19gn13d23n")
        emit solicitudNuevoChip(entradaNuevoNumero->text());
    borrarIntentoNumero();
}

void InterfazGrafica::ejecutarPresionado()
{
    emit ordenEjecutar();
    registro->setText("Registo: \n");
    //faltantes = 0;
    //this->close();
}

void InterfazGrafica::cancelarPresionado()
{
    faltantes = 0;
    registro->setText("Registo: \n");
}

void InterfazGrafica::salirPresionado()
{
    this->close();
}

void InterfazGrafica::cortarPresionado()
{
    if((ingresoCentralizador->text().size()!=1)||(ingresoPuerto->text().size()!=1))
        return;
    QString c = "c";
    accion[faltantes] = c.toUtf8();
    locacion[faltantes][0] = ingresoCentralizador->text().toUtf8();
    locacion[faltantes][1] = ingresoPuerto->text().toUtf8();

    registro->setText(registro->text() + "Cortar centralizador: "+ingresoCentralizador->text()+" en puerto: "+ingresoPuerto->text()+"\n");


    ingresoCentralizador->clear();
    ingresoPuerto->clear();

    faltantes++;
}

void InterfazGrafica::establecerPresionado()
{
    if((ingresoCentralizador->text().size()!=1)||(ingresoPuerto->text().size()!=1))
        return;
    QString e = "e";
    accion[faltantes] = e.toUtf8();
    locacion[faltantes][0] = ingresoCentralizador->text().toUtf8();
    locacion[faltantes][1] = ingresoPuerto->text().toUtf8();

    registro->setText(registro->text() + "Establecer centralizador: "+ingresoCentralizador->text()+" en puerto: "+ingresoPuerto->text()+"\n");


    ingresoCentralizador->clear();
    ingresoPuerto->clear();

    faltantes++;
}

void InterfazGrafica::solicitudRefrescoPotencias()
{
    emit emitRefrescoPotencias();
}

void InterfazGrafica::solicitudRefrescoModem()
{
    emit emitRefrescoModem();
    misAlertas->setText("Verificando Modem");
}
