#include <QApplication>

#include <inicioseguro.h>

#include <QDebug>
#include <QDir>

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication *myapp;
    myapp->addLibraryPath(QDir::currentPath());

    QApplication a(argc, argv);

    InicioSeguro inicio;
    inicio.show();

    return a.exec();
}
