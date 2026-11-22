#include <iostream>
#include "tablaHash.h"

TablaHash::TablaHash(int tamanoTabla, Metricas* metricas) {
    if (tamanoTabla < 1) tamanoTabla = 1;   // evita division entre cero
    this->tamanoTabla = tamanoTabla;
    this->cantidadIncidentes = 0;
    this->tablaIncidentes = new Incidente*[tamanoTabla]; //  lista enlazada
    for (int i = 0; i < tamanoTabla; i++) {
        tablaIncidentes[i] = nullptr;
    }
    this->metricas = metricas;
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
    int valor = std::stoi(id.substr(4));
    return valor % tamanoTabla;
}

void TablaHash::registrarAlerta(const std::string& id, int severidad) {
    int posicion = funcionHash(id);
    Incidente* actual = tablaIncidentes[posicion];

    // Buscar en la lista de esa posicion falta eso
    while (actual != nullptr) {
        metricas->sondeos_hash++;

        // si es el mismo incidente no creara otro solo se sumara a el
        if (actual->incidente_id == id) {
            actual->cantidad_alertas++;
            actual->prioridad_total += severidad;
            return;
        }
        actual = actual->siguiente; // vamos iterando en la lista enlazada
    }

    // No existe incidente en la tabla hash
    Incidente* nuevo = new Incidente(id, severidad);
    // se agrega al inicio
    nuevo->siguiente = tablaIncidentes[posicion];
    tablaIncidentes[posicion] = nuevo;
    cantidadIncidentes++;

    //Si el factor de carga llego a 75% o mas redimensionar tabla
    if ((float)cantidadIncidentes / tamanoTabla >= 0.75f) {
        redimensionar();
    }

}

int TablaHash::getCantidadIncidentes() const {
    return cantidadIncidentes;
}

// Copia los punteros de todos los incidentes al arreglo destino
// (destino debe tener espacio para getCantidadIncidentes() elementos).
void TablaHash::copiarIncidentes(Incidente** destino) const {
    int k = 0;
    for (int i = 0; i < tamanoTabla; i++) {
        Incidente* actual = tablaIncidentes[i];
        while (actual != nullptr) {
            destino[k++] = actual;
            actual = actual->siguiente;
        }
    }
}

void TablaHash::redimensionar() {
    //Guardar en variables aux la tabla anterior y su tamaño
    int tamanoAnterior = tamanoTabla;
    Incidente** tablaAnterior = tablaIncidentes;

    //Crear nueva tabla con tamaño duplciado
    tamanoTabla = tamanoAnterior * 2;
    tablaIncidentes = new Incidente*[tamanoTabla];

    //Poner toda la nueva tabla en nullptr
    for (int i = 0; i < tamanoTabla; i++) {
        tablaIncidentes[i] = nullptr;
    }
    //Por cada posicion de la tabla anterior
    for (int i = 0; i < tamanoAnterior; i++){
        //Elemento en la posicion i
        Incidente* actual = tablaAnterior[i];
        while (actual != nullptr){
            Incidente* sig = actual->siguiente;
            int nuevaPosicion = funcionHash(actual->incidente_id);
            //El siguiente del incidente actual va a ser el que se encuentra en frente en la posicion indicada de la tabla nueva
            actual->siguiente = tablaIncidentes[nuevaPosicion];
            //Actualiza el casillero de la nueva tbala con el incidente actual
            tablaIncidentes[nuevaPosicion] = actual;

            if (metricas != nullptr) {
                metricas->sondeos_hash++;
            }

            actual = sig;
        }
    }

    delete[] tablaAnterior;
}