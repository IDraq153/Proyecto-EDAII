#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include "incidente.h"
#include "metricas.h"
#include "tabla_hash.h"
#include "max_heap.h"
#include "lector_csv.h"
using namespace std;
using namespace std::chrono;

int main(int argumentos, char* arvg[]) {
    
    if (argumentos <2){
        cout << "USo: " <<arvg[0] << "<archivo.csv> [carpeta_salida]" << endl;
        return 1;
    }
    string ruta_entrada = arvg[1];
    string carpeta_salida = (argumentos >=3) ? arvg[2] : "resultados"
    Metricas metricas;
    TablaHash table(metricas);
    MaxHeap heap(metricas);
    Lector CSV lector;

    if(!lector.abrir(ruta_entrada)){
       cout << "Error: no se pudo abrir " << ruta_entrada << endl;
        return 1; 
    }

    auto inicio = high_resolution_clock::now();

    string alerta_id, incidente_id;
    return 0;
}