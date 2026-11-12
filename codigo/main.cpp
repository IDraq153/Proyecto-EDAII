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

// Ejecucion (formato obligatorio del enunciado):
//   cybershield entrada.csv ranking.csv metricas.txt

int main(int argumentos, char* argv[]) {

    if (argumentos != 4) {
        cout << "Uso: " << argv[0] << " entrada.csv ranking.csv metricas.txt" << endl;
        return 1;
    }
    string ruta_entrada = argv[1];
    string ruta_ranking = argv[2];
    string ruta_metricas = argv[3];

    LectorCSV lector;
    if (!lector.abrirArchivo(ruta_entrada)) {
        cout << "Error: no se pudo abrir " << ruta_entrada << endl;
        return 1;
    }

    int capacidad = 1024;
    int n = 0;
    string* ids = new string[capacidad];
    int* severidades = new int[capacidad];

    string alerta_id, incidente_id;
    int severidad;
    while (lector.leerSiguienteAlerta(alerta_id, incidente_id, severidad)) {
        if (n == capacidad) {
            int nuevaCapacidad = capacidad * 2;
            string* nuevosIds = new string[nuevaCapacidad];
            int* nuevasSev = new int[nuevaCapacidad];
            for (int i = 0; i < n; i++) {
                nuevosIds[i] = ids[i];
                nuevasSev[i] = severidades[i];
            }
            delete[] ids;
            delete[] severidades;
            ids = nuevosIds;
            severidades = nuevasSev;
            capacidad = nuevaCapacidad;
        }
        ids[n] = incidente_id;
        severidades[n] = severidad;
        n++;
    }
    lector.cerrarArchivo();
    Metricas metricas;
    auto inicio = steady_clock::now();

    TablaHash tabla(1024, metricas);   // TODO (equipo): justificar el tamano inicial en el informe
    for (int i = 0; i < n; i++) {
        tabla.registrarAlerta(ids[i], severidades[i]);
    }

    int u = tabla.getCantidadIncidentes();
    Incidente** ranking = new Incidente*[u > 0 ? u : 1];
    tabla.copiarIncidentes(ranking);

    // TODO (equipo): ordenar con el MaxHeap. Cuando maxHeap.cpp este listo, algo como:
    // MIENTRAS TANTO el ranking sale SIN ORDENAR falta esto debemos ordenar.

    auto fin = steady_clock::now();
    metricas.tiempo_proceso_ms = duration<double, milli>(fin - inicio).count();

    ofstream salidaRanking(ruta_ranking);
    if (!salidaRanking.is_open()) {
        cout << "Error: no se pudo crear " << ruta_ranking << endl;
        return 1;
    }
    salidaRanking << "posicion,incidente_id,cantidad_alertas,prioridad_total\n";
    for (int i = 0; i < u; i++) {
        salidaRanking << (i + 1) << ',' << ranking[i]->incidente_id << ','
                      << ranking[i]->cantidad_alertas << ',' << ranking[i]->prioridad_total << '\n';
    }
    salidaRanking.close();

    ofstream salidaMetricas(ruta_metricas);
    if (!salidaMetricas.is_open()) {
        cout << "Error: no se pudo crear " << ruta_metricas << endl;
        return 1;
    }
    salidaMetricas << "sondeos_hash=" << metricas.sondeos_hash << '\n';
    salidaMetricas << "comparaciones_heap=" << metricas.comparaciones_heap << '\n';
    salidaMetricas << "intercambios_heap=" << metricas.intercambios_heap << '\n';
    salidaMetricas << "tiempo_proceso_ms=" << metricas.tiempo_proceso_ms << '\n';
    salidaMetricas.close();

    delete[] ranking;
    delete[] ids;
    delete[] severidades;
    return 0;
}
