#ifndef GUICENTRAL_H
#define GUICENTRAL_H

#include <QDialog>
#include <guimodulo.h>
#define MAX_SUBSISTEMAS 100

class GUICentral : public QDialog
{
    Q_OBJECT
public:
    explicit GUICentral(QWidget *parent = 0);

    ~GUICentral();
    GUImodulo * accederModulo();
    int actualizarEstado(int estadoActual,int evento);

    //Evento
    void datosAdquiridos();                                     // Falta
    QByteArray solicitarMensaje();
    void solicitarContacto();
    QByteArray agenda(int place);
    //void establecerContacto(QString name,int numero);

    QByteArray numeroAuxiliar;                                  // Aqui se almacenará el número en cuestión para su futura conversión a int

    void inicializarModulo(QString port);

private slots:
    void anteRecepcionMensaje();    // Verifica el mensaje como recepcion de mensaje o falsa alarma

signals:
    void actualizarAnteLlegada();
    void informeCorte();
    void moduloDespierto();

private:
    GUImodulo * moduloCentral;
    QByteArray mensajeActual;

    enum {comienzo,detectado_plus,detectadoC,detectadoM,detectadoG,detectadoR,detectadoNumero,verifAdqDatos};
    enum {null,plus,C,M,G,R,introNumero,simboloInicial};// Simbolo inicial !

    QByteArray numeroSubSistemas[MAX_SUBSISTEMAS];

    int transiciones[8][8]={{comienzo,detectado_plus,comienzo,comienzo,comienzo,comienzo,comienzo,comienzo},
                           {detectado_plus,comienzo,detectadoC,comienzo,comienzo,comienzo,comienzo,comienzo},
                           {detectadoC,comienzo,comienzo,detectadoM,comienzo,comienzo,comienzo,comienzo},
                           {detectadoM,comienzo,comienzo,comienzo,detectadoG,comienzo,comienzo,comienzo},
                           {detectadoG,comienzo,comienzo,comienzo,comienzo,detectadoR,comienzo,comienzo},
                           {detectadoR,detectadoR,detectadoR,detectadoR,detectadoR,detectadoR,detectadoNumero,detectadoR},
                           {detectadoNumero,verifAdqDatos,verifAdqDatos,verifAdqDatos,verifAdqDatos,verifAdqDatos,detectadoNumero,verifAdqDatos},
                           {verifAdqDatos,verifAdqDatos,verifAdqDatos,verifAdqDatos,verifAdqDatos,verifAdqDatos,verifAdqDatos,comienzo}};

    bool actualizar;
    int inicioMensaje;

// FUNCIONES AUXILIARES

    QByteArray reconstruirNumero(char digito);                  // Esta función junta los carácteres para obtener un único ByteArray con un número completo
    int obtenerNumero(QByteArray);                              // Realiza la conversión e inicializa a la variable numeroAuxiliar para ser utilizada en un momento futuro
    int estadoActual;
    int numeroAccionAutomata;
    void accionAutomata(int number,char current);

    int matrizDeteccionLugar[6][8]={{0,0,0,1,0,0,0,0},
                                   {0,0,0,2,0,0,0,0},
                                   {0,0,0,0,0,3,0,0},
                                   {0,0,0,0,4,0,0,0},
                                   {0,5,0,0,0,0,0,0},
                                   {5,5,5,5,5,5,5,5}};


    QByteArray numeroMensajeALeer;


};


#endif // GUICENTRAL_H
