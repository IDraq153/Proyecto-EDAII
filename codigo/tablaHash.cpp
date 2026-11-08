#include <iostream>
#include "tablaHash.h"

TablaHash::TablaHash(int tamanoTabla) {
    this->tamanoTabla = tamanoTabla;
    this->cantidadIncidentes = 0;
    this->tablaIncidentes = new Incidente*[tamanoTabla];
    for (int i = 0; i < tamanoTabla; i++) {
        tablaIncidentes[i] = nullptr;
    }
    this->metricas = new Metricas();
}

TablaHash::~TablaHash() {
    for (int i = 0; i < tamanoTabla; i++) {
        Incidente* actual = tablaIncidentes[i];
        while (actual != nullptr) {
            Incidente* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
    }
    delete[] tablaIncidentes;
    delete metricas;
}

int TablaHash::funcionHash(int id) {
    return id % tamanoTabla;
}

void TablaHash::registrarAlerta(int id, int severidad) {
    int posicion = funcionHash(id);
    Incidente* actual = tablaIncidentes[posicion];

    // Buscar en la lista de esa posición
    while (actual != nullptr) {
        if (actual->incidente_id == id) {
            actual->cantidad_alertas++;
            actual->prioridad_total += severidad;
            return;
        }
        actual = actual->siguiente;
    }

    // No existe incidente en la tabla hash
    Incidente* nuevo = new Incidente;
    nuevo->incidente_id = id;
    nuevo->cantidad_alertas = 1;
    nuevo->prioridad_total = severidad;
    nuevo->siguiente = tablaIncidentes[posicion];
    tablaIncidentes[posicion] = nuevo;
    cantidadIncidentes++;
}