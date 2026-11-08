#include "lector_csv.h"

// Abrir archivo
bool LectorCSV::abrirArchivo(string nombreArchivo) {
    archivo.open(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return false;
    }

    string linea;

    // Saltar encabezados
    getline(archivo, linea);

    return true;
}

// Leer siguiente alerta
bool LectorCSV::leerSiguienteAlerta(int& numero_alerta, int& numero_incidente, int& severidad) {
    string linea;
    string alerta_id, incidente_id;

    // Leer una fila
    if (!getline(archivo, linea)) {
        return false;
    }

    stringstream ss(linea);

    // Leer alerta
    getline(ss, alerta_id, ',');
    numero_alerta = stoi(alerta_id.substr(1));

    // Leer incidente
    getline(ss, incidente_id, ',');
    numero_incidente = stoi(incidente_id.substr(4));

    // Leer severidad
    ss >> severidad;

    return true;
}

// Cerrar archivo
void LectorCSV::cerrarArchivo() {
    archivo.close();
}
