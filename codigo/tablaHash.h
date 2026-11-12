#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <string>
#include "metricas.h"
#include "incidente.h"

class TablaHash {
private:
    Metricas* metricas;            // CAMBIO: apunta a las metricas de main (antes creaba las suyas
                                   // y los contadores nunca llegaban a metricas.txt)
    Incidente** tablaIncidentes;
    int cantidadIncidentes;
    int tamanoTabla;

public:
    TablaHash(int tamanoTabla, Metricas& metricas);
    ~TablaHash();

    int funcionHash(const std::string& id);              // CAMBIO: recibe string
    void registrarAlerta(const std::string& id, int severidad);

    int getCantidadIncidentes() const;                   // NUEVO
    int copiarIncidentes(Incidente** destino) const;     // NUEVO: "recorrer todos los incidentes" (README)

    // TODO (equipo): void agrandarTabla();  -> rehash cuando cantidadIncidentes supere el factor de carga
};

#endif // TABLAHASH_H
