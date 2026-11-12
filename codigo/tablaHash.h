#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <string>
#include "metricas.h"
#include "incidente.h"

class TablaHash {
private:
    Metricas* metricas;            
    Incidente** tablaIncidentes;
    int cantidadIncidentes;
    int tamanoTabla;

public:
    TablaHash(int tamanoTabla, Metricas& metricas);
    ~TablaHash();

    int funcionHash(const std::string& id);             
    void registrarAlerta(const std::string& id, int severidad);

    int getCantidadIncidentes() const;                  
    int copiarIncidentes(Incidente** destino) const;    

    // TODO (equipo): void agrandarTabla();  -> rehash cuando cantidadIncidentes supere el factor de carga
};

#endif // TABLAHASH_H
