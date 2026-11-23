#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "incidente.h"
#include "metricas.h"

class MaxHeap {
private:
    Incidente** arreglo;   // guarda punteros: un intercambio mueve un puntero, no un string
    int capacidad;
    int cantidad;
    Metricas* metricas;

    void subir(int i);
    void bajar(int i);
    bool esMayor(const Incidente* a, const Incidente* b);  // mayor prioridad gana; si empatan, gana el ID menor

public:
    MaxHeap(int capacidad, Metricas& metricas);
    ~MaxHeap();

    void insertar(Incidente* incidente);
    Incidente* sacarMayor();
    bool estaVacio() const;
};

#endif // MAXHEAP_H
