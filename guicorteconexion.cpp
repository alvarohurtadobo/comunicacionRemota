#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>



#include "guicorteconexion.h"

GUICorteConexion::GUICorteConexion(QWidget * parent) : QDialog(parent)
{
    faltantes = 0;


//  interfaz gráfica:
    etiquetaSubSistema = new QLabel("Ingrese el Sub Sistema");
    etiquetaCentralizador = new QLabel("Ingrese el centralizador");
    etiquetaPuerto =  new QLabel("Puerto");
    etiRegistro = new QLabel("Registo: \n");

    ingresoSubSistema = new QLineEdit;
    ingresoCentralizador = new QLineEdit;
    ingresoPuerto = new QLineEdit;

    botonCortar = new QPushButton("Cortar Suministro");
    botonEstablecer = new QPushButton("Establecer Suministro");
    botonEjecutar = new QPushButton("Ejecutar");
    botonCancelar = new QPushButton("Cancelar");

    botonCancelar->setDefault(true);

    QHBoxLayout * subsistema = new QHBoxLayout;
    subsistema->addWidget(etiquetaSubSistema);
    subsistema->addWidget(ingresoSubSistema);

    QHBoxLayout * centralizador = new QHBoxLayout;
    centralizador->addWidget(etiquetaCentralizador);
    centralizador->addWidget(ingresoCentralizador);

    QHBoxLayout * puerto = new QHBoxLayout;
    puerto->addWidget(etiquetaPuerto);
    puerto->addWidget(ingresoPuerto);

    QHBoxLayout *opciones = new QHBoxLayout;
    opciones->addWidget(botonCortar);
    opciones->addWidget(botonEstablecer);
    opciones->addWidget(botonEjecutar);
    opciones->addWidget(botonCancelar);

    QVBoxLayout *total1 = new QVBoxLayout;
    //total1->addLayout(subsistema);
    total1->addLayout(centralizador);
    total1->addLayout(puerto);
    //total1->addWidget(etiRegistro);
    total1->addLayout(opciones);

    QVBoxLayout *total2 = new QVBoxLayout;
    total2->addWidget(etiRegistro);

    total = new QHBoxLayout;
    total->addLayout(total1);
    total->addLayout(total2);


    // Conexiones:
    connect(botonCortar,SIGNAL(clicked()),this,SLOT(cortarPresionado()));
    connect(botonEstablecer,SIGNAL(clicked()),this,SLOT(establecerPresionado()));
    connect(botonEjecutar,SIGNAL(clicked()),this,SLOT(ejecutarPresionado()));
    connect(botonCancelar,SIGNAL(clicked()),this,SLOT(cancelarPresionado()));

    this->setLayout(total);
    this->setWindowTitle("Realizar corte o reconexion");

}

int GUICorteConexion::obtenerFaltantes()
{
    //int aux = faltantes;                        // Se borra los faltantes en esta clase pero se retorna el número para el envio
    //faltantes = 0;
    //return aux;
    return faltantes;
}

int GUICorteConexion::obtenerSubsistema()
{
    return ingresoSubSistema->text().toInt();
}

QByteArray GUICorteConexion::obtenerAccion(int posicion)
{
    return accion[posicion];
}

QByteArray GUICorteConexion::obtenerCentralizador(int posicion)
{
    return locacion[posicion][0];
}

QByteArray GUICorteConexion::obtenerPuerto(int posicion)
{
    return locacion[posicion][1];
}

void GUICorteConexion::ordenEjecutada()
{
    faltantes--;
}

QHBoxLayout *GUICorteConexion::robarVista()
{
    return total;
}

void GUICorteConexion::cortarPresionado()
{
    QString c = "c";
    accion[faltantes] = c.toUtf8();
    locacion[faltantes][0] = ingresoCentralizador->text().toUtf8();
    locacion[faltantes][1] = ingresoPuerto->text().toUtf8();

    etiRegistro->setText(etiRegistro->text() + "Cortar centralizador: "+ingresoCentralizador->text()+" en puerto: "+ingresoPuerto->text()+"\n");


    ingresoCentralizador->clear();
    ingresoPuerto->clear();

    faltantes++;
}

void GUICorteConexion::establecerPresionado()
{
    QString e = "e";
    accion[faltantes] = e.toUtf8();
    locacion[faltantes][0] = ingresoCentralizador->text().toUtf8();
    locacion[faltantes][1] = ingresoPuerto->text().toUtf8();

    etiRegistro->setText(etiRegistro->text() + "Establecer centralizador: "+ingresoCentralizador->text()+" en puerto: "+ingresoPuerto->text()+"\n");


    ingresoCentralizador->clear();
    ingresoPuerto->clear();

    faltantes++;
}

void GUICorteConexion::ejecutarPresionado()
{
    emit ordenEjecutar();
    etiRegistro->setText("Registo: \n");
    //faltantes = 0;
    this->close();
}

void GUICorteConexion::cancelarPresionado()
{
    faltantes = 0;
    etiRegistro->setText("Registo: \n");
    this->close();
}
