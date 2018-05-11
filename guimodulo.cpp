#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <time.h>
#include <QTime>

#include "guimodulo.h"

using namespace std;

GUImodulo::GUImodulo(QString port,QWidget *parent) : QDialog(parent)
{
    readyToSend = false;
// Se crea y configura la clase serial:
    // SE INICIALIZA EL PUERTO SERIAL:
    serial = new QSerialPort(this);
    // SE CONFIGURA EL MISMO:
    serial->setPortName(port);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);

    connect(serial,SIGNAL(readyRead()),this,SLOT(recepcionDatos()));

// Se incia el módulo en modo SMS
    serial->write("AT+CMGF=1");
    serial->write("\r\n");
    serial->write("AT+CMGD=1,49");

// Se inicializan los objetos de la interfaz grafica:
    miTitulo = new QLabel("Módulo de comunicación");
    miLeyenda1 = new QLabel("Comando AT");
    miLeyenda2 = new QLabel("Ultimos mensaje del Modulo");
    leyendaNumero = new QLabel("Numero");
    leyendaMensaje = new QLabel("Mensaje");

    for(int i = 0;i<MAX_LINEAS-1;i++)
        misMensajesAnteriores[i]= new QLabel("empty");

    mensajeAEnviar = new QLineEdit;
    mensajeRecibido = new QLineEdit;
    ingresoNumero = new QLineEdit;
    ingresoMensaje = new QLineEdit;

    enviar = new QPushButton("Enviar comando AT");
    enviarUSSD = new QPushButton("Enviar USSD");
    llamar = new QPushButton("Llamar");
    colgar = new QPushButton("Colgar");
    enviarMensajeBoton = new QPushButton("Enviar Mensaje");

// Se establecen los parámetros por defecto:
    enviar->setDefault(true);

// Se conectan las señales
    connect(enviar,SIGNAL(clicked()),this,SLOT(enviarComandoATPresionado()));
    connect(enviarUSSD,SIGNAL(clicked()),this,SLOT(enviarUSSDPresionado()));
    connect(llamar,SIGNAL(clicked()),this,SLOT(realizarLlamada()));
    connect(colgar,SIGNAL(clicked()),this,SLOT(colgarLlamada()));
    connect(enviarMensajeBoton,SIGNAL(clicked()),this,SLOT(enviarMensajeTexto()));

// Se crean las capas
    QHBoxLayout * capaTitulo = new QHBoxLayout;
    capaTitulo->addWidget(miTitulo);

    QHBoxLayout * capaEnvio = new QHBoxLayout;
    capaEnvio->addWidget(miLeyenda1);
    capaEnvio->addWidget(mensajeAEnviar);
    capaEnvio->addWidget(enviar);

    QHBoxLayout * capaRecepcion = new QHBoxLayout;
    capaRecepcion->addWidget(miLeyenda2);
    capaRecepcion->addWidget(mensajeRecibido);

    QHBoxLayout * capaLlamada = new QHBoxLayout;
    capaLlamada->addWidget(leyendaNumero);
    capaLlamada->addWidget(ingresoNumero);
    capaLlamada->addWidget(llamar);
    capaLlamada->addWidget(colgar);
    capaLlamada->addWidget(enviarUSSD);

    QHBoxLayout * capaMensaje = new QHBoxLayout;
    capaMensaje->addWidget(leyendaMensaje);
    capaMensaje->addWidget(ingresoMensaje);
    capaMensaje->addWidget(enviarMensajeBoton);

    QVBoxLayout * totalCapas = new QVBoxLayout;
    totalCapas->addLayout(capaTitulo);
    totalCapas->addLayout(capaEnvio);
    totalCapas->addLayout(capaLlamada);
    totalCapas->addLayout(capaMensaje);
    totalCapas->addLayout(capaRecepcion);
    for(int i = 0;i<MAX_LINEAS-1;i++)
        totalCapas->addWidget(misMensajesAnteriores[i]);

    this->setLayout(totalCapas);
    setWindowTitle("Modem Comunicacion");
}


GUImodulo::~GUImodulo()
{
    serial->close();
}

void GUImodulo::recepcionDatos()
{
    // Este SLOT actualiza todos los campos y emite la señal recibiMensaje para hacer conocer a la central que debe analizar los mismos
    ultimoMensaje = serial->readAll();
    mensajeRecibido->setText(ultimoMensaje);
    /*if(ultimoMensaje.length()>20){
        emit recibiMensaje();
    }*/

    for(int i = MAX_LINEAS-1; i>0;i--)
    {
        ultimasLineas[i] = ultimasLineas[i-1];
        misMensajesAnteriores[i-1]->setText(ultimasLineas[i]);
    }
    ultimasLineas[0] = ultimoMensaje;

    if(readyToSend)
     {// Si estamos a la respuesta de un mensaje enviamos el mismo
        enviarMensajeYSUB(mensajeActual);
        readyToSend = false;
        this->setWindowTitle(ultimoMensaje);
     }
    emit recibiMensaje();
}

void GUImodulo::enviarComandoATPresionado()
{
    QByteArray comandoAT = mensajeAEnviar->text().toUtf8();
    serial->write(comandoAT);
    serial->write("\r\n");
}

void GUImodulo::enviarUSSDPresionado()
{
    // Enviando en formato: AT+CUSD=1,"*105#", para mandar opciones solo poner el número de la opcion como ser: AT+CUSD=1,"1"
    QByteArray codigoUSSD = ingresoNumero->text().toUtf8();
    serial->write("AT+CUSD=1,");
    serial->write("\x22");
    serial->write(codigoUSSD);
    serial->write("\x22");
    serial->write("\r\n");
}

void GUImodulo::realizarLlamada()
{
    QByteArray numero = ingresoNumero->text().toUtf8();
    serial->write("ATD+591");
    serial->write(numero);
    serial->write(";\r\n");
}

void GUImodulo::colgarLlamada()
{
    serial->write("ATH");
    serial->write("\r\n");
}

void GUImodulo::enviarMensajeTexto()
{
    QByteArray numero = ingresoNumero->text().toUtf8();
    QByteArray mensaje = ingresoMensaje->text().toUtf8();
    enviarMensaje(numero,mensaje);

    /*readyToSend = true;
    serial->write("AT+CMGS=");
    serial->write("\x22");
    serial->write(numero);
    serial->write("\x22");
    serial->write("\r\n");*/
}

QByteArray GUImodulo::getUltimoMensaje()
{
    return ultimoMensaje;
}

void GUImodulo::enviarMensaje(QByteArray number, QByteArray message)
{
    readyToSend = true;                         // Cuidar este y el que esta en el slot
    serial->write("AT+CMGS=");
    serial->write("\x22");
    serial->write(number);
    serial->write("\x22");
    serial->write("\r\n");
    mensajeActual = message;                    // ~MensajeActual
    /*QTime miTiempo = QTime::currentTime();
    while((QTime::currentTime().msec() - miTiempo.msec())<2000)
    {
        true;
    }*/
    //enviarMensajeYSUB(message);
}

void GUImodulo::leerMensaje(QByteArray messageNumber)
{
    serial->write("AT+CMGR=");
    serial->write(messageNumber);
    serial->write("\r\n");
}

void GUImodulo::escribir(QByteArray mensaje)
{
    serial->write(mensaje);
}

void GUImodulo::enviarMensajeYSUB(QByteArray message)
{
    serial->write(message);
    serial->write("\x1A");
    serial->write("AT\r\n");
}

