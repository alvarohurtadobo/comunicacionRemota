#ifndef INTERFAZGRAFICA_H
#define INTERFAZGRAFICA_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

#define MAX_EJE 16


// Se incluye la base de datos de solo una instancia
#include <basedatos.h>
#include <controlbasedatos.h>
#include <QDateTime>

// Se incluyen las clases de control de Base de datos
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QModelIndex>
#include <QModelIndex>

#include <QSqlQuery>
#include <QDir>

#include <QIcon>
#include <QSize>
#include <QPixmap>

//#include <guicorteconexion.h>

class QLabel;
class QLineEdit;
class QPushButton;

class QTableView;
class QComboBox;
class QTabWidget;

class InterfazGrafica : public QWidget
{
    Q_OBJECT

public:
    InterfazGrafica(QWidget *parent = 0);
    QLabel * obtenerLabelInformacion();
    void establecerVistaTabla(QSortFilterProxyModel * myTable);
    void actualizacionExitosa();
    QLabel *getRegistro();
    void actualizarNumerosCC(int data);

    int obtenerFaltantes();
    int obtenerSubsistema();

    QByteArray obtenerAccion(int posicion);
    QByteArray obtenerCentralizador(int posicion);
    QByteArray obtenerPuerto(int posicion);
    void ordenEjecutada();
    void setAlerta(QString miAlerta);


signals:
    void llamadoAModem();
    void llamadoACC();
    void solicitudDatos();
    void comandoFiltroCambiado(QString searchKey);
    void llamadaExportacion();

    void solicitudNuevoChip(QString);

    void numeroCeldaPresionada(int row);

    void ordenEjecutar();

    void emitRefrescoPotencias();
    void emitRefrescoModem();


private slots:
    void solicitudModemPresionado();
    void solicitudCC();
    void salirPresionado();
    void solicitarDatosPresionado();
    void solicitudExportarPresionado();
    void solicitudBusquedaCambiada(QString searchKey);
    void seleccionCelda(QModelIndex miDato);

    // SEGURIDAD
    void borrarIntentoContrasena();
    void ejecutarCambioContrasena();
    void borrarIntentoNumero();
    void ejecutarCambioNumero();

    //EJECUCION
    void ejecutarPresionado();
    void cancelarPresionado();

    void cortarPresionado();
    void establecerPresionado();


    void solicitudRefrescoPotencias();
    void solicitudRefrescoModem();


private:
    // Refresco
    QPushButton * refrescoModem;
    QPushButton * refrescoPotencias;

    // Alerta
    QLabel * etiquetaAlertas;
    QLabel * misAlertas;

// CONTROL CONTRASEÑA
    QString miContrasenaAuxiliar;

// MULTIMEDIA
    QIcon miIcono;
    QPixmap miImagenFondo1;
    QLabel * miFondoImagen1;
    QPixmap miImagenFondo2;
    QLabel * miFondoImagen2;
    QLabel * miFondoImagen3;
    QLabel * miFondoImagen4;
    QLabel * miFondoImagen5;
    QLabel * miFondoImagen6;

    QTabWidget *miParteSuperior;
    QWidget * miPantallaControl;
    QWidget * miPantallaSeguridad;
    QWidget * miPantallaInformacion;

//  SEGURIDAD
    QLabel * etiquetaTituloCambioContrasena;
    QLabel * etiquetaAdvertencia;
    QLabel * etiquetaAntiguaContrasena;
    QLabel * etiquetaConfirmarContrasena;
    QLabel * etiquetaNuevaContrasena;
    QLineEdit * entradaAntiguaContrasena;
    QLineEdit * entradaConfirmarContrasena;
    QLineEdit * entradaNuevaContrasena;
    QPushButton * botonEjecutarCambioContrasena;
    QPushButton * botonCancelarCambioContrasena;


    QLabel * etiquetaTituloCambioNumero;
    QLabel * etiquetaNuevoNumero;
    QLabel * etiquetaContrasenaActual;
    QPushButton * botonEjecutarCambioNumero;
    QPushButton * botonCancelarCambioNumero;
    QLineEdit * entradaContrasenaActual;
    QLineEdit * entradaNuevoNumero;



//  INFORMACIÓN
    QLabel * miEtiqueta;

//  GENERAL
    QLabel * miTitulo1;
    QLabel * miTitulo2;
    QLabel * miTitulo3;
    QLabel * miTitulo4;
    QLabel * registro;

    QLabel * etiquetaActualizacion;
    QLabel * ultimoTiempo;
    QLabel * etiquetaSubsistema;
    QLineEdit * numeroSistema;
    QPushButton * solicitarDatos;
    QPushButton * accederModemComunicacion;
    QPushButton * accederBaseDatos;
    QPushButton * accederSistemaActuacion;
    QPushButton * salir;
    QLabel * miInformacionActualizada;


// BASE DE DATOS MAS EJECUCION
    BaseDatos * miBaseDatos;

    QLineEdit * miBusqueda;
    QLabel * miEtiquetaBusqueda;
    QTableView * miTablaMediciones;

    QLabel * etiquetaSubSistemaCC;
    QLabel * etiquetaCentralizador;
    QLabel* etiquetaPuerto;

    QPushButton * botonCortar;
    QPushButton * botonEstablecer;

    QLineEdit * ingresoSubSistema;
    QLineEdit * ingresoCentralizador;
    QLineEdit * ingresoPuerto;

    QPushButton * botonEjecutar;
    QPushButton * botonCancelar;
    QPushButton * botonExportar;

    int faltantes;
    QByteArray accion[MAX_EJE];
    QByteArray locacion[MAX_EJE][2];
};

#endif // INTERFAZGRAFICA_H

