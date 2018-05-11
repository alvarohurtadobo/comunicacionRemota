#include "selectorpuerto.h"

#include <QLabel>
#include <QPushButton>

#include <QListView>
#include <QComboBox>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

SelectorPuerto::SelectorPuerto(QWidget *parent) :
    QWidget(parent)
{
    miEtiqueta = new QLabel("Seleccione el Modem a emplear:");
    botonCancelar = new QPushButton("Cancelar");
    botonContinuar = new QPushButton("Continuar");
    miListaPuertos = new QComboBox;

    // Aqui se muestra el puerto seleccionado:
    etiquetaPuertoSeleccionado = new QLabel("Puerto seleccionado: ");
    puertoSeleccionado = new QLabel("");

    // SE ALMACENAN Y AGREGAN LOS PUERTOS AL BOX COMBO

    int i =0;           // El contador i tendra el tamaño del numero de puertos
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        misPuertos[i][0]= info.portName();
        misPuertos[i][1]= info.description();
        misPuertos[i][2]= info.manufacturer();

        qDebug() << "Name        : " << misPuertos[i][0];
        qDebug() << "Description : " << misPuertos[i][1];
        qDebug() << "Manufacturer: " << misPuertos[i][2];
        i++;
    }

    for(int j; j<i;j++){
        miListaPuertos->addItem(misPuertos[j][0]+"; "+misPuertos[j][1]+"; "+misPuertos[j][2]);
    }

    // Si el puerto esta vacio no permitira el ingreso en modo normal y en modo prueba lo garantizará:

    QHBoxLayout *seleccionMuestra = new QHBoxLayout;
    seleccionMuestra->addWidget(etiquetaPuertoSeleccionado);
    seleccionMuestra->addWidget(puertoSeleccionado);

    QHBoxLayout * misOpciones = new QHBoxLayout;
    misOpciones->addWidget(botonCancelar);
    misOpciones->addWidget(botonContinuar);

    botonContinuar->setDefault(true);

    QVBoxLayout * total = new QVBoxLayout;
    total->addWidget(miEtiqueta);
    total->addWidget(miListaPuertos);
    total->addLayout(seleccionMuestra);
    total->addLayout(misOpciones);

    // CONEXIONES:
    // Botones:
    connect(botonCancelar,SIGNAL(clicked()),this,SLOT(close()));
    connect(botonContinuar,SIGNAL(clicked()),this,SLOT(puertoSeleccionadoYEjecutar()));

    // Presionado ComboBox
    connect(miListaPuertos,SIGNAL(highlighted(int)),this,SLOT(actualizarPuerto(int)));

    // Para no arrancar el programa a menos que se seleccione un puerto de forma conciente se inicializa el inicializador en falso:
    seleccionado = false;

    this->setLayout(total);
    this->setWindowTitle("Selección de puerto de comunicación");
    this->show();
}

void SelectorPuerto::actualizarPuerto(int currentPort)
{
    seleccionado = true;
    puertoAMandar = misPuertos[currentPort][0];
    puertoSeleccionado->setText(puertoAMandar);
}

void SelectorPuerto::puertoSeleccionadoYEjecutar()
{
    if(seleccionado){
        puertoSeleccionado->setText(puertoAMandar+" mandado!!");
        miSistema = new SistemaControl(puertoAMandar);
        this->close();
    }
    else{
        puertoSeleccionado->setText("<Seleccionar>");
        // Delete this
        miSistema = new SistemaControl(puertoAMandar);
        this->close();
    }
}
