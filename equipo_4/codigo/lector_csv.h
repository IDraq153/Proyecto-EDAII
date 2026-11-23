#ifndef LECTOR_CSV_H
#define LECTOR_CSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class LectorCSV {
private:
    ifstream archivo;

public:
    bool abrirArchivo(string nombreArchivo);
    bool leerSiguienteAlerta(string& alerta_id, string& incidente_id, int& severidad);
    void cerrarArchivo();
};

#endif
