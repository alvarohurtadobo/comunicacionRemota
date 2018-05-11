#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDebug>

#include "guibasedatos.h"

GUIBaseDatos::GUIBaseDatos(QWidget * parent) : QDialog(parent)
{
// Se inicializa el modelo de la base de datos:
    // Al data:
    misMediciones = new QSqlRelationalTableModel(this,BaseDatos::miBase);
    misMediciones->setTable("private");
    misMediciones->select();


    /*QModelIndex miNuevaFila;
    miNuevaFila.child(4,0);*/


    // misMediciones->insertRow(misMediciones->rowCount(),miNuevaFila);

    // Prueba Record
    QSqlRecord miFila;

    QSqlField miCampo("ID", QVariant::Int);
    QSqlField miCampo2("Codigo",QVariant::Int);
    QSqlField miCampo3("Precio",QVariant::Int);

    miCampo.setValue(QString("16"));
    miCampo2.setValue(QString("111111"));
    miCampo3.setValue(QString("9999"));

    miFila.append(miCampo);
    miFila.append(miCampo2);
    miFila.append(miCampo3);

    misMediciones->insertRecord(-1,miFila);

    //QDebug() << misMediciones->lastError();

// Se crean los objetos
    miBusqueda = new QLineEdit;
    miEtiquetaBusqueda = new QLabel("Buscar: ");
    miEtiquetaCombo = new QLabel("Filtrar por: ");
    miBoton = new QPushButton("Buscar");
    miTablaMediciones = new QTableView;
    miCombo = new QComboBox;

// Se organizan los objetos
    QHBoxLayout * opciones = new QHBoxLayout;
    opciones->addWidget(miEtiquetaBusqueda);
    opciones->addWidget(miBusqueda);
    opciones->addWidget(miEtiquetaCombo);
    opciones->addWidget(miCombo);

    QVBoxLayout * total = new QVBoxLayout;
    total->addLayout(opciones);
    total->addWidget(miTablaMediciones);
    total->addWidget(miBoton);

// Se asigna la tabla y se establece su tamaño:
    miTablaMediciones->setModel(misMediciones);// Al database
    miTablaMediciones->setColumnWidth(0,25);//Aldatabas
    // miTablaMediciones->setModel(miBaseDatos->obtenerDatos()); // Del
    //misMediciones->insertRow(5,QMoldelIndex)

    this->setLayout(total);

    this->setWindowTitle("Base de Datos");
}

GUIBaseDatos::~GUIBaseDatos()
{

}
