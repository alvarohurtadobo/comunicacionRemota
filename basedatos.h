#ifndef BASEDATOS_H
#define BASEDATOS_H

#include <QObject>
#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>

//#include <QSqlRelationalTableModel> // Del
//#include <QSortFilterProxyModel> // Del

class BaseDatos : public QObject
{
    Q_OBJECT
public:
    explicit BaseDatos(QObject *parent = 0);

    static BaseDatos *estaBase;
    static BaseDatos *accederEstaBase();

    static QSqlDatabase miBase;
    static QSqlDatabase accederBaseDatos();

    //QSqlRelationalTableModel * misMediciones; //Del nop
    //QSqlRelationalTableModel * obtenerDatos(); //Del nop

public slots:

signals:


};

#endif // BASEDATOS_H
