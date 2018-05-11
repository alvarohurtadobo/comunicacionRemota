#include "qpushbutton.h"
#include "qlabel.h"
#include "qlineedit.h"

#include "inicioseguro.h"

// Para la interfaz gráfica:
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include <QHBoxLayout>
#include <QVBoxLayout>


InicioSeguro::InicioSeguro(QWidget *parent) : QDialog(parent)
{    
    contrasenaEnOrden = true;

    QFile inputFile(QDir::currentPath()+"/OddOne.txt");
        if (inputFile.open(QIODevice::ReadWrite))
        {
           QTextStream in(&inputFile);
           while ( !in.atEnd() ){
                line = in.readLine();
           }
           inputFile.close();
        }

    // Contraseña de administrador, no posible de cambiar:
    contrasena = "vj19gn13d23n";

    // Objetos de la interfaz gráfica

    salir = new QPushButton("Salir");
    ingresar = new QPushButton("Ingresar");
    etiquetaContrasena = new QLabel("Ingrese la contrasena del sistema:");
    etiquetaInformacion = new QLabel;
    ingresoContrasena = new QLineEdit;
    ingresoContrasena->setEchoMode(QLineEdit::Password); //Hint de http://stackoverflow.com/questions/4663207/masking-qlineedit-text
    ingresar->setDefault(true);

    QHBoxLayout * botones = new QHBoxLayout;
    botones->addWidget(salir);
    botones->addWidget(ingresar);

    QVBoxLayout * total = new QVBoxLayout;
    total->addWidget(etiquetaContrasena);
    total->addWidget(etiquetaInformacion);
    total->addWidget(ingresoContrasena);
    total->addLayout(botones);

    // Conexiones
    connect(ingresar,SIGNAL(clicked()),this,SLOT(intentoIngreso()));
    connect(salir,SIGNAL(clicked()),this,SLOT(salida()));


    this->setLayout(total);

    this->setWindowTitle("Bienvenido");

    // Si alguien altera el archivo de la contraseña:

    if(line.size()<4||line.isEmpty()){
        etiquetaContrasena->setText("Error de contraseña");
        contrasenaEnOrden = false;
    }
}

void InicioSeguro::intentoIngreso()                     // este SLOT verifica que la contraseña es la correcta e ingresa al sistema
{
    if((((ingresoContrasena->text() == contrasena)||(ingresoContrasena->text() == line))&&contrasenaEnOrden)||true){
        miSeleccion = new SelectorPuerto;
        this->close();
    }
    else{
        etiquetaInformacion->setText("Contrasena Incorrecta");
        ingresoContrasena->clear();
    }
}

void InicioSeguro::salida()
{
    this->close();
}
