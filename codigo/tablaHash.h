#ifndef TABLAHASH_H
#define TABLAHASH_H
#include "metricas.h"
#include "incidente.h"
#include "maxHeap.h"

class TablaHash {
private:
    Metricas* metricas;
    Incidente** tablaIncidentes;
    int cantidadIncidentes;
    int tamanoTabla;

public:
    TablaHash(int tamanoTabla);
    ~TablaHash();

    int funcionHash(int id);
    void registrarAlerta(int id, int severidad);
};
#endif // TABLAHASH_H