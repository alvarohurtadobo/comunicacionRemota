#ifndef SISTEMACONTROL_H
#define SISTEMACONTROL_H

#include <QObject>

// Interfaces gráficas
#include <interfazgrafica.h>
#include <guicentral.h>

// Librerias extra:
#include <exporttable2xls.h>
#include <controlbasedatos.h>

// Sistema
#include <sistemafisico.h>

class SistemaControl : public QObject
{
    Q_OBJECT
public:
    SistemaControl(QString port,QObject * parent = 0);
    SistemaFisico accederSistema();
    void cortarMedidor(int subSystem,int central,int controlElement);
    void establecerMedidor(int subSystem);
    void adquirirInformacion();
    bool guardarEstado();
    QString getContrasena();
    void setContrasena(QString pass);

// TRIALS NEXT STABLISH NEEDED FUNCTIONS
    int consultarSaldo(int subSystem,int central,int controlElement);

private slots:
    void arrancarGUIModem();
    void solicitarMediciones();
    void ejecutarCorteConexion();
    void actualizarAnteAlertaGUICentral();

    void actualizarTabla();
    void actualizarBusqueda(QString key);
    void exportar();
    void nuevaEjecucion(bool verificado,QString antes,QString despues);

    void anteNuevoNumero(QString number);
    void actualizarInformacionCorte();

    void anteRefrescoPontencias();
    void anteRefrescoModem();

    void anteModuloDespierto();

private:
    bool esperandoModem;
    InterfazGrafica * miPantallaControl;
    ControlBaseDatos miControl;
    GUICentral miCentral;
    ExportTable2XLS miExportador;

    SistemaFisico miSistema;
    QString contrasena;

    // Momentaneo
    QString numeroSubSistema;
    QString mensajeSolicitud;
};

#endif // SISTEMACONTROL_H
