#ifndef GUICORTECONEXION_H
#define GUICORTECONEXION_H

#include <QDialog>

#include <QHBoxLayout>
#include <QVBoxLayout>

// Considerando un caracter de comando, uno de accion, dos de localizacion y cuatro de contraseña (8byte) en 160 caracteres resulta en un maximo de 20:
#define MAX_EJE 20

class QLineEdit;
class QLabel;
class QPushButton;

class GUICorteConexion : public QDialog
{
    Q_OBJECT

public:
    GUICorteConexion(QWidget * parent=0);
    int obtenerFaltantes();
    int obtenerSubsistema();

    QByteArray obtenerAccion(int posicion);
    QByteArray obtenerCentralizador(int posicion);
    QByteArray obtenerPuerto(int posicion);
    void ordenEjecutada();
    QHBoxLayout * robarVista();     // Tricky


signals:
    void ordenEjecutar();

private slots:
    void cortarPresionado();
    void establecerPresionado();
    void ejecutarPresionado();
    void cancelarPresionado();

private:
    QHBoxLayout * total;            // Tricky

    //QLabel * etiquetaCodigo;
    QLabel * etiquetaSubSistema;
    QLabel * etiquetaCentralizador;
    QLabel* etiquetaPuerto;
    QLabel * etiRegistro;

    QLineEdit * ingresoSubSistema;
    QLineEdit * ingresoCentralizador;
    QLineEdit * ingresoPuerto;

    QPushButton * botonCortar;
    QPushButton * botonEstablecer;
    QPushButton * botonEjecutar;
    QPushButton * botonCancelar;

    int faltantes;
    QByteArray accion[MAX_EJE];
    QByteArray locacion[MAX_EJE][2];
};

#endif // GUICORTECONEXION_H
