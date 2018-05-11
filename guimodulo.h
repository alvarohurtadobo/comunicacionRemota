#ifndef GUIMODULO_H
#define GUIMODULO_H

#include <QDialog>

#include <QSerialPort>
#include <QDebug>

#define MAX_LINEAS 12

class QLabel;
class QLineEdit;
class QPushButton;

class GUImodulo : public QDialog
{
    Q_OBJECT

public:
    //GUImodulo(ModuloComunicacion myModule);
    GUImodulo(QString port, QWidget *parent = 0);
    ~GUImodulo();

    QByteArray getUltimoMensaje();
    void enviarMensaje(QByteArray number,QByteArray message);
    void leerMensaje(QByteArray messageNumber);
    void escribir(QByteArray mensaje);


signals:
    void recibiMensaje();

private slots:
    void enviarComandoATPresionado();
    void recepcionDatos();

    void realizarLlamada();
    void colgarLlamada();
    void enviarMensajeTexto();
    void enviarUSSDPresionado();

private:
    int numero;
    QSerialPort * serial;
    QByteArray ultimasLineas[MAX_LINEAS];
    QByteArray ultimoMensaje;

    //ModuloComunicacion miModulo;
    QLabel * miTitulo;
    QLabel * miLeyenda1;
    QLabel * miLeyenda2;
    QLabel * leyendaNumero;
    QLabel * leyendaMensaje;
    QLabel * misMensajesAnteriores[MAX_LINEAS-1];
    QLineEdit * mensajeAEnviar;
    QLineEdit * mensajeRecibido;
    QLineEdit * ingresoNumero;
    QLineEdit * ingresoMensaje;
    QPushButton * enviar;
    QPushButton * enviarUSSD;
    QPushButton * llamar;
    QPushButton * colgar;
    QPushButton * enviarMensajeBoton;

    // Auxiliares:
    void enviarMensajeYSUB(QByteArray message);
    bool readyToSend;
    QByteArray mensajeActual;
};

#endif // GUIMODULO_H
