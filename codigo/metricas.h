#ifndef METRICAS_H
#define METRICAS_H

struct Metricas {
    long long sondeos_hash;        // CAMBIO: long long para archivos grandes
    long long comparaciones_heap;
    long long intercambios_heap;
    double tiempo_proceso_ms;      // NUEVO: lo pide metricas.txt

    // Inicializar las variables a 0
    Metricas() : sondeos_hash(0), comparaciones_heap(0), intercambios_heap(0), tiempo_proceso_ms(0.0) {}
};

#endif // METRICAS_H
