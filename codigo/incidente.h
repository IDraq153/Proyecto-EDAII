#ifndef INCIDENTE_H
#define INCIDENTE_H

#include <string>

struct Incidente {
    std::string incidente_id;
    int cantidad_alertas;
    int prioridad_total;
    Incidente* siguiente;

    // Constructor por defecto
    Incidente() 
        : incidente_id(""), cantidad_alertas(0), prioridad_total(0), siguiente(nullptr) {}

    // Constructor para inicializar un nuevo incidente con su primera alerta
    Incidente(const std::string& id, int severidad_inicial) 
        : incidente_id(id), cantidad_alertas(1), prioridad_total(severidad_inicial), siguiente(nullptr) {}

    // Constructor parametrizado completo (util para transferir datos al Heap)
    Incidente(const std::string& id, int alertas, int prioridad)
        : incidente_id(id), cantidad_alertas(alertas), prioridad_total(prioridad), siguiente(nullptr) {}
};


#endif // INCIDENTE_H