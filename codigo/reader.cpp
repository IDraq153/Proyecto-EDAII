#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream archivo("../datos_prueba/5000data.csv");

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
        int numero_alerta = stoi(alerta_id.substr(1));
        
        getline(ss, incidente_id, ',');
        int numero_incidente = stoi(incidente_id.substr(4));
        
        ss >> severidad;

        cout << "Alerta: " << numero_alerta << endl;
        cout << "Incidente: " << numero_incidente << endl;
        cout << "Severidad: " << severidad << endl;
        cout << "-------------------" << endl;
    }

    archivo.close();

    return 0;
}
