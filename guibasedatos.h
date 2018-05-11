#ifndef GUIBASEDATOS_H
#define GUIBASEDATOS_H

#include <QDialog>

#include <QSql>

#include <QSqlRelationalTableModel> // Al data
//#include <QSqlTableModel> // Al data
#include <QSortFilterProxyModel> // Aldata
#include <QSqlRecord>
#include <QSqlField>
#include <QModelIndex>

#include <QSqlQuery>

#include <basedatos.h>

#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class QTableView;
class QPushButton;
class QLabel;
class QLineEdit;
class QComboBox;

class GUIBaseDatos : public QDialog
{
    Q_OBJECT

public:
    GUIBaseDatos(QWidget *parent = 0);
    ~GUIBaseDatos();
    QSqlRelationalTableModel * misMediciones; // Al database
    QSqlRelationalTableModel * accesoMediciones;


private:
    BaseDatos * miBaseDatos;

    QLineEdit * miBusqueda;
    QLabel * miEtiquetaBusqueda;
    QLabel * miEtiquetaCombo;
    QTableView * miTablaMediciones;
    QPushButton * miBoton;
    QComboBox * miCombo;
};

#endif // GUIBASEDATOS_H
