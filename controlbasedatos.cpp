#include "controlbasedatos.h"

ControlBaseDatos::ControlBaseDatos(QObject *parent) :
    QObject(parent)
{
    aActualizarPotencia= true;

    numeroMedidores = 0;

    misMediciones = new QSqlRelationalTableModel(this,BaseDatos::miBase);
    misMediciones->setTable("mediciones");
    misMediciones->select();

    miCampoID = new QSqlField("ID",QVariant::Int);
    miCampoUb = new QSqlField("Ubicación",QVariant::String);
    miCampoMe = new QSqlField("Medidor",QVariant::String);
    miCampoDe = new QSqlField("Descripción", QVariant::String);
    miCampoNo = new QSqlField("Notas",QVariant::String);
    miCampoEs = new QSqlField("Estado",QVariant::String);
    miCampoPo = new QSqlField("Potencia",QVariant::Double);
    miCampoN = new QSqlField("Nº Pulsos", QVariant::ULongLong);
    miCampoSi = new QSqlField("Sistema",QVariant::String);
    miCampoCe = new QSqlField("Centralizador",QVariant::Int);
    miCampoPu = new QSqlField("Puerto", QVariant::Int);
    miCampoCr = new QSqlField("Creación",QVariant::Date);
    miCampoFe = new QSqlField("Fecha Modificación",QVariant::Date);
    miCampoHo = new QSqlField("Hora Modificación", QVariant::Date);

    for(int i = 0; i<16; i++)
        estadosMomentaneos[i] = true;
    //connect(misMediciones,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(actualizarPotencias(QModelIndex topLeft,QModelIndex bottomRight)));


// OPCIONES DE FILTRADO
    miModeloFiltro = new QSortFilterProxyModel(this);
    miModeloFiltro->setSourceModel(misMediciones);
    miModeloFiltro->setFilterCaseSensitivity(Qt::CaseInsensitive);
    miModeloFiltro->setFilterKeyColumn(-1);
}

QSqlRelationalTableModel *ControlBaseDatos::getTabla()
{
    return misMediciones;
}

QSortFilterProxyModel *ControlBaseDatos::getFiltro()
{
    return miModeloFiltro;
}

void ControlBaseDatos::actualizarPotencias()
{
    for(int i = 0; i<16;i++)
    {
        double tamanoPulso = misMediciones->record(i).field("Ke").value().toDouble();
        double pulsos = misMediciones->record(i).field("Nº Pulsos").value().toDouble();
        // La potencia estará en kWh por defecto:
        double potenciaReal = tamanoPulso*(double)pulsos/1000;
        miCampoPo->setValue(QString::number(potenciaReal));
        miFila.clear();
        miFila.append(*miCampoPo);

        miCampoID->setValue(misMediciones->record(i).field("ID").value());
        miCampoUb->setValue(misMediciones->record(i).field("Ubicación").value());
        miCampoMe->setValue(misMediciones->record(i).field("Medidor").value());
        miCampoDe->setValue(misMediciones->record(i).field("Descripción").value());
        miCampoNo->setValue(misMediciones->record(i).field("Notas").value());
        miCampoEs->setValue(misMediciones->record(i).field("Estado").value());
        miCampoN->setValue(misMediciones->record(i).field("Nº Pulsos").value());
        miCampoSi->setValue(misMediciones->record(i).field("Sistema").value());
        miCampoCe->setValue(misMediciones->record(i).field("Centralizador").value());
        miCampoPu->setValue(misMediciones->record(i).field("Puerto").value());
        miCampoCr->setValue(misMediciones->record(i).field("Creación").value());
        miCampoFe->setValue(misMediciones->record(i).field("Fecha Modificación").value());
        miCampoHo->setValue(misMediciones->record(i).field("Hora Modificación").value());

        miFila.append(*miCampoID);
        miFila.append(*miCampoUb);
        miFila.append(*miCampoMe);
        miFila.append(*miCampoDe);
        miFila.append(*miCampoNo);
        miFila.append(*miCampoEs);
        miFila.append(*miCampoN);
        miFila.append(*miCampoSi);
        miFila.append(*miCampoCe);
        miFila.append(*miCampoPu);
        miFila.append(*miCampoCr);
        miFila.append(*miCampoFe);
        miFila.append(*miCampoHo);

        misMediciones->setRecord(i,miFila);
    }
}

void ControlBaseDatos::actualizarLectura(int iden, bool state, unsigned long pulsos)
{
    miCampoN->setValue(QString::number(pulsos));
    if(state)
        miCampoEs->setValue("Con Suministro");
    else
        miCampoEs->setValue("Sin Suministro");

    double tamanoPulso = misMediciones->record(iden).field("Ke").value().toDouble();
    double potenciaReal = tamanoPulso*(double)pulsos;

    miCampoPo->setValue(QString::number(potenciaReal));
    //miCampoFe = new QSqlField("Fecha Modificación",QVariant::Date);
    miCampoFe->setValue(QDateTime::currentDateTime().date().toString("dd-MMMM-yy"));

    //miCampoHo = new QSqlField("Hora Modificación", QVariant::Date);
    miCampoHo->setValue(QDateTime::currentDateTime().time().toString("hh:mm:ss"));

    if(iden<8)
    {
        miCampoPu->setValue(QString::number(iden));
        miCampoCe->setValue(QString::number(0));
    }
    else
    {
        miCampoPu->setValue(QString::number(iden-8));
        miCampoCe->setValue(QString::number(1));
    }

    miFila.clear();
    miFila.append(*miCampoN);
    miFila.append(*miCampoFe);
    miFila.append(*miCampoHo);
    miFila.append(*miCampoPo);
    miFila.append(*miCampoEs);
    miFila.append(*miCampoCe);
    miFila.append(*miCampoPu);

    misMediciones->setRecord(iden,miFila);

    emit tablaActualizada();
}

void ControlBaseDatos::crearMedidor(int iden, QString place, QString medidor, QString description, QString notes, bool state, unsigned long pulse, QString system, int central, int port)
{
// Se obtiene el valor de la potencia en base al número de pulsos, en kWh:
    double potencia = 1.25*(double)pulse/1000.0;
    miCampoID->setValue(QString::number(iden));
    miCampoUb->setValue(QString(place));
    miCampoMe->setValue(QString(medidor));
    miCampoDe->setValue(QString(description));
    miCampoNo->setValue(QString(notes));
    miCampoEs->setValue(QString::number(state));
    miCampoPo->setValue(potencia);
    miCampoN->setValue(QString::number(pulse));
    miCampoSi->setValue(QString(system));
    miCampoCe->setValue(QString::number(central));
    miCampoPu->setValue(QString::number(port));
    miCampoCr->setValue(QDateTime::currentDateTime().toString());
    miCampoFe->setValue(QDateTime::currentDateTime().date().toString());
    miCampoHo->setValue(QDateTime::currentDateTime().time().toString());

// SE VACIA LA FILA ANTES DE ADJUNTAR LOS VALORES
    miFila.clear();
    miFila.append(*miCampoID);
    miFila.append(*miCampoUb);
    miFila.append(*miCampoMe);
    miFila.append(*miCampoDe);
    miFila.append(*miCampoNo);
    miFila.append(*miCampoEs);
    miFila.append(*miCampoPo);
    miFila.append(*miCampoN);
    miFila.append(*miCampoSi);
    miFila.append(*miCampoCe);
    miFila.append(*miCampoPu);
    miFila.append(*miCampoCr);
    miFila.append(*miCampoFe);
    miFila.append(*miCampoHo);

    misMediciones->insertRecord(iden,miFila);

    emit tablaActualizada();
}

void ControlBaseDatos::borrarMedidor(int fila)
{
    misMediciones->removeRow(fila);
}

void ControlBaseDatos::nuevosDatosSubSistema(unsigned long uno, unsigned long dos, unsigned long tres, unsigned long cuatro, unsigned long cinco, unsigned long seis, unsigned long siete, unsigned long ocho)
{

}

void ControlBaseDatos::datosAlterados(QModelIndex antes, QModelIndex despues)
{
    /*bool igual = false;
    if((antes.column()==despues.column())&&(antes.row()==despues.row()))
        igual = true;
    emit paraEjecutar(igual,antes.data().toString(),despues.data().toString());*/
}

