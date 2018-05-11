#ifndef SELECTORPUERTO_H
#define SELECTORPUERTO_H

#include <QWidget>
#include <sistemacontrol.h>

class QLabel;
class QPushButton;

class QListView;
class QComboBox;

class SelectorPuerto : public QWidget
{
    Q_OBJECT
public:
    explicit SelectorPuerto(QWidget *parent = 0);

signals:

public slots:
    void actualizarPuerto(int currentPort);
    void puertoSeleccionadoYEjecutar();

private:
    SistemaControl * miSistema;

    bool seleccionado;
    QLabel * miEtiqueta;
    QLabel *etiquetaPuertoSeleccionado;
    QLabel *puertoSeleccionado;
    QPushButton * botonCancelar;
    QPushButton * botonContinuar;
    QComboBox * miListaPuertos;

    QString misPuertos[12][3];
    QString puertoAMandar;
};

#endif // SELECTORPUERTO_H
