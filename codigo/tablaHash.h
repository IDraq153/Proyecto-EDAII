#ifndef TABLAHASH_H
#define TABLAHASH_H
#include "metricas.h"
#include "incidente.h"

class TablaHash {
    private:
        Metricas* metricas;
        Incidente* incidentes;
        int cantidadIncidentes;
        int tamañoTabla;

    public:
        TablaHash(int tamañoTabla);
        ~TablaHash();

        void registrarAlerta(int id, int severidad);
};

#endif // TABLAHASH_H