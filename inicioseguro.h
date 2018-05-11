#ifndef INICIOSEGURO_H
#define INICIOSEGURO_H

#include <QDialog>

// Para el acceso a la contraseña:
#include <QFile>
#include <QTextStream>
#include <QDir>

// Para arrancar el selector de puerto
#include <selectorpuerto.h>

class QPushButton;
class QLabel;
class QLineEdit;

class InicioSeguro : public QDialog
{
    Q_OBJECT
public:
    explicit InicioSeguro(QWidget *parent = 0);

public slots:
    void intentoIngreso();
    void salida();

private:
    QPushButton * ingresar;
    QPushButton * salir;
    QLabel * etiquetaContrasena;
    QLabel * etiquetaInformacion;
    QLineEdit * ingresoContrasena;

    SelectorPuerto * miSeleccion;

    QString contrasena;

    QString line;

    bool contrasenaEnOrden;

    //QFile pass;
};

#endif // INICIOSEGURO_H
