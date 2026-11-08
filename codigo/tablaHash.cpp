#include <iostream>
#include "tablaHash.h"

TablaHash::TablaHash(int tamañoTabla) {
    this->tamañoTabla = tamañoTabla;
    this->cantidadIncidentes = 0;
    this->incidentes = new Incidente[tamañoTabla];
    this->metricas = new Metricas();
}

TablaHash::~TablaHash() {
    delete[] incidentes;
    delete metricas;
}
