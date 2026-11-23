#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <string>
#include "metricas.h"
#include "incidente.h"

class TablaHash {
private:
    Metricas* metricas;            
    Incidente** tablaIncidentes; // lista enlazada apuntamos a direcciones que apuntan a incidentes
    int cantidadIncidentes;
    int tamanoTabla;

public:
    TablaHash(int tamanoTabla, Metricas* metricas);
    ~TablaHash();

    int funcionHash(const std::string& id);             
    void registrarAlerta(const std::string& id, int severidad);

    int getCantidadIncidentes() const;                  
    void copiarIncidentes(Incidente** destino) const;    

    void redimensionar();
};

#endif // TABLAHASH_H
