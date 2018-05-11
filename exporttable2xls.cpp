#include "exporttable2xls.h"

ExportTable2XLS::ExportTable2XLS()
{
    //e = new BasicExcel;
    // xls.New(1);

    f.setFileName(fileName);
    f.open(QFile::WriteOnly);
    f.close();

    miTiempo = QDateTime::currentDateTime();
}

void ExportTable2XLS::exportarCSV()
{
    QFile miArchivoTemporal;
    fileName.clear();                                       // Se asegura que el nombre este vacio para empezar

    fileName = "trial_";                                    // Nombre principal
    fileName.append(QDateTime::currentDateTime().toString("dd.MMMM.yyyy_hh.mm.ss"));            // Se introduce el formato

    fileName.append(".csv");                                // La extensión

    miArchivoTemporal.setFileName(fileName);
    if (miArchivoTemporal.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data( &miArchivoTemporal );
        QStringList strList;

        for( int r = 0; r < 10; ++r )
        {
            strList.clear();
            for( int c = 0; c < 8; ++c )
            {
                strList <<QString::number(r+c+100);
            }
            data << strList.join( ";" )+"\n";
        }
        miArchivoTemporal.close();
    }
}

void ExportTable2XLS::exportarCSV(QSqlRelationalTableModel *miModelo)
{
    QFile miArchivoTemporal;
    fileName.clear();                                       // Se asegura que el nombre este vacio para empezar

    fileName = QDir::currentPath()+"/datosExportados/export_";                                   // Nombre principal
    fileName.append(QDateTime::currentDateTime().toString("dd.MMMM.yyyy_hh.mm.ss"));            // Se introduce el formato

    fileName.append(".csv");                                // La extensión

    miArchivoTemporal.setFileName(fileName);
    if (miArchivoTemporal.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data( &miArchivoTemporal );
        QStringList strList;

        strList << "ID" << "UBICACION" << "MEDIDOR" << "DESCRIPCION" << "NOTAS" << "ESTADO" << "POTENCIA" << "N PULSOS" << "SISTEMA" << "CENTRALIZADOR" << "PUERTO" << "CREACION" << "FECHA MODIFICACION" << "FECHA CREACION";
        data << strList.join( "\t" )+"\n";

        for( int r = 0; r < miModelo->rowCount(); ++r )
        {
            strList.clear();
            for( int c = 0; c < miModelo->columnCount(); ++c )
            {
                strList << miModelo->record(r).field(c).value().toString();
            }
            data << strList.join( "\t" )+"\n";
        }
        miArchivoTemporal.close();
    }
}
