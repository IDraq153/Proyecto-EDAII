#ifndef LECTOR_CSV_H
#define LECTOR_CSV_H

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class LectorCSV {
private:
    ifstream archivo;

public:
    bool abrirArchivo(string nombreArchivo);
    bool leerSiguienteAlerta(int& numero_alerta, int& numero_incidente, int& severidad);
    void cerrarArchivo();
};

#endif
