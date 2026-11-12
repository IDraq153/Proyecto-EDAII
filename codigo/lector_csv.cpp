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
bool LectorCSV::leerSiguienteAlerta(string& alerta_id, string& incidente_id, int& severidad) {
    string linea;

    // Leer una fila (se saltan lineas vacias)
    do {
        if (!getline(archivo, linea)) {
            return false;
        }
        if (!linea.empty() && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
    } while (linea.empty());

    stringstream ss(linea);
    string campoSeveridad;

    // Leer alerta (se guarda como texto, no se convierte a numero)
    getline(ss, alerta_id, ',');

    // Leer incidente (CAMBIO: se mantiene como texto completo, ej. "INC-0000050")
    getline(ss, incidente_id, ',');

    // Leer severidad
    getline(ss, campoSeveridad, ',');
    severidad = stoi(campoSeveridad);
    return true;
}

// Cerrar archivo
void LectorCSV::cerrarArchivo() {
    archivo.close();
}
