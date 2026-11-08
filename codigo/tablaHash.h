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
        TablaHash(int tamañoTabla) {
            this->tamañoTabla = tamañoTabla;
        }
        ~TablaHash();

        void registrarAlerta() {
                
        }

};

#endif // TABLAHASH_H