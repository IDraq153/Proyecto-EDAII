#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream archivo("40data.csv");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    string linea;
    string alerta_id, incidente_id;
    int severidad;

    // Saltar la primera fila (encabezados)
    getline(archivo, linea);

    // Leer cada fila
    while (getline(archivo, linea)) {
        stringstream ss(linea);

        getline(ss, alerta_id, ',');
        getline(ss, incidente_id, ',');
        ss >> severidad;

        cout << "Alerta: " << alerta_id << endl;
        cout << "Incidente: " << incidente_id << endl;
        cout << "Severidad: " << severidad << endl;
        cout << "-------------------" << endl;
    }

    archivo.close();

    return 0;
}