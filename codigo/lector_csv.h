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
    // CAMBIO: los IDs se devuelven como string (antes int con stoi)
    bool leerSiguienteAlerta(string& alerta_id, string& incidente_id, int& severidad);
    void cerrarArchivo();
};

#endif
