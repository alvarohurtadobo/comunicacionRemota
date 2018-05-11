#ifndef CONTROLBASEDATOS_H
#define CONTROLBASEDATOS_H

#include <QObject>
#include <basedatos.h>

#include <QSqlField>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QModelIndex>

#include <QDateTime>

class ControlBaseDatos : public QObject
{
    Q_OBJECT
public:
    explicit ControlBaseDatos(QObject *parent = 0);

    QSqlRelationalTableModel * getTabla();
    QSortFilterProxyModel * getFiltro();

    int obtenerIdentificador(long numero, int centralizador, int puerto);
    void actualizarLectura(int iden, bool state ,unsigned long pulsos);

    void crearMedidor(int iden);
    void crearMedidor(int iden,QString place, QString medidor, QString description, QString notes,bool state, unsigned long pulse, QString system, int central, int port);
    void actualizarMedidor();
    void borrarMedidor(int fila);
    void nuevosDatosSubSistema(unsigned long uno, unsigned long dos, unsigned long tres, unsigned long cuatro, unsigned long cinco, unsigned long seis, unsigned long siete, unsigned long ocho);

    void actualizarPotencias();

signals:
    void tablaActualizada();
    void paraEjecutar(bool action,QString centr,QString port);

public slots:
    void datosAlterados(QModelIndex antes,QModelIndex despues);


private:
    bool estadosMomentaneos[16];

    BaseDatos * miBaseDatos;
    QSqlRelationalTableModel * misMediciones;

    QSqlRecord miFila;
    QSqlField * miCampoID;
    QSqlField * miCampoUb;
    QSqlField * miCampoMe;
    QSqlField * miCampoDe;
    QSqlField * miCampoNo;
    QSqlField * miCampoEs;
    QSqlField * miCampoPo;
    QSqlField * miCampoN;
    QSqlField * miCampoSi;
    QSqlField * miCampoCe;
    QSqlField * miCampoPu;
    QSqlField * miCampoCr;
    QSqlField * miCampoFe;
    QSqlField * miCampoHo;

    int numeroMedidores;

    //FILTRADO
    QSortFilterProxyModel * miModeloFiltro;

    bool aActualizarPotencia;

};

#endif // CONTROLBASEDATOS_H
