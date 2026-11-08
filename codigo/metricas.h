#ifndef METRICAS_H
#define METRICAS_H

struct Metricas {
    int sondeos_hash;
    int comparaciones_heap;
    int intercambios_heap;

    // Inicializar las variables a 0
    Metricas() : sondeos_hash(0), comparaciones_heap(0), intercambios_heap(0) {}

};

#endif // METRICAS_H