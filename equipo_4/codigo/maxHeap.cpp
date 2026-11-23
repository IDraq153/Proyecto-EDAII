#include "maxHeap.h"
#include <iostream>
#include <utility>
using namespace std;

// Mayor prioridad gana; si empatan, gana el ID menor.
bool MaxHeap::esMayor(const Incidente* a, const Incidente* b) {
    metricas->comparaciones_heap++;
    if (a->prioridad_total != b->prioridad_total) {     
        return a->prioridad_total > b->prioridad_total;
    }
    return a->incidente_id < b->incidente_id;           
}

void MaxHeap::subir(int i) {
    while (i > 0) {
        int padre = (i - 1) / 2;
        if (esMayor(arreglo[i], arreglo[padre])) {
            swap(arreglo[i], arreglo[padre]);
            metricas->intercambios_heap++;
            i = padre;
        } else {
            break;                                   
        }
    }
}

// Se usa cuando queremos extraer el mayor, el cual es la raiz y queremos reacomodar el heap
void MaxHeap::bajar(int i) {
    while (i < cantidad) {
        int izq = 2 * i + 1;
        int der = 2 * i + 2;
        if (izq >= cantidad) {
            break;
        }
        if (der < cantidad) {
            int mejor; // Se usa para comparar cual de los hijos es mayor, o izquierda o derecha 
            if (esMayor(arreglo[izq], arreglo[der])) {
                mejor = izq;
            } else {
                mejor = der;
            }
            // En esta parte realizamos las comparaciones para poder acomodar el heap
            if (esMayor(arreglo[mejor], arreglo[i])) {
                swap(arreglo[mejor], arreglo[i]);
                i = mejor;
                metricas->intercambios_heap++;
            } else {
                break;
            }
        } else {
            if (esMayor(arreglo[izq], arreglo[i])) {
                swap(arreglo[izq], arreglo[i]);
                i = izq;
                metricas->intercambios_heap++;
            } else {
                break;
            }
        }
    }
}

MaxHeap::MaxHeap(int capacidad, Metricas& metricas) {
    this->capacidad = capacidad;
    this->metricas = &metricas;                         
    this->cantidad = 0;                                
    this->arreglo = new Incidente*[capacidad];          
}

MaxHeap::~MaxHeap() {
    delete[] arreglo;
}

void MaxHeap::insertar(Incidente* incidente) {          
    if (cantidad == capacidad) {
        cout << " El heap esta lleno " << endl;
        return;
    }
    arreglo[cantidad] = incidente;
    cantidad++;
    subir(cantidad - 1);                                
}

Incidente* MaxHeap::sacarMayor() {
    if (cantidad == 0) {                                
        return nullptr;
    }
    Incidente* mayor = arreglo[0];
    cantidad--;
    arreglo[0] = arreglo[cantidad];
    arreglo[cantidad] = nullptr;
    bajar(0);
    return mayor;
}

// verifica si mi arreglo esta vacio, para hacer las respectivas comparaciones
bool MaxHeap::estaVacio() const {                      
    return cantidad == 0;
}
