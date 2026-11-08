#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include "incidente.h"
#include "metricas.h"
#include "tablaHash.h"
#include "maxHeap.h"
#include "lector_csv.h"
using namespace std;
using namespace std::chrono;

// funcion pasar al heap ira en main
// void pasarAlHeap(maxHeap& heap, Metricas& metricas) {
//     for (int i = 0; i < tamañoTabla; i++) {
//         Incidente* actual = tablaIncidentes[i];
//         while (actual != nullptr) {
//             heap.insertar(*actual, metricas);
//             actual = actual->siguiente;
//         }
//     }
// }

int main(int argumentos, char* arvg[]) {
    
    if (argumentos <2){
        cout << "USo: " <<arvg[0] << "<archivo.csv> [carpeta_salida]" << endl;
        return 1;
    }
    string ruta_entrada = arvg[1];
    string carpeta_salida = (argumentos >=3) ? arvg[2] : "resultados";
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

