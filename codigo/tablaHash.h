#ifndef TABLAHASH_H
#define TABLAHASH_H
#include "metricas.h"
#include "incidente.h"

class TablaHash {
    private:
        Metricas* metricas;
        // incidentes es una tabla 
        Incidente* tablaIncidentes;
        // Tamaño
        int cantidadIncidentes;
        int tamañoTabla;

    public:
        TablaHash(int tamañoTabla);
        ~TablaHash();

        int funcionHash(int id);
        void registrarAlerta(int id, int severidad);
};

#endif // TABLAHASH_H