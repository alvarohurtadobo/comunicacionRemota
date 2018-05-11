#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "basedatos.h"
#include "QDir"

QSqlDatabase BaseDatos::miBase = QSqlDatabase::addDatabase("QSQLITE");
BaseDatos *BaseDatos::estaBase = new BaseDatos;

BaseDatos::BaseDatos(QObject *parent) : QObject(parent) // QW y QDialog
{
    miBase.setDatabaseName(QDir::currentPath()+"/datoMedidas");
    if(miBase.open()){
        qDebug() << "Conectado --->" + miBase.databaseName()+"<--";
    }
    else{
        qDebug() << "No se conecto";
    }

    /*misMediciones = new QSqlRelationalTableModel(this,BaseDatos::miBase);
    misMediciones->setTable("sqlMediciones");
    misMediciones->select();*/ //Del
}

BaseDatos *BaseDatos::accederEstaBase()
{
    if(!estaBase){
        estaBase = new BaseDatos();
    }
    return estaBase;
}

QSqlDatabase BaseDatos::accederBaseDatos()
{
    return miBase;
}

/*QSqlRelationalTableModel *BaseDatos::obtenerDatos() // Nop
{
    return misMediciones;
}*/

