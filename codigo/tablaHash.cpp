#include <iostream>
#include "tablaHash.h"

TablaHash::TablaHash(int tamañoTabla) {
    this->tamañoTabla = tamañoTabla;
    this->cantidadIncidentes = 0;
    this->tablaIncidentes = new Incidente[tamañoTabla];
    this->metricas = new Metricas();
}

TablaHash::~TablaHash() {
    delete[] tablaIncidentes;
    delete metricas;
}
int TablaHash::funcionHash(int id) {
    return id % tamañoTabla;     
}
// Incidente es como un nodo
void TablaHash::registrarAlerta(int id, int severidad) {
    Incidente* actual;
    int posicion = funcionHash(id);

}
