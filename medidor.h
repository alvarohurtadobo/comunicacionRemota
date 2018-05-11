#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <string>

using namespace std;

class Medidor
{
public:
    Medidor();
    void setNombre(string nombreNuevo);
    string getNombre();
    void setCodigo(int nuevoCodigo);
    int getCodigo();
    void NuevoPulso();
    void setContador(int contadorNuevo);
    int getContador();
    void setEnergia(double energiaNueva);
    double getEnergia();
    void arruinado();
    void funcional();
    bool getEstado();
    void setTamanoPasoKe(double stepKe);
    double getTamanopasoKe();

private:
    string nombre;
    string marca;
    string modelo;
    string carga;
    string descripcion;
    int contador;
    double energia_Wh;
    bool estado;
    double tamanoDePasoKe;
};

#endif // MEDIDOR_H
