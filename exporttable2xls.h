#ifndef EXPORTTABLE2XLS_H
#define EXPORTTABLE2XLS_H

//#include "ExcelFormat.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>
#include <QDateTime>
#include <time.h>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QSqlField>

//using namespace ExcelFormat;


class ExportTable2XLS
{
public:
    ExportTable2XLS();

    void exportarCSV();
    void exportarCSV(QSqlRelationalTableModel * miModelo);

private:
    // BasicExcel xls;

    QFile f;
    QString fileName;
    QString miFecha;
    QDateTime miTiempo;
    time_t miTiempoC;
};

#endif // EXPORTTABLE2XLS_H
