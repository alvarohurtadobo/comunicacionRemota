#-------------------------------------------------
#
# Project created by QtCreator 2014-12-12T11:40:02
#
#-------------------------------------------------

QT       += core gui serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = comunicacionRemota
TEMPLATE = app

SOURCES += main.cpp\
    medidor.cpp \
    elementocontrol.cpp \
    centralizador.cpp \
    sistemafisico.cpp \
    sistemacontrol.cpp \
    interfazgrafica.cpp \
    guimodulo.cpp \
    basedatos.cpp \
    inicioseguro.cpp \
    guicentral.cpp \
    controlbasedatos.cpp \
    exporttable2xls.cpp \
    selectorpuerto.cpp \
    actuador.cpp

HEADERS  += medidor.h \
    elementocontrol.h \
    centralizador.h \
    sistemafisico.h \
    sistemacontrol.h \
    interfazgrafica.h \
    guimodulo.h \
    basedatos.h \
    inicioseguro.h \
    guicentral.h \
    controlbasedatos.h \
    exporttable2xls.h \
    selectorpuerto.h \
    actuador.h

CONFIG       += serialport
