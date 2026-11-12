#include <iostream>
#include "tablaHash.h"

TablaHash::TablaHash(int tamanoTabla, Metricas& metricas) {
    if (tamanoTabla < 1) tamanoTabla = 1;   // evita division entre cero
    this->tamanoTabla = tamanoTabla;
    this->cantidadIncidentes = 0;
    this->tablaIncidentes = new Incidente*[tamanoTabla];
    for (int i = 0; i < tamanoTabla; i++) {
        tablaIncidentes[i] = nullptr;
    }
    this->metricas = &metricas;
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
}

int TablaHash::funcionHash(const std::string& id) {
    // falta esto
    (void)id;
    return 0;
}

void TablaHash::registrarAlerta(const std::string& id, int severidad) {
    int posicion = funcionHash(id);
    Incidente* actual = tablaIncidentes[posicion];

    // Buscar en la lista de esa posicion falta eso
    // TODO (equipo): incrementar metricas->sondeos_hash segun la regla 
    // (por ejemplo, 1 por cada nodo examinado y 1 si la cubeta esta vacia).
    while (actual != nullptr) {
        if (actual->incidente_id == id) {
            actual->cantidad_alertas++;
            actual->prioridad_total += severidad;
            return;
        }
        actual = actual->siguiente;
    }

    // No existe incidente en la tabla hash
    Incidente* nuevo = new Incidente(id, severidad);
    nuevo->siguiente = tablaIncidentes[posicion];
    tablaIncidentes[posicion] = nuevo;
    cantidadIncidentes++;

    // TODO (equipo): si se supera el factor de carga, llamar a agrandarTabla() falta esto
}

int TablaHash::getCantidadIncidentes() const {
    return cantidadIncidentes;
}

// Copia los punteros de todos los incidentes al arreglo destino
// (destino debe tener espacio para getCantidadIncidentes() elementos).
int TablaHash::copiarIncidentes(Incidente** destino) const {
    int k = 0;
    for (int i = 0; i < tamanoTabla; i++) {
        Incidente* actual = tablaIncidentes[i];
        while (actual != nullptr) {
            destino[k++] = actual;
            actual = actual->siguiente;
        }
    }
    return k;
}
